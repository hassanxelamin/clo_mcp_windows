# CLO MCP Plugin

This project is a plugin for CLO, demonstrating integration with external systems.

## Building

This project uses CMake and requires the Microsoft Visual C++ compiler toolset (MSVC) and Qt 5.15.

**Prerequisites:**

*   Visual Studio Build Tools (2019 or later) with C++ workload installed.
*   CMake (version 3.20 or later).
*   Qt 5.15.2 (specifically the `msvc2019_64` version). Ensure the `QTDIR` environment variable is set, or provide the path during CMake configuration.
*   CLO API SDK (ensure it is placed in the `sdk` directory relative to the project root as expected by `CMakeLists.txt`).

**Steps:**

1.  **Open the Correct Command Prompt:**
    *   Go to your Windows Start Menu.
    *   Search for and open the **"x64 Native Tools Command Prompt for VS 2019"** (or the equivalent for your VS version). Using the x64 prompt is crucial to match the 64-bit libraries.

2.  **Navigate to the Project Directory:**
    ```bash
    cd path\to\clo_mcp\mcp
    ```

3.  **Create a Build Directory:**
    ```bash
    mkdir build
    cd build
    ```

4.  **Configure with CMake:** Run the following command from within the `build` directory. Adjust the `CMAKE_PREFIX_PATH` if your Qt installation is different.
    ```bash
    cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="C:\Qt\5.15.2\msvc2019_64"
    ```

5.  **Build with NMake:**
    ```bash
    nmake
    ```

6.  **Output:** The compiled plugin (`Plugin.dll`) will be located in the `build` directory. 