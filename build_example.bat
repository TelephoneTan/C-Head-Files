@echo off
cls
chcp 65001
rd build /s /q
mkdir build
cd build
echo -------------------start------------------->log.txt
echo=>>log.txt
set WD=%cd%
cd "D:\Program Files (x86)\Microsoft Visual Studio"
cd "2019\Community\VC\Auxiliary\Build"
echo -------------------init------------------->>"%WD%\log.txt"
call vcvarsall.bat x86 >>"%WD%\log.txt" 2>&1
cd "%WD%"
echo -------------------cmake------------------->log2.txt
cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Debug >>log2.txt 2>&1
echo -------------------MSBuild------------------->>log2.txt
nmake >>log2.txt 2>&1
echo -------------------end------------------->>log2.txt
move /Y log.txt ../log.txt >nul
move /Y log2.txt ../log2.txt >nul
echo ---------------------run---------------------
CPP_HEADERS.exe
echo -------------------run-end-------------------
cd ..