cmake_minimum_required(VERSION 3.20)
project(love)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PkgConfig REQUIRED)

set(LOVE_SOURCES
    ${PROJECT_SOURCE_DIR}/src/love.cpp
    ${PROJECT_SOURCE_DIR}/src/json.cpp
    ${PROJECT_SOURCE_DIR}/src/curl.cpp
)

add_executable(love ${LOVE_SOURCES})
target_include_directories(love PUBLIC ${PROJECT_SOURCE_DIR}/src)

pkg_check_modules(JANSSON REQUIRED jansson)
target_include_directories(love PUBLIC ${JANSSON_INCLUDE_DIRS})
target_link_libraries(love ${JANSSON_LINK_LIBRARIES})
target_compile_options(love PUBLIC ${JANSSON_CFLAGS_OTHER})

pkg_check_modules(LIBCURL REQUIRED libcurl)
target_include_directories(love PUBLIC ${LIBCURL_INCLUDE_DIRS})
target_link_libraries(love ${LIBCURL_LINK_LIBRARIES})
target_compile_options(love PUBLIC ${LIBCURL_CFLAGS_OTHER})