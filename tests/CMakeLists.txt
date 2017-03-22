add_executable(helloworld helloworld.cpp)
target_link_libraries(helloworld PRIVATE seastar)


add_executable(test_continuous main.cpp
        test_continuous.cpp)
target_link_libraries(test_continuous PRIVATE seastar)


add_executable(test_distributed main.cpp
        test_distributed.cpp)
target_link_libraries(test_distributed PRIVATE seastar)