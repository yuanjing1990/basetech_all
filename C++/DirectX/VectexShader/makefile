OBJTMP=DXUT.obj DXUTenum.obj DXUTmisc.obj
COMLIB=dxerr.lib dxguid.lib d3dx9d.lib d3d9.lib winmm.lib comctl32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib

VertexShader.exe:VertexShader.obj dxut.lib
	cl /Gm VertexShader.obj $(COMLIB) dxut.lib

VertexShader.obj:VertexShader.c
	cl /TP /c VertexShader.c

DXUT.lib:$(OBJTMP)
	lib DXUT.obj DXUTenum.obj DXUTmisc.obj $(COMLIB)

$(OBJTMP):DXUT.h DXUT.cpp DXUTenum.h DXUTenum.cpp DXUTmisc.h DXUTmisc.cpp
	cl /c /TP /D"UNICODE" DXUT.cpp DXUTenum.cpp DXUTmisc.cpp

CLEAR:
	del *.obj *.exe *.lib