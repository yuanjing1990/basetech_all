mine.exe:mine.obj minemenu.res
	$(CC) mine.obj minemenu.res kernel32.lib user32.lib gdi32.lib
mine.obj:mine.c
	$(CC) /c /Tp mine.c
minemenu.res:minemenu.rc
	rc minemenu.rc