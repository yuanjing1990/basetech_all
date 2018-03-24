CPPFLAGS=-nologo /EHsc
test.exe:test.obj
	$(CC) $(CPPFLAGS) test.obj
test.obj:test.cpp *.h

clean:
	@-rm *.obj *.exe
