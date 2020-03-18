@echo off
chcp 65001
rd build_github /s /q
mkdir build_github
cd build_github
echo -------------------start-------------------
echo=
echo -------------------init-------------------
echo=
echo -------------------cmake-------------------
cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Debug
echo -------------------MSBuild-------------------
nmake 
echo -------------------end-------------------
echo=
echo ---------------------run---------------------
CPP_HEADERS.exe
echo -------------------run-end-------------------