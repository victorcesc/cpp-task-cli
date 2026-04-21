// Interactive task CLI: two modes in one binary.
//
// 1) REPL (read-eval-print loop): run with no CLI args — the program stays open,
//    reads lines from stdin, and keeps tasks in memory until you quit or EOF.
// 2) One-shot: run with argv subcommands (e.g. ./prog add "title") — one command
//    per process, same as typical shell tools (state does not persist across runs
//    until you add file I/O later).

#include "Task.hpp"

#include <iostream> // std::cin, std::cout, std::flush
#include <span>     // std::span — argv as pointer+length (no C-style array parameter)
#include <sstream>  // std::istringstream — split one input line into command + rest
#include <string>   // std::string — owns task titles in the vector
#include <string_view> // std::string_view — cheap read-only view of argv tokens (no copy)
#include <utility>  // std::move — transfer title into Task without extra copy
#include <vector>   // std::vector — dynamic array of tasks for this run

// Anonymous namespace: helpers here are "file private" — not visible to other .cpp
// translation units and cannot clash with symbols in other files.
namespace
{

// After `iss >> cmd`, a following `std::getline(iss, title)` often leaves leading
// spaces before the title; we strip those so "add   Buy milk" still works.
void trimLeadingSpaces(std::string& text)
{
    while (!text.empty() && text.front() == ' ')
    {
        text.erase(0, 1);
    }
}

auto isReplQuitCommand(std::string_view cmd) -> bool
{
    return cmd == "quit" || cmd == "exit";
}

void printReplHelp()
{
    std::cout << "Commands:\n"
              << "  add <title>   append a task\n"
              << "  list          show all tasks\n"
              << "  help          this message\n"
              << "  quit          exit\n";
}

// 1-based ids in output match common CLI expectations.
void printReplTaskList(const std::vector<Task>& tasks)
{
    if (tasks.empty())
    {
        std::cout << "(no tasks yet)\n";
        return;
    }
    for (const auto& task : tasks)
    {
        std::cout << task.id() << ". " << task.title();
        if (task.isDone())
        {
            std::cout << " [done]";
        }
        std::cout << '\n';
    }
}

// Everything after "add" on the same line becomes the title (getline keeps spaces).
void replHandleAdd(std::istringstream& restOfLine, std::vector<Task>& tasks, int& nextId)
{
    std::string title;
    std::getline(restOfLine, title);
    trimLeadingSpaces(title);
    if (title.empty())
    {
        std::cout << "Usage: add <title>\n";
        return;
    }
    tasks.emplace_back(nextId++, std::move(title));
    std::cout << "Added task " << tasks.back().id() << ".\n";
}

// Interactive mode: loop until user types quit/exit or stdin closes (EOF / Ctrl+D).
void runRepl()
{
    // Tasks live only for this process. Exiting the program discards them unless
    // you later load/save to disk (your roadmap Week 4).
    std::vector<Task> tasks;
    int nextId = 1;

    std::cout << "Task CLI (interactive). Type: add <title> | list | help | quit\n";

    // Infinite loop by design; we only leave via break (quit, EOF, etc.).
    for (;;)
    {
        // Prompt. std::flush forces the prompt to appear before we block on input
        // (line buffering can otherwise delay output until a newline).
        std::cout << "> " << std::flush;

        // Read a full line of user input (including spaces inside the title).
        std::string line;
        if (!std::getline(std::cin, line))
        {
            // getline failed: end-of-file (Ctrl+D on Unix) or stream error — exit loop.
            std::cout << "\n";
            break;
        }

        // Parse the line: first "word" is the command; remainder handled per command.
        std::istringstream iss(line);
        std::string cmd;
        if (!(iss >> cmd))
        {
            // Empty or whitespace-only line — ignore and show prompt again.
            continue;
        }

        if (isReplQuitCommand(cmd))
        {
            break;
        }

        if (cmd == "help")
        {
            printReplHelp();
            continue;
        }

        if (cmd == "list")
        {
            printReplTaskList(tasks);
            continue;
        }

        if (cmd == "add")
        {
            replHandleAdd(iss, tasks, nextId);
            continue;
        }

        std::cout << "Unknown command \"" << cmd << "\". Try help.\n";
    }
}

// Non-interactive mode: argv from the shell (one command, then program exits).
// args[0] = program path/name; args[1] = subcommand; further args depend on command.
// `std::span` is a non-owning view: it does not allocate or free argv — main owns that.
auto runOnce(std::span<char* const> args) -> int
{
    // Fresh vector each invocation — a later separate `./prog list` cannot see data
    // from a previous `./prog add` until you persist to a file.
    std::vector<Task> tasks;
    int nextId = 1;

    if (args.size() < 2)
    {
        // Defensive: main() normally only calls us when argc >= 2; kept for clarity.
        const char* prog = args.empty() ? "task-cli" : args[0];
        std::cout << "Usage: " << prog << " <command> [args...]\n"
                  << "  " << prog << " add \"<title>\"\n"
                  << "  " << prog << " list\n"
                  << "Or run with no arguments for interactive mode.\n";
        return 0;
    }

    // string_view: non-owning pointer+length into argv memory; valid for whole main().
    std::string_view command = args[1];

    if (command == "add")
    {
        // Need exactly: program + "add" + title => three argv slots.
        if (args.size() != 3)
        {
            std::cout << "Usage: " << args[0] << " add \"<title>\"\n";
            return 1; // non-zero exit = error (convention for shell scripts)
        }
        // Copy C-string from argv into std::string so we own storage in the vector.
        tasks.emplace_back(nextId++, args[2]);
        std::cout << "Adding task " << tasks.back().id() << ": " << tasks.back().title() << '\n';
        return 0;
    }

    if (command == "list")
    {
        // list must not take extra argv tokens for this minimal implementation.
        if (args.size() != 2)
        {
            std::cout << "Usage: " << args[0] << " list\n";
            return 1;
        }
        if (tasks.empty())
        {
            std::cout << "(no tasks in this run)\n";
        }
        for (const auto& task : tasks)
        {
            std::cout << task.id() << ". " << task.title();
            if (task.isDone())
            {
                std::cout << " [done]";
            }
            std::cout << '\n';
        }
        return 0;
    }

    std::cout << "Unknown command: " << command << '\n';
    return 1;
}

} // namespace

auto main(int argc, char** argv) -> int
{
    // argc == 1 means only argv[0] (program name) — no subcommand: go interactive.
    if (argc == 1)
    {
        runRepl();
        return 0;
    }

    // return runOnce(argc, argv);
    // argc >= 2: build a span over argv (owned by the runtime) and parse one shot.
    return runOnce(std::span(argv, static_cast<std::size_t>(argc)));
}
