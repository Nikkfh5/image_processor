#include "utils.h"
#include <iostream>
#include "parser/parser.h"
#include "image/image.h"
#include "reading_and_writing/reader.h"
#include "filters/filters.h"
#include "reading_and_writing/writer.h"

std::vector<parser::Argument> GetArguments(int argc, char **argv) {
    std::vector<parser::Argument> arguments = parser::ParseArguments(argc, argv);
    if (arguments.size() <= 2) {
        throw std::invalid_argument("Not enough arguments");
    }
    return arguments;
}

Image GetImage(const std::string &path) {
    read_and_write::Reader reader(path);
    Image image = reader.ReadFile();
    return image;
}

Image ApplyFilter(const std::vector<parser::Argument> &arguments, const Image &initial_image) {
    Image image = initial_image;
    for (size_t i = 2; i < arguments.size(); ++i) {
        image = filter::MakeFilter(arguments[i])->Apply(image);
    }
    return image;
}

void WriteImage(const Image &image, const std::string &path) {
    read_and_write::Writer writer(path);
    writer.WriteImage(image);
}
void DisplayHelp(char **argv) {
    std::cout << "Usage:\n";
    std::cout << argv[0] << " input_file.bmp output_file.bmp [-filter1 [args...]] [-filter2 [args...]] ...\n";
    std::cout << "Supported filters:\n";
    std::cout << "  -crop width height\n";
    std::cout << "  -gs\n";
    std::cout << "  -neg\n";
    std::cout << "  -sharp\n";
    std::cout << "  -edge threshold\n";
    std::cout << "  -blur sigma\n";
    std::cout << "  -pixelate block_size\n";
}
int main(int argc, char **argv) {
    try {
        if (argc <= 1) {
            DisplayHelp(argv);
            return 0;
        }
        std::vector<parser::Argument> arguments = GetArguments(argc, argv);
        Image image = GetImage(arguments[image::utils::INPUT_FILE_POSITION].name);
        image = ApplyFilter(arguments, image);
        WriteImage(image, arguments[image::utils::OUTPUT_FILE_POSITION].name);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
