#rebuid seastar project if neccessary
execute_process(COMMAND ninja -C ${CMAKE_CURRENT_SOURCE_DIR})

set(SEASTAR_LIB_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/build)
if (CMAKE_BUILD_TYPE MATCHES RELEASE)
set(SEASTAR_LIB_LOCATION ${SEASTAR_LIB_LOCATION}/release)
else ()
set(SEASTAR_LIB_LOCATION ${SEASTAR_LIB_LOCATION}/debug)
endif ()
find_package(PkgConfig REQUIRED)
execute_process(COMMAND pkg-config --cflags --libs ${SEASTAR_LIB_LOCATION}/seastar.pc OUTPUT_VARIABLE SEASTAR_LIB)
string(STRIP "${SEASTAR_LIB}" SEASTAR_LIB)
#add library
add_library(seastar INTERFACE)
target_link_libraries(seastar INTERFACE ${SEASTAR_LIB})