all:tutorial.exe test.exe
	
tutorial.exe:tutorial.obj
	cl tutorial.obj kernel32.lib user32.lib gdi32.lib d3d9.lib
tutorial.obj:tutorial.cpp
	cl /c /TP tutorial.cpp
test.exe:test.obj DirectX9.obj
	cl test.obj DirectX9.obj kernel32.lib user32.lib gdi32.lib d3d9.lib d3dx9.lib winmm.lib
test.obj:test.cpp DirectX9.obj
	cl /c /TP test.cpp DirectX9.cpp