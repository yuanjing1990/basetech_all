sfdsf
platform=WIN32
config=debug

EXCLUDE_DIRS=

ALL_DIRS=$(foreach i,$(shell ls),$(shell if [ -d ./$(i) ];then echo $(i);fi))
DIRS=$(filter-out $(EXCLUDE_DIRS),$(ALL_DIRS))

platform=$(shell uname -s)
ifneq ($(platform),WIN32)
	platform=LINUX
endif

ifeq ($(platform),WIN32)
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

ifeq ($(platform),LINUX)
EXCLUDE_DIRS+=csharp windows
CPP=g++
CPPFLAGS=
CC=gcc
CFLAGS=
LD=ld
LDFLAGS=

ifeq ($(config),debug)
CPPFLAGS+=
CFLAGS+=
LDFLAGS+=
else
CPPFLAGS+=
CFLAGS+=
LDFLAGS+=
endif

##define make rule############################->Begin
%.o:%.cpp %.hpp
	$(CPP) -c $(CPPFLAGS) $< -o $@
%.exe:%.o
	$(LD) $(LDFLAGS) $< $@
##define make rule############################-<End
endif
export

all:$(DIRS)

#$(DIRS):
C++:
	cd $@ && make platform=$(platform)

clean:
	@echo $(foreach i,$(DIRS),$(shell cd $(i) && make clean platform=$(platform)))>/dev/null 

.PHONY:all clean $(DIRS)

unexport EXCLUDE_DIRS
unexport ALL_DIRS
unexport DIRS

