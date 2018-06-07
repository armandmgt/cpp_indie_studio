@echo off
echo %CD%
if not exist ..\..\include\irrlicht.zip (
	unzip -o -q ..\..\irrlicht.zip ..\..\include\irrlicht
)
if exist ..\..\bin\Debug\bomberman.exe (
	xcopy /s/z/y ..\..\bin\Debug\bomberman.exe ..\..\bin\
	echo "bomberman binary in debug mode copied"
	rmdir /s /q ..\..\bin\Debug
	echo "Debug directory removed"
) else if exist ..\..\bin\Release\bomberman.exe (
	xcopy /s/z/y ..\..\bin\Release\bomberman.exe ..\..\bin\
	echo "bomberman binary in release mode copied"
	rmdir /s /q ..\..\bin\Release
	echo "Release directory removed"
) else (echo "No such file bomberman.exe at %CD%"
)
exit