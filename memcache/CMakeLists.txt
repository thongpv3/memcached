add_executable(memcache memcache.cc)
target_link_libraries(memcache PRIVATE seastar)
#todo fix ragel build command
#execute_process(COMMAND ragel ascii.rl -o ${CMAKE_CURRENT_BINARY_DIR}/ascii.hh WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}) #using ragel to compile ascii protocol
target_include_directories(memcache PRIVATE ${CMAKE_CURRENT_BINARY_DIR}) #add include directory to memcache

set(MY_MEMCACHE_SRCS main.cpp
        item.h
        cache.h
        allocation_strategy.hh)
add_executable(my_memcache ${MY_MEMCACHE_SRCS})
target_link_libraries(my_memcache PRIVATE seastar)