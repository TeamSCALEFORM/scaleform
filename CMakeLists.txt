cmake_minimum_required(VERSION 3.21)
project(TeamSCALEFORM)

file(GLOB_RECURSE SRC
	"memscan/src/memscan/util/util.c"
	"memscan/src/memscan/memscan.c"

	"scaleform/scaleform.cpp"

	"init.cpp"
	"main.cpp"
)

include("memscan/memscan.cmake")

set_option(MEMSCAN_UNSAFE_OPTIMIZATIONS "Remove memscan safety checks" OFF)
set_option(UTIL_UNSAFE_OPTIMIZATIONS "Remove util safety checks" OFF)

if (UNIX)

# DEBUG or RELEASE
set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_C_FLAGS "-march=native --no-gnu-unique")
set(CMAKE_C_FLAGS_DEBUG "-g3")
set(CMAKE_C_FLAGS_RELEASE "-O3 -s -fvisibility=hidden -DNDEBUG")

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fpermissive")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")

# These are for funchook
add_compile_definitions(DISASM_DISTORM)
add_compile_definitions(_GNU_SOURCE)
add_compile_definitions(_DEBUG)

file(GLOB_RECURSE FUNCHOOK_SOURCES "${CMAKE_SOURCE_DIR}/funchook/src/*.c")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_library("${CMAKE_PROJECT_NAME}" SHARED ${SRC} ${FUNCHOOK_SOURCES})

target_link_options("${CMAKE_PROJECT_NAME}" PRIVATE LINKER:--no-undefined)
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE ${SDL2_LIBRARIES})
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE
    "${CMAKE_SOURCE_DIR}/funchook/include"
)

else()

set(CMAKE_SYSTEM_PROCESSOR "i686")
set(ARCH "x86")

add_definitions(/bigobj /Oi /Ot /Zi /GL /MP)

file(GLOB_RECURSE MINHOOK
	"minhook/src/hde/hde32.c"
	"minhook/src/buffer.c"
	"minhook/src/hook.c"
	"minhook/src/trampoline.c"
)

add_library(${PROJECT_NAME} SHARED ${MINHOOK} ${SRC})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)
add_definitions(/GR- /EHsc)
add_definitions(-D_HAS_EXCEPTIONS=0) #for STL
add_definitions(/MP) #multi-processor compilation

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/minhook/include")

endif()