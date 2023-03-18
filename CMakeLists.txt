cmake_minimum_required(VERSION 3.12)

project(Cider VERSION 1.3.0 DESCRIPTION "A little experimental and header only lib to improve operator ->* shitty syntax")

option(EXAMPLE "EXAMPLE" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(lib)

if (EXAMPLE)
	add_executable(cider_example example/main.cpp)
	target_compile_options(cider_example
						PRIVATE
						$<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
						$<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra -Wall -Wsign-conversion -Wfloat-equal -pedantic -Wredundant-decls -Wshadow -Wpointer-arith -O3>)
	target_link_libraries(cider_example PRIVATE cider)
endif()					   