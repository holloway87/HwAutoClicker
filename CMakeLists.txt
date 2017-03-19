cmake_minimum_required(VERSION 3.6)
project(HwAutoClicker)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp AutoClicker.cpp)
add_executable(HwAutoClicker ${SOURCE_FILES})
target_link_libraries(HwAutoClicker X11 Xtst)
install(TARGETS HwAutoClicker DESTINATION bin)
