#
# sample makefile to illustrate batch-mode inference rules
#
O = .
S = .
Objs = $O/ColorCode.obj $O/streamiterator.obj $O/usevector.obj $O/example_istream_iterator.obj $O/limit.obj $O/any_main.obj\
 $O/auto_ptr.obj $O/constructor.obj $O/newhandler.obj $O/overnew.obj $O/preprocess.obj $O/rtti.obj $O/streambuffer.obj $O/memorycheck.obj
Dest = $O/ColorCode.exe $O/streamiterator.exe $O/usevector.exe $O/example_istream_iterator.exe $O/limit.exe $O/any_main.obj\
 $O/auto_ptr.exe $O/constructor.exe $O/newhandler.exe $O/overnew.exe $O/preprocess.exe $O/rtti.exe $O/streambuffer.exe $O/memorycheck.exe\
 Dir_example_boost Dir_exprtmp Dir_meta Dir_mystl Dir_parameter Dir_search Dir_traits Dir_types
CPPFLAGS = -nologo /EHsc


$(Dest) :

{$S}.obj{$O}.exe::
   $(CC) $(CPPFLAGS) -Fd$O\ $<
#!ifdef NOBatch
#{$S}.cpp{$O}.obj:
#!else
#{$S}.cpp{$O}.obj::
#!endif
#   $(CC) $(CFLAGS) -Fd$O\ -c $<
 
$(Objs) :

#end of makefile

Dir_example_boost:
	cd example_boost && nmake

Dir_exprtmp:
	cd exprtmp && nmake

Dir_meta:
	cd meta && nmake

Dir_mystl:
	cd mystl && nmake

Dir_parameter:
	cd parameter && nmake

Dir_search:
	cd search && nmake

Dir_traits:
	cd traits && nmake

Dir_types:
	cd types && nmake

clean:
	del *.obj *.exe
	cd example_boost && nmake clean
	cd exprtmp && nmake clean
	cd meta && nmake clean
	cd mystl && nmake clean
	cd parameter && nmake clean
	cd search && nmake clean
	cd traits && nmake clean
	cd types && nmake clean