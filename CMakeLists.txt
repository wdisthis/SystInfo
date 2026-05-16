cmake_minimum_required(VERSION 3.15)
project(SystInfo VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WIN32_EXECUTABLE ON)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/Providers.cpp
    src/Renderer.cpp
    src/Window.cpp
)

set(HEADERS
    include/Providers.hpp
    include/Renderer.hpp
    include/Window.hpp
)

add_executable(SystInfo WIN32 ${SOURCES} ${HEADERS})

target_compile_definitions(SystInfo PRIVATE 
    UNICODE 
    _UNICODE 
    _WIN32_WINNT=0x0600
)

target_link_libraries(SystInfo
    PRIVATE
    pdh
    iphlpapi
    d2d1
    dwrite
    dwmapi
    ws2_32
)

# MSVC specific compiler flags for a lightweight binary
if(MSVC)
    target_compile_options(SystInfo PRIVATE /W4 /WX-)
    # Optional: Linker flags for smaller binary
    set_target_properties(SystInfo PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
endif()

if(MINGW)
    target_link_options(SystInfo PRIVATE -municode)
endif()
