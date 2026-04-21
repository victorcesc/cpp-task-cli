#pragma once

#include <string>

// Week 2: a small type that owns one task's data (encapsulation + ctor).
// `id` is stable for this run (used later for done/remove); `title` is the text;
// `done` is reserved for Week 3+ without exposing mutable state yet.
class Task
{
public:
    Task(int taskId, std::string title);

    [[nodiscard]] auto id() const noexcept -> int
    {
        return id_;
    }

    [[nodiscard]] auto title() const noexcept -> const std::string&
    {
        return title_;
    }

    [[nodiscard]] auto isDone() const noexcept -> bool
    {
        return done_;
    }

private:
    int id_{};
    std::string title_;
    bool done_{false};
};
