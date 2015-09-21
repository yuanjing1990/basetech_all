#pragma once
#include <windows.h>

class ETL_FRAME_CLASS_NAME
{
public:
	enum {_IDS_MENU,_IDS_STATUS,_IDS_NAME,_IDS_VER};
	enum {_ALLOW_OPEN_SAME_GROUP,_ALLOW_MULTIPLE_INSTANCES,_MAX_EE_VERSION,_MIN_EE_VERSION,
		_SUPPORT_EE_PRO,_SUPPORT_EE_STD};
	enum {_MASK_TRUE_COLOR,_MASK_256_COLOR};
	enum {_IDB_TRUE_24_BW,_IDB_TRUE_24_HOT,_IDB_TRUE_24_DEFAULT,_IDB_256C_24_BW,_IDB_256C_24_HOT,
		_IDB_256C_24_DEFAULT,_IDB_16C_24,_IDB_TRUE_16_BW,_IDB_TRUE_16_HOT,_IDB_TRUE_16_DEFAULT,
		_IDB_256C_16_BW,_IDB_256C_16_HOT,_IDB_256C_16_DEFAULT,_IDB_BITMAP};
	ETL_FRAME_CLASS_NAME(){};
	~ETL_FRAME_CLASS_NAME(){};
	
	virtual void OnCommand( HWND hwndView ){};
	
	void OnEvents( HWND hwndView, UINT nEvent ){};
	
	BOOL QueryStatus( HWND hwndView, LPBOOL pbChecked ){return true;};
	
	LRESULT PlugInProc( HWND hwnd, UINT nMsg, WPARAM /*wParam*/, LPARAM /*lParam*/ ){return 0;};
	
	LRESULT QueryUninstall(HWND hwnd){return 0;};
	LRESULT SetUninstall(HWND hwnd ){return 0;};
	LRESULT QueryProperties(HWND hwnd ){return 0;};
	LRESULT SetProperties(HWND hwnd ){return 0;};
};