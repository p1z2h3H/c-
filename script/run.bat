@echo off
setlocal
pushd "%~dp0.." || exit /b 1

if not exist "build\tests\training_main.exe" (
    echo training_main.exe does not exist. Run build.bat first.
    popd
    exit /b 1
)

"build\tests\training_main.exe"
set "testExit=%errorlevel%"
popd
exit /b %testExit%
