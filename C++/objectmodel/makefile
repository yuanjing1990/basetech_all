#
#定义目标文件
#
ALL_PROG=objectmodel.exe point.exe

#伪目标生成所有程序
all:$(ALL_PROG)
	
#定义生成目标块-----------》
objectmodel.exe:objectmodel.cpp
	cl $(**F) /EHsc
point.exe:point.cpp
	cl $(**F) /EHsc
#定义生成目标块-----------《

#伪目标清理临时文件
clear:
	del *.obj *.exe