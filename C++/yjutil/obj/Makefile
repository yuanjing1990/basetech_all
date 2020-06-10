ifeq ($(platform),)
	platform=LINUX
endif

#dest setting
all:
	make -f Makefile.$(platform) all

clean:
	make -f Makefile.$(platform) clean

.PHONY:all clean
