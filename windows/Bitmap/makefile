Bitmap.exe:Bitmap.obj Bitmap.res
	$(CC) Bitmap.obj Bitmap.res kernel32.lib user32.lib gdi32.lib
Bitmap.obj:Bitmap.c
	$(CC) /c /Tp Bitmap.c
Bitmap.res:Bitmap.rc
	rc Bitmap.rc
CLEAR:
	del *.exe *.obj *.res