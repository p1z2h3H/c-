@echo off
setlocal
pushd "%~dp0.." || exit /b 1

cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
if errorlevel 1 (
    popd
    exit /b 1
)

cmake --build build --parallel 4
set "buildExit=%errorlevel%"
popd
exit /b %buildExit%
