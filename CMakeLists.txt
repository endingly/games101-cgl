cmake_minimum_required(VERSION 3.25)

project(CGL VERSION 0.1.0 LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_STATIC_LIBS "Build shared libraries" ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)

# target CGL
file(GLOB_RECURSE CGL_SOURCES_FILES src/*.cpp)
file(GLOB_RECURSE CGL_HEADERS_FILES include/*.h)

if(BUILD_STATIC_LIBS)
    add_library(CGL ${CGL_SOURCES_FILES})
    target_link_libraries(CGL PUBLIC glfw GLEW::GLEW Freetype::Freetype)
    target_include_directories(
        CGL PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
    set_target_properties(
        CGL PROPERTIES
        PUBLIC_HEADER "${CGL_HEADERS_FILES}"
        VERSION ${PROJECT_VERSION}
    )
    set(EXPORT_LIBS CGL)
endif()

# ############################################################ install CGL
set(EXPORT_NAME ${PROJECT_NAME}Targets)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

install(
    TARGETS "${EXPORT_LIBS}"
    EXPORT "${EXPORT_NAME}"
    PUBLIC_HEADER DESTINATION "include/${PROJECT_NAME}"
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}"
)

write_basic_package_version_file(
    "${PROJECT_NAME}ConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
          "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION lib/cmake/${PROJECT_NAME}
)

install(
    EXPORT ${EXPORT_NAME}
    DESTINATION lib/cmake/${PROJECT_NAME}
    NAMESPACE CGL::
)