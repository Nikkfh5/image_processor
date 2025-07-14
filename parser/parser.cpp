#include "parser.h"
namespace parser {
void Argument::ClearArgument() {
    name.clear();
    parameters.clear();
}

bool Argument::IsEmpty() const {
    return name.empty() && parameters.empty();
}

std::vector<Argument> ParseArguments(int argc, char **argv) {
    std::vector<Argument> arguments;
    Argument tmp;
    for (size_t i = 1; i != static_cast<size_t>(argc); ++i) {
        std::string str(argv[i]);
        if (i == 1 || i == 2) {
            tmp.name = str;
            tmp.parameters.clear();
            arguments.push_back(tmp);
            tmp.ClearArgument();
        }

        else {
            if (str.front() == '-') {
                if (!tmp.IsEmpty()) {
                    arguments.push_back(tmp);
                    tmp.ClearArgument();
                }
                tmp.name = str;
            } else {
                tmp.parameters.push_back(str);
            }
        }
    }
    if (!tmp.IsEmpty()) {
        arguments.push_back(tmp);
    }
    return arguments;
}
}  // namespace parser
