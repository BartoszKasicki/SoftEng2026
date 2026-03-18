cmake_minimum_required(VERSION 3.10)
project(ShapeLib)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MDd")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MDd")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

# Szukaj plików .cpp i .h w katalogu src
file(GLOB SOURCES CONFIGURE_DEPENDS
     "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

file(GLOB HEADERS CONFIGURE_DEPENDS
     "${CMAKE_SOURCE_DIR}/src/*.h"
)


add_library(ShapeLib STATIC ${SOURCES} ${HEADERS})

#target_link_libraries(ShapeLib PUBLIC Lib::Lib)

target_compile_definitions(ShapeLib PRIVATE BUILDING_CLIENT_DLL)


enable_testing()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(externals/googletest)
# TODO: remove this part later, we can use one exe instead of multiple ones
#target_include_directories(ShapeLib
#    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
#)

#add_executable(tests
#    src/tests/smoke/test_shape1.cpp
#    src/tests/smoke/test_torus.cpp
#)

#target_link_libraries(tests
#    gtest
#    gtest_main
#    ShapeLib
#)

#add_test(NAME tests COMMAND tests)

add_executable(test_shape1 src/tests/smoke/test_shape1.cpp)
target_link_libraries(test_shape1 gtest gtest_main ShapeLib)
target_include_directories(test_shape1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src  PRIVATE ${PROJECT_BINARY_DIR})

add_executable(test_torus src/tests/smoke/test_torus.cpp)
target_link_libraries(test_torus gtest gtest_main ShapeLib)
target_include_directories(test_torus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src  PRIVATE ${PROJECT_BINARY_DIR})

#add_executable(test_shape2 src/tests/smoke/test_shape2.cpp)
#target_link_libraries(test_shape2 gtest gtest_main ShapeLib)
#target_include_directories(test_shape2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src  PRIVATE ${PROJECT_BINARY_DIR})

add_test(NAME test_shape1 COMMAND test_shape1)
add_test(NAME test_torus COMMAND test_torus)
#add_test(NAME test_shape2 COMMAND test_shape2)
