@echo off
cmake -S . -B build
cmake --build build --config Debug
.\build\bin\Debug\simulator.exe
pause