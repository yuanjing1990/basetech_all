SRC_EXTEND=.cpp
OBJ_EXTEND=.obj
EXE_EXTEND=.exe

CPP=cl.exe
LD=link.exe

#compile flags setting
CPPFLAGS+=-D_WIN32_WINNT=0x0501
CPPFLAGS+=/EHsc
CPPFLAGS+=/MDd
LDFLAGS+=/MANIFEST
#LDFLAGS+=/MANIFESTDEPENDENCY:type="Win32"
#LDFLAGS+=/MANIFESTUAC:level=asInvoker
#LDFLAGS+=/INCREMENTAL:no

#default rule setting
%.exe: %.obj
	$(LD) $(LDFLAGS) $< /OUT:$@
%.obj: %.cpp
	$(CPP) /c $(CPPFLAGS) $< /Fo$@

#source file,obj file and exe file setting
SRC_FILES=$(shell ls *$(SRC_EXTEND))
OBJ_FILES=$(SRC_FILES:%$(SRC_EXTEND)=%$(OBJ_EXTEND))
EXE_FILES=$(SRC_FILES:%$(SRC_EXTEND)=%$(EXE_EXTEND))

#dest setting
all:$(EXE_FILES)

clean:
	-rm -rf $(OBJ_FILES) *.exe *.ilk *.pdb *.manifest

.PHONY:all clean
