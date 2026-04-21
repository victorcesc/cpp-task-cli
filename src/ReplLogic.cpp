#include "ReplLogic.hpp"

#include "Task.hpp"

#include <istream>
#include <ostream>
#include <string>
#include <utility>

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

void printReplHelp(std::ostream& out)
{
    out << "Commands:\n"
        << "  add <title>   append a task\n"
        << "  list          show all tasks\n"
        << "  help          this message\n"
        << "  quit          exit\n";
}

void printReplTaskList(const std::vector<Task>& tasks, std::ostream& out)
{
    if (tasks.empty())
    {
        out << "(no tasks yet)\n";
        return;
    }
    for (const auto& task : tasks)
    {
        out << task.id() << ". " << task.title();
        if (task.isDone())
        {
            out << " [done]";
        }
        out << '\n';
    }
}

void replHandleAdd(std::istream& restOfLine, std::vector<Task>& tasks, int& nextId, std::ostream& out)
{
    std::string title;
    std::getline(restOfLine, title);
    trimLeadingSpaces(title);
    if (title.empty())
    {
        out << "Usage: add <title>\n";
        return;
    }
    tasks.emplace_back(nextId++, std::move(title));
    out << "Added task " << tasks.back().id() << ".\n";
}
