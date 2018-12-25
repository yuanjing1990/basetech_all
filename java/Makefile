SRC_EXTEND=.java
EXE_EXTEND=.class

JAVAC=javac

#default rule setting
%$(EXE_EXTEND): %$(SRC_EXTEND)
	$(JAVAC) -encoding utf-8 $< 

#source file,obj file and exe file setting
SRC_FILES=$(shell ls *$(SRC_EXTEND))
EXE_FILES=$(SRC_FILES:%$(SRC_EXTEND)=%$(EXE_EXTEND))

#dest setting
all:$(EXE_FILES)

clean:
	@echo 'cleaning java...'
