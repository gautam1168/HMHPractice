@echo off
mkdir ..\..\build
pushd ..\..\build
copy ..\HMHPractice\code\index.html .\index.html
cl -Zi ..\HMHPractice\code\win32_handmade.cpp user32.lib Gdi32.lib
clang --target=wasm32 --no-standard-libraries -Wl,--export-all -Wl,--no-entry -o web_handmade.wasm ..\HMHPractice\code\web_handmade.cpp
popd