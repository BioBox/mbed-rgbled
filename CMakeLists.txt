
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
set(MBED_PATH ${PROJECT_SOURCE_DIR}/../os/mbed-os/ CACHE INTERNAL "")
set(MBED_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR}/.. CACHE INTERNAL "")

include(${MBED_PATH}/tools/cmake/app.cmake)

add_library(rgbled rgbled.cpp)
target_include_directories(rgbled INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rgbled mbed-os)
set_target_properties(rgbled PROPERTIES LINKER_LANGUAGE CXX)
