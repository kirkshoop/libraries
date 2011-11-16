
#define WINDOW_MESSAGE_DEFINITION (PAINT,               Paint,               0, ())
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (NCPAINT,             NCPaint,             1, (HRGN))
#include "win32_message_define.h"

// missing from windowsx.h
#ifndef HANDLE_WM_PRINTCLIENT
/* void Cls_OnPrintClient(HWND hwnd, HDC hdc, DWORD flags) */
#define HANDLE_WM_PRINTCLIENT(hwnd, wParam, lParam, fn) \
    ((fn)(hwnd, (HDC)(wParam), (DWORD)(lParam)), 0L)
#define FORWARD_WM_PRINTCLIENT(hwnd, hdc, flags, fn) \
    (void)(fn)((hwnd), WM_PRINTCLIENT, (WPARAM)(HDC)(hdc), (LPARAM)(DWORD)(flags))
#endif

#define WINDOW_MESSAGE_DEFINITION (PRINTCLIENT,         PrintClient,         2, (HDC, DWORD))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (WINDOWPOSCHANGING,   WindowPosChanging,   1, (LPWINDOWPOS))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (WINDOWPOSCHANGED,    WindowPosChanged,    1, (const WINDOWPOS*))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (SIZE,                Size,                3, (UINT, int, int))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (COMMAND,             Command,             3, (int, HWND, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (NCCREATE,            NCCreate,            1, (LPCREATESTRUCT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (CREATE,              Create,              1, (LPCREATESTRUCT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (DESTROY,             Destroy,             0, ())
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (NCDESTROY,           NCDestroy,           0, ())
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (QUIT,                Quit,                1, (int))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (SHOWWINDOW,          ShowWindow,          2, (BOOL, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (SETREDRAW,           SetRedraw,           1, (BOOL))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (ENABLE,              Enable,              1, (BOOL))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (SETTEXT,             SetText,             1, (LPCWSTR))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (GETTEXT,             GetText,             2, (int, LPWSTR))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (GETTEXTLENGTH,       GetTextLength,       0, ())
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (MOVE,                Move,                2, (int, int))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (CLOSE,               Close,               0, ())
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (QUERYOPEN,           QueryOpen,           0, ())
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (GETMINMAXINFO,       GetMinMaxInfo,       0, (LPMINMAXINFO))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (ERASEBKGND,          EraseBkgnd,          1, (HDC))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (ICONERASEBKGND,      IconEraseBkgnd,      1, (HDC))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (NCCALCSIZE,          NCCalcSize,          2, (BOOL, NCCALCSIZE_PARAMS*))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (NCHITTEST,           NCHitTest,           2, (int, int))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (QUERYDRAGICON,       QueryDragIcon,       0, ())
#include "win32_message_define.h"

#ifdef _INC_SHELLAPI
#define WINDOW_MESSAGE_DEFINITION (DROPFILES,           DropFiles,           1, (HDROP))
#include "win32_message_define.h"
#endif  /* _INC_SHELLAPI */

#define WINDOW_MESSAGE_DEFINITION (ACTIVATE,            Activate,            3, (UINT, HWND, BOOL))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (ACTIVATEAPP,         ActivateApp,         2, (BOOL, DWORD))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (NCACTIVATE,          NCActivate,          3, (BOOL, HWND, BOOL))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (SETFOCUS,            SetFocus,            1, (HWND))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (KILLFOCUS,           KillFocus,           1, (HWND))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (KEYDOWN,             KeyDown,             4, (UINT, BOOL, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (KEYUP,               KeyUp,               4, (UINT, BOOL, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (CHAR,                Char,                2, (WCHAR, int))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (DEADCHAR,            DeadChar,            2, (WCHAR, int))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (SYSKEYDOWN,          SysKeyDown,          4, (UINT, BOOL, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (SYSKEYUP,            SysKeyUp,            4, (UINT, BOOL, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (SYSCHAR,             SysChar,             2, (WCHAR, int))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (SYSDEADCHAR,         SysDeadChar,         2, (WCHAR, int))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (MOUSEMOVE,           MouseMove,           3, (int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (LBUTTONDOWN,         LButtonDown,         4, (BOOL, int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (LBUTTONDBLCLK,       LButtonDblClk,       4, (BOOL, int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (LBUTTONUP,           LButtonUp,           3, (int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (RBUTTONDOWN,         RButtonDown,         4, (BOOL, int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (RBUTTONDBLCLK,       RButtonDblClk,       4, (BOOL, int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (RBUTTONUP,           RButtonUp,           3, (int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (MBUTTONDOWN,         MButtonDown,         4, (BOOL, int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (MBUTTONDBLCLK,       MButtonDblClk,       4, (BOOL, int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (MBUTTONUP,           MButtonUp,           3, (int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (MOUSEWHEEL,          MouseWheel,          3, (int, int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (NCMOUSEMOVE,         NCMouseMove,         3, (int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (NCLBUTTONDOWN,       NCLButtonDown,       4, (BOOL, int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (NCLBUTTONDBLCLK,     NCLButtonDblClk,     4, (BOOL, int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (NCLBUTTONUP,         NCLButtonUp,         3, (int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (NCRBUTTONDOWN,       NCRButtonDown,       4, (BOOL, int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (NCRBUTTONDBLCLK,     NCRButtonDblClk,     4, (BOOL, int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (NCRBUTTONUP,         NCRButtonUp,         3, (int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (NCMBUTTONDOWN,       NCMButtonDown,       4, (BOOL, int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (NCMBUTTONDBLCLK,     NCMButtonDblClk,     4, (BOOL, int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (NCMBUTTONUP,         NCMButtonUp,         3, (int, int, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (MOUSEACTIVATE,       MouseActivate,       3, (HWND, UINT, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (CANCELMODE,          CancelMode,          0, ())
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (TIMER,               Timer,               1, (UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (INITMENU,            InitMenu,            1, (HMENU))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (INITMENUPOPUP,       InitMenuPopUp,       3, (HMENU, UINT, BOOL))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (MENUSELECT,          MenuSelect,          4, (HMENU, int, HMENU, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (MENUCHAR,            MenuChar,            3, (UINT, UINT, HMENU))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (HSCROLL,             HScroll,             3, (HWND, UINT, int))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (VSCROLL,             VScroll,             3, (HWND, UINT, int))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (CUT,                 Cut,                 0, ())
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (COPY,                Copy,                0, ())
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (PASTE,               Paste,               0, ())
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (CLEAR,               Clear,               0, ())
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (UNDO,                Undo,                0, ())
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (RENDERFORMAT,        RenderFormat,        1, (UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (RENDERALLFORMATS,    RenderAllFormats,    0, ())
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (DESTROYCLIPBOARD,    DestroyClipboard,    0, ())
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (DRAWCLIPBOARD,       DrawClipboard,       0, ())
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (PAINTCLIPBOARD,      PaintClipboard,      2, (HWND, LPPAINTSTRUCT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (SIZECLIPBOARD,       SizeClipboard,       2, (HWND, LPRECT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (VSCROLLCLIPBOARD,    VScrollClipboard,    3, (HWND, UINT, int))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (HSCROLLCLIPBOARD,    HScrollClipboard,    3, (HWND, UINT, int))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (ASKCBFORMATNAME,     AskCBFormatName,     2, (int, LPWSTR))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (CHANGECBCHAIN,       ChangeCBChain,       2, (HWND, HWND))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (SETCURSOR,           SetCursor,           3, (HWND, UINT, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (SYSCOMMAND,          SysCommand,          3, (UINT, int, int))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (CHILDACTIVATE,       ChildActivate,       0, ())
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (SETFONT,             SetFont,             2, (HFONT, BOOL))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (GETFONT,             GetFont,             0, ())
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (CONTEXTMENU,         ContextMenu,         3, (HWND, UINT, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (COPYDATA,            CopyData,            2, (HWND, PCOPYDATASTRUCT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (DISPLAYCHANGE,       DisplayChange,       3, (UINT, UINT, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (DEVICECHANGE,        DeviceChange,        2, (UINT, DWORD))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (HOTKEY,              HotKey,              3, (int, UINT, UINT))
#include "win32_message_define.h"


