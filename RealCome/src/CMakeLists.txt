set(core_SRCS main.cpp)
add_library(core ${core_SRCS})
add_executable(main main.cpp Realization.cpp Chain.h)

target_link_libraries(main core)