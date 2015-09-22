DIRS=$(foreach i,$(shell ls),$(shell if [ -d ./$(i) ]; then echo $(i);fi))
all:$(DIRS)

Boost MFC OpenGl STL objectmodel DirectX RTL:
	@cd $@ && make
	
clean:
	@echo 'cleaning C++...'
	@echo $(foreach i,$(DIRS),$(shell cd $(i) && make clean)) >/dev/null

