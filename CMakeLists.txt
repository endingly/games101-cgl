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

add_library(${PROJECT_NAME} ${CGL_SOURCES_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC glfw GLEW::GLEW PRIVATE Freetype::Freetype)
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    PUBLIC_HEADER "${CGL_HEADERS_FILES}"
    VERSION ${PROJECT_VERSION}
    DEBUG_POSTFIX d
)

# ############################################################ install CGL
set(EXPORT_NAME ${PROJECT_NAME}Targets)

install(
    TARGETS ${PROJECT_NAME} 
    EXPORT "${EXPORT_NAME}"
    PUBLIC_HEADER DESTINATION "include/${PROJECT_NAME}"
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION "share/${PROJECT_NAME}"
)

write_basic_package_version_file(
    "${PROJECT_NAME}ConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION share/${PROJECT_NAME}
)

install(
    EXPORT ${EXPORT_NAME}
    DESTINATION share/${PROJECT_NAME}
)