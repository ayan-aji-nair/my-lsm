cmake_minimum_required(VERSION 3.30)
project(my_lsm)

# use C++ 20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

# how to link external libraries
find_package(fmt)

# another way to include libraries

# depend on googletest, which we download from github
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# enable address sanitizer
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

# add build options
option(ENABLE_ASAN "Enable AddressSanitzer" OFF)
option(ENABLE_TSAN "Enable ThreadSanitizer" OFF)

add_compile_options(-fsanitize=undefined)
add_link_options(-fsanitize=undefined)

add_compile_options(-Werror)
add_link_options(-Werror)

add_compile_options(-flto)
add_link_options(-flto)

if (ENABLE_ASAN)
  add_compile_options(-fsanitize=address)
  add_link_options(-fsanitize=address)
elseif (ENABLE_TSAN)
  add_compile_options(-fsanitize=thread)
  add_link_options(-fsanitize=thread)
endif()

add_executable(${PROJECT_NAME} main.cpp)
# default to static, can make this dynamic

# add my own package and fmt
target_link_libraries(${PROJECT_NAME} lib fmt::fmt)

# add my own lib
add_subdirectory(lib)
add_subdirectory(tests)



