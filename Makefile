DIRS=$(foreach i,$(shell ls),$(shell if [ -d ./$(i) ];then echo $(i);fi))

CPPFLAGS=
CFLAGS=

%.obj:%.cpp %.hpp
	$(CPP) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
%.exe:%.obj
	$(LD) $(LDFLAGS) $< -o $@


all:$(DIRS)

C++:
	cd $@ && make

clean:
	@echo $(foreach i,$(DIRS),$(shell cd $(i) && make clean))>/dev/null
