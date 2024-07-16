project(TESTS)

include(CTest)

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/boost_1_85_0")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/boost_1_85_0/lib64-msvc-14.0")

# Найдите пакет Boost
find_package(Boost REQUIRED)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

# Добавьте директории заголовочных файлов Boost к пути поиска заголовочных файлов
include_directories(${Boost_INCLUDE_DIRS})

enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_executable(string_test "string_test.cpp")
target_link_libraries(string_test ${Boost_LIBRARIES})

add_test(Test_0, "${CMAKE_SOURCE_DIR}/bin/string_tests" "0")