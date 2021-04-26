cmake_minimum_required(VERSION 3.9)
set (CMAKE_CXX_STANDARD 11)

project(node_fwlib VERSION 0.0.1)

set(DEPS "fwlib32" "config")

find_library(FWLIB NAMES fwlib32 libfwlib32 HINTS "${CMAKE_SOURCE_DIR}/lib" REQUIRED)
add_library(fwlib32 SHARED IMPORTED)
set_target_properties(fwlib32 PROPERTIES
  IMPORTED_LOCATION "${FWLIB}"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/lib")
list(APPEND DEPS "m" "pthread")

# target_link_libraries(${DEPS})


include_directories(${CMAKE_JS_INC})
string(APPEND CMAKE_C_FLAGS "-Wall -Wextra -Wno-unused-parameter -Wendif-labels")

file(GLOB SOURCE_FILES src/*.cpp src/*.h src/*.cc src/*.c)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} ${DEPS})

# Include Node-API wrappers
execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )

# need to pay attention to this part
string(REGEX REPLACE "[\r\n\"]" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})

# Define NAPI_VERSION
add_definitions(-DNAPI_VERSION=3)

