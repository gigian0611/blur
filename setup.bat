git clone https://github.com/microsoft/vcpkg
set root=%~dp0\vcpkg
cd /d %ROOT%
call bootstrap-vcpkg.bat

vcpkg install opencv4:x64-windows
vcpkg integrate install
pause