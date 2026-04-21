#include <catch2/catch_test_macros.hpp>

#include "ReplLogic.hpp"
#include "Task.hpp"

#include <sstream>
#include <string>
#include <vector>

TEST_CASE("trimLeadingSpaces removes leading spaces", "[repl]")
{
    std::string s{"   hello"};
    trimLeadingSpaces(s);
    REQUIRE(s == "hello");
}

TEST_CASE("trimLeadingSpaces leaves non-leading content", "[repl]")
{
    std::string s{"  a  b"};
    trimLeadingSpaces(s);
    REQUIRE(s == "a  b");
}

TEST_CASE("isReplQuitCommand recognizes quit and exit", "[repl]")
{
    REQUIRE(isReplQuitCommand("quit"));
    REQUIRE(isReplQuitCommand("exit"));
    REQUIRE_FALSE(isReplQuitCommand("help"));
    REQUIRE_FALSE(isReplQuitCommand("quit "));
    REQUIRE_FALSE(isReplQuitCommand(""));
}

TEST_CASE("printReplTaskList empty", "[repl]")
{
    std::vector<Task> tasks;
    std::ostringstream out;
    printReplTaskList(tasks, out);
    REQUIRE(out.str() == "(no tasks yet)\n");
}

TEST_CASE("printReplTaskList formats tasks", "[repl]")
{
    std::vector<Task> tasks;
    tasks.emplace_back(1, "First");
    tasks.emplace_back(2, "Second");
    std::ostringstream out;
    printReplTaskList(tasks, out);
    REQUIRE(out.str() == "1. First\n2. Second\n");
}

TEST_CASE("printReplHelp mentions core commands", "[repl]")
{
    std::ostringstream out;
    printReplHelp(out);
    const auto s = out.str();
    REQUIRE(s.find("add") != std::string::npos);
    REQUIRE(s.find("list") != std::string::npos);
    REQUIRE(s.find("quit") != std::string::npos);
}

TEST_CASE("replHandleAdd rejects empty title", "[repl]")
{
    std::vector<Task> tasks;
    int nextId = 1;
    std::istringstream in{""};
    std::ostringstream out;
    replHandleAdd(in, tasks, nextId, out);
    REQUIRE(tasks.empty());
    REQUIRE(out.str() == "Usage: add <title>\n");
}

TEST_CASE("replHandleAdd appends task and bumps id", "[repl]")
{
    std::vector<Task> tasks;
    int nextId = 10;
    std::istringstream in{"  Buy oats"};
    std::ostringstream out;
    replHandleAdd(in, tasks, nextId, out);
    REQUIRE(tasks.size() == 1);
    REQUIRE(tasks[0].id() == 10);
    REQUIRE(tasks[0].title() == "Buy oats");
    REQUIRE(nextId == 11);
    REQUIRE(out.str() == "Added task 10.\n");
}
