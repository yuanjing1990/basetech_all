HelloMsg.exe:HelloMsg.obj
	$(CC) HelloMsg.obj kernel32.lib user32.lib gdi32.lib
HelloMsg.obj:HelloMsg.c
	$(CC) /c HelloMsg.c

clean:
	rm *.obj *.exe