# Virtual Wardrobe Assistant - Qt Version

This is a Qt Widgets desktop implementation of your OOP + file handling project.

## GUI Features
- User profile form: age, skin tone, height category, preferred style.
- Wardrobe manager: add item, view all items in table, remove by ID.
- Outfit recommendation tab using:
  - style matching
  - occasion filtering
  - skin tone suitability
  - height-based scoring
  - age/style compatibility
- Persistent storage:
  - `user_profile.txt`
  - `wardrobe_data.txt`

## OOP Architecture
- `ClothingItem` model: item data + serialization.
- `UserProfile` model: personal attributes + serialization.
- `FileManager`: all file read/write operations.
- `WardrobeManager`: item add/remove/query logic.
- `RecommendationEngine`: scoring + best outfit recommendation.
- `MainWindow` (Qt UI): connects user actions to backend classes.

## Project Files
- CMake project: `CMakeLists.txt`
- qmake project: `virtual_wardrobe_qt.pro`
- Qt UI code: `qt/main.cpp`, `qt/MainWindow.h`, `qt/MainWindow.cpp`
- Backend logic: `include/*.h`, `src/*.cpp`

## Build with CMake (Verified)
From project root:

```powershell
New-Item -ItemType Directory -Force build-qt-cmake | Out-Null
cd build-qt-cmake

$env:PATH = "C:\Qt\Tools\mingw1310_64\bin;C:\Qt\6.10.2\mingw_64\bin;C:\Qt\Tools\CMake_64\bin;" + $env:PATH
& "C:\Qt\Tools\CMake_64\bin\cmake.exe" -S .. -B . -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/Qt/6.10.2/mingw_64"
& "C:\Qt\Tools\CMake_64\bin\cmake.exe" --build . -j 4
```

Run:
```powershell
.\virtual_wardrobe_qt.exe
```

## Qt Creator
You can open either:
- `CMakeLists.txt` (recommended), or
- `virtual_wardrobe_qt.pro`

Then choose your Desktop Qt kit and build/run.
