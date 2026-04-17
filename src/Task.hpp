#pragma once
#include <string>

class Task
{
public:
    Task(int id, std::string title);

private:
    int id;
    std::string title;
    bool done = false;
};