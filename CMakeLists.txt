cmake_minimum_required(VERSION 3.21)
project(TeamSCALEFORM)

set(CMAKE_SYSTEM_PROCESSOR "i686")
set(ARCH "x86")

add_definitions(/bigobj /Oi /Ot /Zi /GL /MP)

include("memscan/memscan.cmake")

file(GLOB_RECURSE SRC
	"minhook/src/hde/hde32.c"
	"minhook/src/buffer.c"
	"minhook/src/hook.c"
	"minhook/src/trampoline.c"

	"memscan/src/memscan/util/util.c"
	"memscan/src/memscan/memscan.c"

	"scaleform/scaleform.cpp"

	"init.cpp"
	"main.cpp"
)

set_option(MEMSCAN_UNSAFE_OPTIMIZATIONS "Remove memscan safety checks" OFF)
set_option(UTIL_UNSAFE_OPTIMIZATIONS "Remove util safety checks" OFF)


add_library(${PROJECT_NAME} SHARED ${SRC})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)
add_definitions(/GR- /EHsc)
add_definitions(-D_HAS_EXCEPTIONS=0) #for STL
add_definitions(/MP) #multi-processor compilation

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/minhook/include")