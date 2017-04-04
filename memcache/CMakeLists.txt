add_executable(memcache memcache.cc)
target_link_libraries(memcache PRIVATE seastar)
execute_process(COMMAND ragel ascii.rl -o ${CMAKE_CURRENT_BINARY_DIR}.hh WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}) #using ragel to compile ascii protocol
target_include_directories(memcache PRIVATE ${CMAKE_CURRENT_BINARY_DIR}) #add include directory to memcache