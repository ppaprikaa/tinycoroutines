set(PLAY_TARGET ${LIB_TARGET}_PLAY)

add_executable(${PLAY_TARGET} main.cpp)

target_link_libraries(${PLAY_TARGET} ${LIB_TARGET})
