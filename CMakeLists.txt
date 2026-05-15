cmake_minimum_required(VERSION 3.15)
project(SystInfo VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Win32 Subsystem for GUI application
set(CMAKE_WIN32_EXECUTABLE ON)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/Providers.cpp
    src/Renderer.cpp
)

# Header files (for IDE visibility)
set(HEADERS
    include/Providers.hpp
    include/Renderer.hpp
    include/Window.hpp
)

add_executable(SystInfo WIN32 ${SOURCES} ${HEADERS})

# Link Windows libraries
target_link_libraries(SystInfo
    PRIVATE
    pdh         # Performance Data Helper (CPU)
    iphlpapi    # IP Helper API (Network)
    d2d1        # Direct2D
    dwrite      # DirectWrite
    dwmapi      # Desktop Window Manager (Transparency)
    ws2_32      # Winsock (Optional but good for network)
)

# MSVC specific compiler flags for a lightweight binary
if(MSVC)
    target_compile_options(SystInfo PRIVATE /W4 /WX-)
    # Optional: Linker flags for smaller binary
    set_target_properties(SystInfo PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
endif()
