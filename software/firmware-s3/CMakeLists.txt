# CMakeLists.txt for mpair ESP32-S3 firmware
# Requires ESP-IDF v5.5.2+
cmake_minimum_required(VERSION 3.16)

# Set the target to ESP32-S3
set(IDF_TARGET esp32s3)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(mpair-s3)
