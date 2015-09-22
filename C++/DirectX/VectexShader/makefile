SRC_EXTEND=.cpp
OBJ_EXTEND=.obj
EXE_EXTEND=.exe

CPP=cl.exe
LD=link.exe

#compile flags setting
CPPFLAGS+=-D_WIN32_WINNT=0x0501
CPPFLAGS+=-DUNICODE
CPPFLAGS+=/MDd
CPPFLAGS+=/EHsc
CPPFLAGS+=/I D:/DirectxSDK/Include
#LDFLAGS+=/MANIFEST:no
LDFLAGS+=/DYNAMICBASE
LDFLAGS+=/LIBPATH:D:/DirectxSDK/Lib/x86
LDFLAGS+=kernel32.lib user32.lib gdi32.lib comctl32.lib shell32.lib winmm.lib dxerr9.lib d3d9.lib d3dx9.lib

#default rule setting
%.exe: %.obj
	$(LD) $(LDFLAGS) $< /OUT:$@
%.obj: %.cpp
	$(CPP) /c $(CPPFLAGS) $< /Fo$@

#source file,obj file and exe file setting
SRC_FILES=$(shell ls *$(SRC_EXTEND))
OBJ_FILES=$(SRC_FILES:%$(SRC_EXTEND)=%$(OBJ_EXTEND))
#EXE_FILES=$(SRC_FILES:%$(SRC_EXTEND)=%$(EXE_EXTEND))
EXE_FILES=Test.exe

#dest setting
all:$(EXE_FILES)

$(EXE_FILES):$(OBJ_FILES)
	$(LD) $(LDFLAGS) $^ /OUT:$@

clean:
	@echo 'cleaning C++...'
	-rm $(OBJ_FILES) *.ilk *.pdb *.manifest
	@echo 'clean end.'

.PHONY:all clean
