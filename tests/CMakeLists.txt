add_executable(helloworld helloworld.cpp)
target_include_directories(helloworld PRIVATE ${SEASTAR_INCLUDE})
target_link_libraries(helloworld PRIVATE seastar)