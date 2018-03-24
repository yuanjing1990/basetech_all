ifeq ($(platform),)
	platform=LINUX
endif

ALL_DIRS=$(foreach i,$(shell ls),$(shell if [ -d ./$(i) ]; then echo $(i);fi))

#dest setting
all:
	make -f Makefile.$(platform) all

$(ALL_DIRS):
	cd $@ && make platform=$(platform)

clean:
	make -f Makefile.$(platform) clean

#@echo $(foreach i,$(ALL_DIRS),$(shell cd $(i) && make clean)) >/dev/null

.PHONY:all clean
