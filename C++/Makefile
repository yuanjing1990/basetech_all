#exclude dirs,user can set it
EXCLUDE_DIRS=

ifeq ($(platform),)
	platform=LINUX
endif

ifneq ($(platform),WIN32)
	EXCLUDE_DIRS=DirectX MFC OpenGl
endif

ALL_DIRS=$(foreach i,$(shell ls),$(shell if [ -d ./$(i) ]; then echo $(i);fi))
PROJECT_DIRS=$(filter-out $(EXCLUDE_DIRS),$(ALL_DIRS))
all:$(PROJECT_DIRS)

#Boost MFC OpenGl STL objectmodel DirectX RTL:
$(PROJECT_DIRS):
	@cd $@ && make platform=$(platform)

clean:
	@echo 'cleaning C++...'
	@echo $(foreach i,$(PROJECT_DIRS),$(shell cd $(i) && make clean)) >/dev/null
	@echo 'clean OK'

.PHONY:all clean $(PROJECT_DIRS)
