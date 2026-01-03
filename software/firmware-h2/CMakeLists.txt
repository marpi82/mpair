# CMakeLists.txt for mpair ESP32-H2 firmware (Matter/Thread)
cmake_minimum_required(VERSION 3.16)

# Set the target to ESP32-H2
set(IDF_TARGET esp32h2)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(mpair-h2)
