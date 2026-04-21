#pragma once

#include <iosfwd>
#include <string>
#include <string_view>
#include <vector>

class Task;

void trimLeadingSpaces(std::string& text);

[[nodiscard]] auto isReplQuitCommand(std::string_view cmd) -> bool;

void printReplHelp(std::ostream& out);

void printReplTaskList(const std::vector<Task>& tasks, std::ostream& out);

// Everything after "add" on the same line becomes the title (getline keeps spaces).
void replHandleAdd(std::istream& restOfLine, std::vector<Task>& tasks, int& nextId, std::ostream& out);
