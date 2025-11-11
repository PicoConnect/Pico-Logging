@echo off
setlocal

echo.
echo == Changing to repo root ==
pushd "%~dp0\.."

cd /d "%cd%"

REM if not defined PICO_CONNECT (
    REM echo Installing Pico Libraries on
	REM set INSTALL_PATH="%~d0\PicoLibraries\"
REM )

set INSTALL_PATH="%~d0\PicoLibraries\"

rem Choose config (Release by default)
set CONFIG=Release

rem Create/configure the build dir if needed
if not exist "build\CMakeCache.txt" (
  echo.
  echo == Configuring CMake (first time) ==
  cmake -S . -B build -DCMAKE_BUILD_TYPE=%CONFIG%
  if errorlevel 1 goto :fail
)

rem Build (handles MSVC/Ninja Multi-Config)
echo.
echo == Building (%CONFIG%) ==
cmake --build build --config %CONFIG%
if errorlevel 1 goto :fail

rem Install (only if you have install() rules)
echo.
echo == Installing ==
cmake --install build --config %CONFIG% --prefix PicoLogging
::cmake --install build --config %CONFIG%
if errorlevel 1 goto :fail

echo.
echo ✅ Done.
popd
exit /b 0

:fail
echo.
echo ❌ Failed with errorlevel %errorlevel%.
popd
exit /b %errorlevel%
