# SystInfo - Custom Taskbar Widget

SystInfo is a lightweight, high-performance C++ application designed to provide real-time system monitoring directly on your Windows taskbar. It offers a clean, non-intrusive way to track your PC's health without opening heavy applications like Task Manager.

## Tech Stack
| Component | Technology |
| :--- | :--- |
| **Language** | C++17 |
| **Graphics** | Direct2D (Hardware accelerated) |
| **UI Framework** | Win32 API (Native Windows) |
| **Build System** | CMake 3.15+ |

## Features
| Feature | Description | Metric Source |
| :--- | :--- | :--- |
| **CPU Monitor** | Real-time percentage usage | GetSystemTimes (Native Windows API) |
| **RAM Monitor** | Memory usage percentage | GlobalMemoryStatusEx |
| **Network Speed** | Upload (↑) and Download (↓) speeds in MB/s | IP Helper API (GetIfTable2) |
| **Disk Usage** | Free space for C: and D: drives | GetDiskFreeSpaceExW |

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
│   ├── Renderer.cpp      # UI implementation
│   └── Window.cpp        # Window event handling
├── README.md             # Project documentation
└── CMakeLists.txt        # Build configuration
```

## Requirements
- **OS**: Windows 10 or 11
- **Compiler**: MSVC (Visual Studio 2019+) or MinGW-w64 (MSYS2)
- **Build Tool**: CMake 3.15+

## How to Build

### Using MSYS2 (MinGW)
Run the following in your MinGW64 terminal:
```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

### Using Visual Studio
1. Open the project folder in Visual Studio.
2. CMake will automatically detect the configuration.
3. Select `Release` and click **Build > Build All**.

## Usage
1. Run `SystInfo.exe`.
2. The widget will appear at the bottom right, above the taskbar.
3. It is borderless and features a translucent dark background for a premium look.

## Important Notes
- **Resource Usage**: Designed to consume <10MB RAM and <0.5% CPU.
- **Admin Rights**: Network metrics might require administrative privileges in some environments.
- **Overlay Position**: Positioned relative to the primary monitor's resolution.
