@echo off
setlocal

:: Install on this drive
echo == Changing to repo root ==
pushd "%~dp0\.."

cd /d "%cd%"

:: The parent directory (e.g. E:\PicoLibraries)
set "INSTALL_PATH=%~d0\PicoLibraries"

:: The name of the package (no slashes)
set "INSTALL_FOLDER=PicoLogging"

:: Combined installation location: e.g. E:\PicoLibraries\PicoLogging
set "INSTALL_LOCATION=%INSTALL_PATH%\%INSTALL_FOLDER%"

set "CONFIG=Release"

echo == Installing at: "%INSTALL_LOCATION%" ==
cmake --install build --config %CONFIG% --prefix "%INSTALL_LOCATION%"
if errorlevel 1 goto :fail

echo.
popd
exit /b 0

:fail
echo.
echo Failed with errorlevel %errorlevel%.
popd
exit /b %errorlevel%
