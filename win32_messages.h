
#define WINDOW_MESSAGE_DEFINITION (PAINT,               Paint,			     0, ())
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (NCPAINT,             NCPaint,             1, (HRGN))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (PRINTCLIENT,         PrintClient,         2, (HDC, DWORD))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (WINDOWPOSCHANGING,   WindowPosChanging,   1, (LPWINDOWPOS))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (WINDOWPOSCHANGED,    WindowPosChanged,    1, (const LPWINDOWPOS))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (SIZE,                Size,                3, (UINT, int, int))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (COMMAND,             Command,             3, (int, HWND, UINT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (NCCREATE,            NCCreate,            1, (LPCREATESTRUCT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (CREATE,              Create,              1, (LPCREATESTRUCT))
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (DESTROY,             Destroy,			 0, ())
#include "win32_message_define.h"

#define WINDOW_MESSAGE_DEFINITION (NCDESTROY,           NCDestroy,			 0, ())
#include "win32_message_define.h"
