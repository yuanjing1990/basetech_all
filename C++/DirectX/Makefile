DIRS=$(foreach i,$(shell ls),$(shell if [ -d ./$(i) ]; then echo $(i);fi))
all:$(DIRS)

#MyDirectX:
#	cd MyDirectX && make
#tutorial:
#	cd tutorial && make
#VectexShader:
$(DIRS):
	cd $@ && make
	
clean:
	@echo 'cleaning C++...'
	@echo $(foreach i,$(DIRS),$(shell cd $(i) && make clean)) >/dev/null

