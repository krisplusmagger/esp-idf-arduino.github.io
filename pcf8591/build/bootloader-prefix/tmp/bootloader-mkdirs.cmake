# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/caoxinyu/esp/esp-idf/components/bootloader/subproject"
  "/Users/caoxinyu/Desktop/esp32_project/pcf8591/build/bootloader"
  "/Users/caoxinyu/Desktop/esp32_project/pcf8591/build/bootloader-prefix"
  "/Users/caoxinyu/Desktop/esp32_project/pcf8591/build/bootloader-prefix/tmp"
  "/Users/caoxinyu/Desktop/esp32_project/pcf8591/build/bootloader-prefix/src/bootloader-stamp"
  "/Users/caoxinyu/Desktop/esp32_project/pcf8591/build/bootloader-prefix/src"
  "/Users/caoxinyu/Desktop/esp32_project/pcf8591/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/caoxinyu/Desktop/esp32_project/pcf8591/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
