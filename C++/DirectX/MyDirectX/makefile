SRC_EXTEND=.cpp
OBJ_EXTEND=.obj
EXE_EXTEND=.exe

CPP=cl.exe
LD=link.exe

#compile flags setting
CPPFLAGS+=-D_WIN32_WINNT=0x0501
CPPFLAGS+=/MDd
CPPFLAGS+=/EHsc
CPPFLAGS+=/I D:/DirectxSDK/Include
#LDFLAGS+=/MANIFEST:no
LDFLAGS+=/DYNAMICBASE
LDFLAGS+=/LIBPATH:D:/DirectxSDK/Lib/x86
LDFLAGS+=kernel32.lib user32.lib d3dx9.lib d3d9.lib

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
	-rm -rf $(OBJ_FILES) *.exe *.ilk *.pdb *.manifest

.PHONY:all clean
