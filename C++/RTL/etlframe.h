#if _MSC_VER > 1000
#pragma once
#endif

#include "plugin.h"
#include "ETL_FRAME_CLASS_NAME.h"
#include <crtdbg.h>
#pragma warning( push )
#pragma warning( disable : 4995 ) // 'function': name was marked as #pragma deprecated
#if _MSC_VER < 0x0700
	#pragma warning( disable : 4786 ) // dentifier was truncated to '255' characters in the browser information
	#pragma warning( disable : 4512 ) // assignment operator could not be generated
	#pragma warning( disable : 4100 ) // unreferenced formal parameter

#endif
#include <map>
#pragma warning( pop )

#if _MSC_VER < 0x0700
	#pragma warning( push )
	#pragma warning( disable : 4127 ) // conditional expression is constant
	#pragma warning( disable : 4786 ) // dentifier was truncated to '255' characters in the browser information
#endif

#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif

// these asserts fail on previous versions of EmEditor (v4.13 or earlier).
#ifdef TEST_V5
#define ASSERT_STRICT(x) _ASSERTE(x)
#else
#define ASSERT_STRICT(x) (void(0))
#endif

#ifdef EE_IMPLEMENT
#define EE_EXTERN
#else
#define EE_EXTERN extern
#endif

#ifdef _DEBUG
#ifdef _DEBUG_NEW
#define new _DEBUG_NEW
#endif
#endif

// forward declaration
#define DEFINE_CREATE(c) 
class ETL_FRAME_CLASS_NAME;
template <typename T> class CETLFrame;
typedef CETLFrame<ETL_FRAME_CLASS_NAME> CETLFrameX;
typedef std::map<HWND, CETLFrameX*> CETLFrameMap;
CETLFrameX* _ETLCreateFrame();
void _ETLDeleteFrame( CETLFrameX* pFrame );

#define _ETL_IMPLEMENT CETLFrameX* _ETLCreateFrame() { CETLFrameX* pFrame = new ETL_FRAME_CLASS_NAME; return pFrame; } void _ETLDeleteFrame( CETLFrameX* pFrame ) { delete static_cast<ETL_FRAME_CLASS_NAME*>(pFrame); }

_ETL_IMPLEMENT
// global data definition
class CETLData
{
public:
	HINSTANCE			m_hInstance;
	CRITICAL_SECTION	m_cs;
	CETLFrameMap*		m_pETLFrameMap;
	WORD				m_wCmdID;

	CETLData() 
	{
		ZeroMemory( this, sizeof( CETLData ) );
		InitializeCriticalSection( &m_cs );
	}

	~CETLData() 
	{
		DeleteCriticalSection( &m_cs );
	}

	void Lock() 
	{
		EnterCriticalSection( &m_cs );
	}

	void Unlock()
	{
		::LeaveCriticalSection( &m_cs );
	}
} _ETLData;

class CETLLock
{
public:
	CETLLock()
	{
		_ETLData.Lock();
	}

	~CETLLock()
	{
		_ETLData.Unlock();
	}
};

template <typename T> class __declspec(novtable) CETLFrame
{
public:
	HWND	m_hWnd;
	CETLFrame<T>() : m_hWnd(0)
	{
	}

	virtual ~CETLFrame<T>()
	{
	}

	virtual void OnCommand( HWND hwndView )
	{
		T* pT = static_cast<T*>(this);
		pT->OnCommand( hwndView );
	}

	void OnEvents( HWND hwndView, UINT nEvent )
	{
		T* pT = static_cast<T*>(this);
		pT->OnEvents( hwndView, nEvent );
	}

	BOOL QueryStatus( HWND hwndView, LPBOOL pbChecked )
	{
		T* pT = static_cast<T*>(this);
		return pT->QueryStatus( hwndView, pbChecked );
	}

	static UINT GetMenuTextID()
	{
		return T::_IDS_MENU;
	}

	static UINT GetStatusMessageID()
	{
		return T::_IDS_STATUS;
	}

	static UINT GetBitmapID()
	{
		return T::_IDB_BITMAP;
	}

	static LRESULT GetStringA( LPSTR pBuf, size_t cchBuf, UINT nID )
	{
		char sz[80];
		LRESULT lResult = LoadStringA( EEGetInstanceHandle(), nID, sz, _countof( sz ) ) + 1;
		_ASSERTE( lResult > 1 );
		if( pBuf ){
			lstrcpynA( pBuf, sz, (int)cchBuf );
		}
		return lResult;
	}

	static LRESULT GetStringW( LPWSTR pBuf, size_t cchBuf, UINT nID )
	{
		WCHAR sz[80];
		LRESULT lResult = LoadStringW( EEGetInstanceHandle(), nID, sz, _countof( sz ) ) + 1;   // LoadStringW does not work on Windows 9x, but that is OK.
		_ASSERTE( lResult > 1 );  
		if( pBuf ){
			lstrcpynW( pBuf, sz, (int)cchBuf );
		}
		return lResult;
	}

	static LRESULT GetNameA( LPSTR pBuf, size_t cchBuf )
	{
		return GetStringA( pBuf, cchBuf, T::_IDS_NAME );
	}

	static LRESULT GetNameW( LPWSTR pBuf, size_t cchBuf )
	{
		return GetStringW( pBuf, cchBuf, T::_IDS_NAME );
	}

	static LRESULT GetVersionA( LPSTR pBuf, size_t cchBuf )
	{
		return GetStringA( pBuf, cchBuf, T::_IDS_VER );
	}

	static LRESULT GetVersionW( LPWSTR pBuf, size_t cchBuf )
	{
		return GetStringW( pBuf, cchBuf, T::_IDS_VER );
	}

	static LRESULT GetInfo( WPARAM flag )
	{
		LRESULT lResult = 0;
		switch( flag ){
		case EPGI_ALLOW_OPEN_SAME_GROUP:
			lResult = T::_ALLOW_OPEN_SAME_GROUP;
			break;
		case EPGI_ALLOW_MULTIPLE_INSTANCES:
			lResult = T::_ALLOW_MULTIPLE_INSTANCES;
			break;
		case EPGI_MAX_EE_VERSION:
			lResult = T::_MAX_EE_VERSION;
			break;
		case EPGI_MIN_EE_VERSION:
			lResult = T::_MIN_EE_VERSION;
			break;
		case EPGI_SUPPORT_EE_PRO:
			lResult = T::_SUPPORT_EE_PRO;
			break;
		case EPGI_SUPPORT_EE_STD:
			lResult = T::_SUPPORT_EE_STD;
			break;
		}
		return lResult;
	}

	LRESULT PlugInProc( HWND hwnd, UINT nMsg, WPARAM /*wParam*/, LPARAM /*lParam*/ )
	{
		LRESULT lResult = 0;
		T* pT = static_cast<T*>(this);
		switch( nMsg ){
		case EP_QUERY_UNINSTALL:
			lResult = pT->QueryUninstall( hwnd );
			break;
		case EP_SET_UNINSTALL:
			lResult = pT->SetUninstall( hwnd );
			break;
		case EP_QUERY_PROPERTIES:
			lResult = pT->QueryProperties( hwnd );
			break;
		case EP_SET_PROPERTIES:
			lResult = pT->SetProperties( hwnd );
			break;
		}
		return lResult;
	}

	static LRESULT GetMask( WPARAM wParam )
	{
		LRESULT lResult = 0;
		if( wParam & BITMAP_24BIT_COLOR ){
			lResult = T::_MASK_TRUE_COLOR;
		}
		else if( wParam & BITMAP_256_COLOR ){
			lResult = T::_MASK_256_COLOR;
		}
		return lResult;
	}

	static LRESULT GetBitmap( WPARAM wParam )
	{
		LRESULT lResult = 0;
		if( wParam & BITMAP_LARGE ){
			if( wParam & BITMAP_24BIT_COLOR ){
				if( wParam & BITMAP_DISABLED ){
					lResult = T::_IDB_TRUE_24_BW;
				}
				else if( wParam & BITMAP_HOT ){
					lResult = T::_IDB_TRUE_24_HOT;
				}
				else {
					lResult = T::_IDB_TRUE_24_DEFAULT;
				}
			}
			else if( wParam & BITMAP_256_COLOR ){
				if( wParam & BITMAP_DISABLED ){
					lResult = T::_IDB_256C_24_BW;
				}
				else if( wParam & BITMAP_HOT ){
					lResult = T::_IDB_256C_24_HOT;
				}
				else {
					lResult = T::_IDB_256C_24_DEFAULT;
				}
			}
			else {
				lResult = T::_IDB_16C_24;
			}
		}
		else {
			if( wParam & BITMAP_24BIT_COLOR ){
				if( wParam & BITMAP_DISABLED ){
					lResult = T::_IDB_TRUE_16_BW;
				}
				else if( wParam & BITMAP_HOT ){
					lResult = T::_IDB_TRUE_16_HOT;
				}
				else {
					lResult = T::_IDB_TRUE_16_DEFAULT;
				}
			}
			else if( wParam & BITMAP_256_COLOR ){
				if( wParam & BITMAP_DISABLED ){
					lResult = T::_IDB_256C_16_BW;
				}
				else if( wParam & BITMAP_HOT ){
					lResult = T::_IDB_256C_16_HOT;
				}
				else {
					lResult = T::_IDB_256C_16_DEFAULT;
				}
			}
			else {
				lResult = T::_IDB_BITMAP;
			}
		}
		return lResult;
	}
};


HINSTANCE EEGetInstanceHandle()
{
	_ASSERTE( _ETLData.m_hInstance != NULL );
	return _ETLData.m_hInstance;
}

WORD EEGetCmdID()
{
	_ASSERTE( _ETLData.m_wCmdID >= EEID_PLUG_IN1 );
	_ASSERTE( _ETLData.m_wCmdID <= EEID_PLUG_IN1 + 255 );
	return _ETLData.m_wCmdID;
}

CETLFrameX* GetFrameFromFrame( HWND hwndFrame )
{
	_ASSERTE( hwndFrame );
	_ASSERTE( IsWindow( hwndFrame ) );
	ASSERT_STRICT( _ETLData.m_pETLFrameMap != NULL );
	if( _ETLData.m_pETLFrameMap == NULL )  return NULL;
	CETLFrameX* pFrame = NULL;
	{
		CETLLock lock;
		CETLFrameMap::iterator it = _ETLData.m_pETLFrameMap->find( hwndFrame );
		ASSERT_STRICT( it != _ETLData.m_pETLFrameMap->end() );
		if( it != _ETLData.m_pETLFrameMap->end() ){
			pFrame = it->second;
			_ASSERTE( pFrame != NULL );
		}
	}
	return pFrame;
}

CETLFrameX* GetFrameFromView( HWND hwndView )
{
	_ASSERTE( hwndView );
	_ASSERTE( IsWindow( hwndView ) );
	HWND hwndFrame = GetParent( hwndView );
	ASSERT_STRICT( hwndFrame );
	if( hwndFrame == NULL )  return NULL;
	return GetFrameFromFrame( hwndFrame );
}

CETLFrameX* GetFrameFromDlg( HWND hwnd )
{
	HWND hwndParent = GetParent( hwnd );
// hwndParent can be hwndFrame or hwndView
	CETLFrameX* pFrame = GetFrameFromFrame( hwndParent );
	if( pFrame == NULL ){
		pFrame = GetFrameFromView( hwndParent );
	}
	_ASSERTE( pFrame );
	return pFrame;
}

void DeleteAllFrames()
{
	for( CETLFrameMap::iterator it = _ETLData.m_pETLFrameMap->begin(); it != _ETLData.m_pETLFrameMap->end(); it++ ){
		CETLFrameX* pFrame = it->second;
		delete pFrame;
	}
	_ETLData.m_pETLFrameMap->clear();
}

BOOL APIENTRY DllMain( HINSTANCE hModule, DWORD  ul_reason_for_call, LPVOID /*lpReserved*/ )
{
    if( ul_reason_for_call == DLL_PROCESS_ATTACH ){
#ifdef _DEBUG
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF );
#endif
		_ASSERTE( _ETLData.m_hInstance == NULL );
		_ETLData.m_hInstance = hModule;
	}
	else if( ul_reason_for_call == DLL_PROCESS_DETACH ){
		_ASSERTE( _ETLData.m_pETLFrameMap == NULL );
	}
    return TRUE;
}

extern "C" void __stdcall OnCommand( HWND hwndView )
{
	CETLFrameX* pFrame = GetFrameFromView( hwndView );
	pFrame->OnCommand( hwndView );
}


extern "C" BOOL __stdcall QueryStatus( HWND hwndView, LPBOOL pbChecked )
{
	CETLFrameX* pFrame = GetFrameFromView( hwndView );
	if( pFrame == NULL )  return FALSE;
	return pFrame->QueryStatus( hwndView, pbChecked );
}

extern "C" UINT __stdcall GetMenuTextID()
{
	return CETLFrameX::GetMenuTextID();
}

extern "C" UINT __stdcall GetStatusMessageID()
{
	return CETLFrameX::GetStatusMessageID();
}

extern "C" UINT __stdcall GetBitmapID()
{
	return CETLFrameX::GetBitmapID();
}


extern "C" void __stdcall OnEvents( HWND hwndView, UINT nEvent, LPARAM lParam )
{
	HWND hwndFrame = NULL;
	if( nEvent != EVENT_CLOSE ){
		_ASSERTE( hwndView );
		hwndFrame = GetParent( hwndView );
		_ASSERTE( hwndFrame );
	}
	if( nEvent & EVENT_CREATE ){
		_ASSERTE( (UINT)lParam >= EEID_PLUG_IN1 && (UINT)lParam <= EEID_PLUG_IN1 + 255 );
		_ASSERTE( _ETLData.m_wCmdID == 0 );
		_ASSERTE( _ETLData.m_pETLFrameMap == NULL );
		_ETLData.m_wCmdID = LOWORD( lParam );
		_ETLData.m_pETLFrameMap = new CETLFrameMap;
		if( Editor_GetVersion( hwndView ) < 5000 ){   // previous versions of EmEditor do not fire EVENT_CREATE_FRAME.
			OnEvents( hwndView, EVENT_CREATE_FRAME, lParam );
		}
	}
	else {
		ASSERT_STRICT( _ETLData.m_pETLFrameMap != NULL );
		if( _ETLData.m_pETLFrameMap != NULL ){
			if( nEvent & EVENT_CREATE_FRAME ){
				_ASSERTE( _ETLData.m_wCmdID == LOWORD( lParam ) );
				CETLFrameX* pFrame = static_cast<CETLFrameX*>(_ETLCreateFrame());
				pFrame->m_hWnd = hwndFrame;
				{
					CETLLock lock;
					_ASSERTE( _ETLData.m_pETLFrameMap->find( hwndFrame ) == _ETLData.m_pETLFrameMap->end() );
					_ETLData.m_pETLFrameMap->insert( std::pair<HWND, CETLFrameX*>( hwndFrame, pFrame ) );
					pFrame->OnEvents( hwndView, nEvent );
				}
			}
			else if( nEvent & EVENT_CLOSE_FRAME ){
				CETLFrameX* pFrame;
				{
					CETLLock lock;
					CETLFrameMap::iterator it = _ETLData.m_pETLFrameMap->find( hwndFrame );
					_ASSERTE( it != _ETLData.m_pETLFrameMap->end() );
					pFrame = it->second;
					_ETLData.m_pETLFrameMap->erase( it );
				}
				pFrame->OnEvents( hwndView, nEvent );
				_ETLDeleteFrame( pFrame );
			}
			else if( nEvent & EVENT_CLOSE ){
				ASSERT_STRICT( _ETLData.m_pETLFrameMap->empty() );
				DeleteAllFrames();  // previous versions of EmEditor do not fire EVENT_CLOSE_FRAME.
				delete _ETLData.m_pETLFrameMap;
				_ETLData.m_pETLFrameMap = NULL;
				_ETLData.m_wCmdID = 0;
			}
			else {
				CETLFrameX* pFrame;
				{
					CETLLock lock;
					CETLFrameMap::iterator it = _ETLData.m_pETLFrameMap->find( hwndFrame );
					_ASSERTE( it != _ETLData.m_pETLFrameMap->end() );
					pFrame = it->second;
				}
				pFrame->OnEvents( hwndView, nEvent );
			}
		}
	}
}


extern "C" LRESULT __stdcall PlugInProc( HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam )
{
	// hwnd can be either view handle, frame handle, or plug-ins settings dialog handle.
	LRESULT lResult = 0;
	switch( nMsg ){
	case EP_GET_BITMAP:
		lResult = CETLFrameX::GetBitmap( wParam );
		break;
	case EP_GET_MASK:
		lResult = CETLFrameX::GetMask( wParam );
		break;
	case EP_GET_NAMEA:
		lResult = CETLFrameX::GetNameA( (LPSTR)lParam, (size_t)wParam );
		break;
	case EP_GET_NAMEW:
		lResult = CETLFrameX::GetNameW( (LPWSTR)lParam, (size_t)wParam );
		break;
	case EP_GET_VERSIONA:
		lResult = CETLFrameX::GetVersionA( (LPSTR)lParam, (size_t)wParam );
		break;
	case EP_GET_VERSIONW:
		lResult = CETLFrameX::GetVersionW( (LPWSTR)lParam, (size_t)wParam );
		break;
	case EP_GET_INFO:
		lResult = CETLFrameX::GetInfo( wParam );
		break;
	default:
		{
			// hwnd is plug-ins settings dialog handle or view window handle.
			// GetParent( hwnd ) is always Frame window handle.
			CETLFrameX* pFrame = GetFrameFromView( hwnd );
			lResult = pFrame->PlugInProc( hwnd, nMsg, wParam, lParam );
		}
		break;
	}
	return lResult;
}


