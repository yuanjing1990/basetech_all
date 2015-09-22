os=WIN32
config=debug

EXCLUDE_DIRS=

ALL_DIRS=$(foreach i,$(shell ls),$(shell if [ -d ./$(i) ];then echo $(i);fi))
DIRS=$(filter-out $(EXCLUDE_DIRS),$(ALL_DIRS))

os=$(shell uname -s)
ifeq ($(os),WIN32)
CPP=cl.exe
CPPFLAGS=
CC=cl.exe
CFLAGS=
LD=link.exe
LDFLAGS=

ifeq ($(config),debug)
CPPFLAGS+=-DDEBUG
CPPFLAGS+=/MDd
CFLAGS+=/TC
LDFLAGS+=
else
CPPFLAGS+=-DRELEASE
CPPFLAGS+=/MD
CFLAGS+=/TC
LDFLAGS+=
endif

##define make rule############################->Begin
%.obj:%.cpp %.hpp
	$(CPP) /c $(CPPFLAGS) $< /Fo$@
%.exe:%.obj
	$(LD) $(LDFLAGS) $< /OUT:$@
##define make rule############################-<End
endif
export

all:$(DIRS)

#$(DIRS):
C++:
	cd $@ && make

clean:
	@echo $(foreach i,$(DIRS),$(shell cd $(i) && make clean))>/dev/null 

.PHONY:all clean $(DIRS)

unexport EXCLUDE_DIRS
unexport ALL_DIRS
unexport DIRS

