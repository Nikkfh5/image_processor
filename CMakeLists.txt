cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(
        image_processor
        image_processor.cpp
        image/color.h
        image/image.h
        image/image.cpp
        reading_and_writing/reader.cpp
        reading_and_writing/reader.h
        utils.h
        parser/parser.h
        parser/parser.cpp
        reading_and_writing/writer.cpp
        reading_and_writing/writer.h
        filters/filters.h
        filters/grayscale.h
        filters/grayscale.cpp
        filters/filters.cpp
        filters/gauss.h
        filters/gauss.cpp
        image/color.cpp
        filters/negative.h
        filters/negative.cpp
        filters/crop.h
        filters/crop.cpp
        filters/sharp.h
        filters/sharp.cpp
        filters/edge.h
        filters/edge.cpp
        filters/pixelate.h
        filters/pixelate.cpp
        unit_tests.cpp
        test_pixelate.cpp
)