test.exe:test.obj DirectX9.obj
	$(CC) test.obj DirectX9.obj d3d9.lib kernel32.lib user32.lib gdi32.lib d3dx9.lib
test.obj:test.cpp
	$(CC) /c test.cpp
DirectX9.obj:DirectX9.cpp
	$(CC) /c DirectX9.cpp
