# verify platform
if (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
  message(FATAL_ERROR "${PROJECT_NAME}: Your platform is currently not supported.")
endif()

# verify compiler
if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  message("${PROJECT_NAME}: Your compiler is not officially supported. Issues or build errors may occur.")
endif()

# options
macro(set_option option help value)
    option(${option} ${help} ${value})
    if(${option})
        message(STATUS "${PROJECT_NAME}: ${option}: ON")
        target_compile_definitions(${PROJECT_NAME} PUBLIC ${option})
    else()
        message(STATUS "${PROJECT_NAME}: ${option}: OFF")
    endif()
endmacro()