get_filename_component(LIB_INCLUDE_PATH ".." ABSOLUTE)
get_filename_component(LIB_PATH "." ABSOLUTE)

add_library(${LIB_TARGET} STATIC 
	coroutine.hpp
	coroutine.cpp
	)

target_include_directories(${LIB_TARGET} PUBLIC ${LIB_INCLUDE_PATH})
target_link_libraries(${LIB_TARGET} PUBLIC ctx function2)
