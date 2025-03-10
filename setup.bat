git clone https://github.com/microsoft/vcpkg
set root=%~dp0\vcpkg
start %root%\bootstrap-vcpkg.bat
pushd %root%
vcpkg install opencv4:x64-windows
vcpkg integrate install
pause