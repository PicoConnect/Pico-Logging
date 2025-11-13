@echo off
setlocal


rem 1. Go to root directory (one level above where this bat file is kept)
pushd "%~dp0\.."
set "ROOT=%CD%"

:: ===========================================================================
:: SCRIPT CONFIG
if not defined BUILD_DIR (
    set "BUILD_DIR=%ROOT%\build"
    echo Setting BUILD_DIR: %BUILD_DIR%
)

if not defined CONFIG (
    set "CONFIG=Release"
    echo Setting CONFIG: %CONFIG%
)

:: Board we're building binary for:
:: Supported board:
::  - pico_w
::  - pico2_w
if not defined PICO_BOARD (
    set "PICO_BOARD=pico_w"
    echo Setting PICO_BOARD: %PICO_BOARD%
)
:: ===========================================================================

echo ==== Begin Building in %CONFIG% ====
echo Root: %ROOT%
echo Build dir: %BUILD_DIR%
echo.

rem === 2. Clean build dir ===
if exist "%BUILD_DIR%" (
    echo Deleting build folder "%BUILD_DIR%"
    rmdir /s /q "%BUILD_DIR%"
)
mkdir "%BUILD_DIR%"

echo.
echo == Configuring Cmake in %CONFIG% ==
echo cmake -S "%ROOT%" -B "%BUILD_DIR%" -G "Ninja Multi-Config"
cmake -S "%ROOT%" -B "%BUILD_DIR%" -G "Ninja Multi-Config" -DPICO_BOARD=%PICO_BOARD%
if %ERRORLEVEL% NEQ 0 goto :cmake_fail

echo.
echo == Building (%CONFIG%) ==
cmake --build "%BUILD_DIR%" --config %CONFIG%
if %ERRORLEVEL% NEQ 0 goto :build_fail

echo.
echo ==== Build completed successfully ====
popd
exit /b 0

:cmake_fail
echo.
echo ==== Error: CMake Configure Failed ====
popd
exit /b 1

:build_fail
echo.
echo ==== Error: Build Failed ====
popd
exit /b 1
