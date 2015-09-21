all:test.exe test1.exe test2.exe

LINKER=link
COMPLIER_FLAGS=/EHsc
LINKER_FLAGS=/SUBSYSTEM:WINDOWS
WNDLIBS=kernel32.lib user32.lib gdi32.lib

test.obj:test.cpp
	$(CPP) $(COMPLIER_FLAGS) /c test.cpp

test.exe:test.obj
	$(LINKER) $(LINKER_FLAGS) test.obj

test1.obj:test1.cpp
	$(CPP) $(COMPLIER_FLAGS) /c test1.cpp

test1.exe:test1.obj
	$(LINKER) $(LINKER_FLAGS) test1.obj $(WNDLIBS)

test2.exe:test2.obj
	$(LINKER) $(LINKER_FLAGS) test2.obj $(WNDLIBS)
test2.obj:test2.cpp
	$(CPP) $(COMPLIER_FLAGS) /c test2.cpp

clean:
	del *.obj *.exe