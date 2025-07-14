#include <iostream>
#include <stdexcept>
#include <cassert>
#include "parser/parser.h"
#include "filters/filters.h"
#include "image/image.h"
#include "reading_and_writing/reader.h"
#include "reading_and_writing/writer.h"

void TestInvalidArguments() {
    using parser::Argument;

    try {
        filter::MakeFilter(Argument{"-neg", {"1"}});
        assert(false);
    } catch (...) {
    }
    try {
        filter::MakeFilter(Argument{"-crop", {"100"}});
        assert(false);
    } catch (...) {
    }
    try {
        filter::MakeFilter(Argument{"-edge", {}});
        assert(false);
    } catch (...) {
    }
    try {
        filter::MakeFilter(Argument{"-blur", {"abc"}});
        assert(false);
    } catch (...) {
    }
    try {
        filter::MakeFilter(Argument{"-pixelate", {"4", "5"}});
        assert(false);
    } catch (...) {
    }
    try {
        filter::MakeFilter(Argument{"-unknown", {}});
        assert(false);
    } catch (...) {
    }
}

void TestReaderThrows() {
    try {
        read_and_write::Reader reader("test_data/nonexistent.bmp");
        reader.ReadFile();
        assert(false);
    } catch (...) {
    }
    try {
        read_and_write::Reader reader("test_data/bad_format.txt");
        reader.ReadFile();
        assert(false);
    } catch (...) {
    }
}

void TestWriterReadWrite() {
    read_and_write::Reader reader("test_data/input.bmp");
    Image image = reader.ReadFile();

    read_and_write::Writer writer("test_data/temp_out.bmp");
    writer.WriteImage(image);

    read_and_write::Reader reader2("test_data/temp_out.bmp");
    Image reread = reader2.ReadFile();

    assert(image.GetWidth() == reread.GetWidth() && image.GetHeight() == reread.GetHeight());
}

void TestImageAccess() {
    Image img(image::utils::NORM_COORDINATES, image::utils::NORM_COORDINATES);
    img.SetColor(image::utils::BASE_COORDINATES, image::utils::BASE_COORDINATES,
                 Color(image::utils::BASE_BLUE_COLOR, image::utils::BASE_GREEN_COLOR, image::utils::BASE_RED_COLOR));
    Color c = img.GetColor(image::utils::BASE_COORDINATES, image::utils::BASE_COORDINATES);
    assert(c.red == image::utils::BASE_RED_COLOR && c.green == image::utils::BASE_GREEN_COLOR &&
           c.blue == image::utils::BASE_BLUE_COLOR);

    try {
        img.GetColor(image::utils::BIG_COORDINATES, image::utils::BIG_COORDINATES);
        assert(false);
    } catch (...) {
    }
}

void TestParserBasic() {
    char arg0[] = "image_processor";
    char arg1[] = "test_data/input.bmp";
    char arg2[] = "out.bmp";
    char arg3[] = "-crop";
    char arg4[] = "10";
    char arg5[] = "10";
    char arg6[] = "-gs";
    char arg7[] = "-blur";
    char arg8[] = "1.0";

    char* argv[] = {arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8};
    int argc = sizeof(argv) / sizeof(argv[0]);

    auto args = parser::ParseArguments(argc, argv);

    assert(args[0].name == "test_data/input.bmp");
    assert(args[1].name == "out.bmp");
    assert(args[2].name == "-crop");
    assert(args[2].parameters == std::vector<std::string>({"10", "10"}));
    assert(args[3].name == "-gs");
    assert(args[4].name == "-blur");
    assert(args[4].parameters == std::vector<std::string>({"1.0"}));
}

int Main2() {
    TestInvalidArguments();
    TestReaderThrows();
    TestWriterReadWrite();
    TestImageAccess();
    TestParserBasic();

    std::cout << "All tests passed!\n";
    return 0;
}
