#exclude dirs,user can set it
EXCLUDE_DIRS=

ALL_DIRS=$(foreach i,$(shell ls),$(shell if [ -d ./$(i) ]; then echo $(i);fi))
PROJECT_DIRS=$(filter-out $(EXCLUDE_DIRS),$(ALL_DIRS))
all:$(PROJECT_DIRS)

#Boost MFC OpenGl STL objectmodel DirectX RTL:
$(PROJECT_DIRS):
	@cd $@ && make
	
clean:
	@echo 'cleaning C++...'
	@echo $(foreach i,$(DIRS),$(shell cd $(i) && make clean)) >/dev/null

