cmake_minimum_required(VERSION 3.6)
project(memcache)

set(CMAKE_CXX_STANDARD 14)


#add libs
add_subdirectory(include)

#add custom memcache
add_subdirectory(memcache)

#add tests
add_subdirectory(tests)
