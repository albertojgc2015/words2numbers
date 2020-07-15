cmake_minimum_required(VERSION 3.18.0)
project(Words2Numbers)
set(SOURCES Words2Numbers/Words2Numbers/Words2Numbers.cpp)
# TODO: Add tests here so they are verified before multiplatform compilation
add_executable(Words2Numbers Words2Numbers.cpp)
