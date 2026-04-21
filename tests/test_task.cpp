#include <catch2/catch_test_macros.hpp>

#include "Task.hpp"

#include <string>

TEST_CASE("Task stores id and title", "[task]")
{
    Task t{7, "Buy milk"};
    REQUIRE(t.id() == 7);
    REQUIRE(t.title() == "Buy milk");
}

TEST_CASE("Task is not done by default", "[task]")
{
    Task t{1, "x"};
    REQUIRE_FALSE(t.isDone());
}

TEST_CASE("Task title can be moved in", "[task]")
{
    std::string title{"Long enough title to avoid SSO surprises"};
    Task t{1, std::move(title)};
    REQUIRE(t.title() == "Long enough title to avoid SSO surprises");
}
