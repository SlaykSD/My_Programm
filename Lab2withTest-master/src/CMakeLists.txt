set(core_SRCS main.cpp)
add_library(core ${core_SRCS})
add_executable(main main.cpp lab2.20.cpp lab2.20.h)

target_link_libraries(main core)
