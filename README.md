# SystInfo - Custom Taskbar Widget

SystInfo is a light weight, high-performance C++ application designed to provide real-time system monitoring directly on your Windows 10 taskbar. It offers a clean, non-intrusive way to track your PC's health without opening heavy applications like Task Manager.


## Tech Stack
| Component | Technology |
| :--- | :--- |
| Language | C++17 |
| Graphics | Direct2D (Hardware accelerated) |
| UI Framework | Win32 API (Native Windows) |
| Build System | CMake 3.15+ |

## Features
| Feature | Description | Metric Source |
| :--- | :--- | :--- |
| CPU Monitor | Real-time percentage usage | PDH (Performance Data Helper) |
| RAM Monitor | Memory usage percentage | GlobalMemoryStatusEx |
| Network Speed | Upload (↑) and Download (↓) speeds in MB/s | IP Helper API |
| Disk Usage | Free space for C: and D: drives (English) | GetDiskFreeSpaceExW |

## Project Structure
```text
SystInfo/
├── include/              # Header files (.hpp)
│   ├── Providers.hpp     # System data gathering logic
│   ├── Renderer.hpp      # Direct2D drawing logic
│   └── Window.hpp        # Win32 Window management
├── src/                  # Source files (.cpp)
│   ├── main.cpp          # Entry point & Message loop
│   ├── Providers.cpp     # Metric implementations
│   └── Renderer.cpp      # UI implementation
├── README.md             # This file
└── CMakeLists.txt        # Build configuration
```

## Requirements
- OS: Windows 10 (Optimized)
- Compiler: MSVC (Visual Studio 2019 or 2022 recommended)
- Build Tool: CMake 3.15+

## How to Run
1. **Clone & Open**: Open the project folder in Visual Studio or your favorite C++ IDE.
2. **Build**: 
   - Using CMake: 
     ```bash
     mkdir build
     cd build
     cmake ..
     cmake --build . --config Release
     ```
3. **Launch**: Run `SystInfo.exe`.
4. **Usage**: The widget will automatically appear above your taskbar. It is borderless and follows your taskbar's background theme.

## Important Notes
- **Admin Rights**: Some network metrics might require administrative privileges depending on your Windows security settings.
- **Overlay Position**: The widget is programmed to auto-detect your taskbar's location. If you move your taskbar, the widget will re-align itself on the next refresh.
- **Resource Usage**: Designed to consume <10MB RAM and <0.5% CPU.
- **No GPU Monitoring**: This version explicitly excludes GPU monitoring to minimize library dependencies.
