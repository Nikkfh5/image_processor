#pragma once
#include <string>
#include <vector>

namespace parser {
struct Argument {
    std::string name;
    std::vector<std::string> parameters;
    void ClearArgument();
    bool IsEmpty() const;
};

std::vector<Argument> ParseArguments(int argc, char **argv);
}  // namespace parser
