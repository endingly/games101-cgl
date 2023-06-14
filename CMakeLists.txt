cmake_minimum_required(VERSION 3.25)

project(games101-cgl VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)

# target CGL
file(GLOB_RECURSE CGL_SOURCES_FILES src/*.cpp)
file(GLOB_RECURSE CGL_HEADERS_FILES include/*.h)

add_library(CGL ${CGL_SOURCES_FILES})
target_link_libraries(CGL PUBLIC glfw GLEW::GLEW PRIVATE Freetype::Freetype)
target_include_directories(
    CGL PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
set_target_properties(
    CGL PROPERTIES
    PUBLIC_HEADER "${CGL_HEADERS_FILES}"
    VERSION ${PROJECT_VERSION}
    DEBUG_POSTFIX d
)

# ############################################################ install CGL
install(
    TARGETS CGL 
    EXPORT CGLTargets
    PUBLIC_HEADER DESTINATION "include/CGL"
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/CGLConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/CGLConfig.cmake"
    INSTALL_DESTINATION "share/CGL"
)

write_basic_package_version_file(
    "CGLConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES "${PROJECT_BINARY_DIR}/CGLConfig.cmake"
    "${PROJECT_BINARY_DIR}/CGLConfigVersion.cmake"
    DESTINATION share/CGL
)

install(
    EXPORT CGLTargets
    DESTINATION share/CGL
)