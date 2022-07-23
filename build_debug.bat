set PATH=%PATH%;C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.32.31326\bin\Hostx86\x86\

cd C:\Users\gabriel\Documents\GitHub\cavalcade

cmake.exe --preset x86-debug
cd out/build/x86-debug/
ninja -v