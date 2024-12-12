cmake_minimum_required(VERSION 3.0) # setting this is required
project(rs232soc)            # this sets the project name

file(GLOB_RECURSE sources src/*.cpp src/*.h)
add_executable(rs232soc ${sources} ${data})

target_compile_options(rs232soc PUBLIC -std=c++17 -Wall -Wfloat-conversion)

target_include_directories(rs232soc PUBLIC src)

file(COPY ${data} DESTINATION resources)

find_package(Boost 1.86.0 COMPONENTS filesystem system REQUIRED)

target_link_libraries(rs232soc PUBLIC
  ${Boost_LIBRARIES}
)

install(TARGETS rs232soc DESTINATION build)

set(CPACK_PACKAGE_NAME "rs232soc")
set(CPACK_PACKAGE_VERSION "0.1.0")

set(CPACK_MONOLITHIC_INSTALL 1)

include(CPack)
