#include "Task.hpp"

#include <utility>

Task::Task(int taskId, std::string title)
    : id_(taskId)
    , title_(std::move(title))
{
}
