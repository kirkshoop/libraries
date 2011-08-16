
#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
// Windows Header Files:
#include <windows.h>
#include <winerror.h>
#include <WindowsX.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <new>
#include <memory>
#include <utility>
#include <iterator>
#include <exception>
#include <unordered_map>

#define COMMON_NAMESPACE nscommon
#include "common.h"

#define RANGE_NAMESPACE nsrange
#include "range.h"
namespace rg=RANGE_NAMESPACE;

#define UNWINDER_NAMESPACE nsunwinder
#include "unwinder.h"

#define UNIQUE_ERROR_NAMESPACE nsunqerr
#include "unique_error.h"
#include "unique_winerror.h"

#define UNIQUE_RESOURCE_NAMESPACE nsunqrsrc
#include "unique_resource.h"

#define WINDOWS_RESOURCES_NAMESPACE nswinrsrc
#include "windows_resources.h"
namespace wr=WINDOWS_RESOURCES_NAMESPACE;

#define WIN32_WINDOW_NAMESPACE nswin32window
#include "win32_window.h"
namespace win=WIN32_WINDOW_NAMESPACE;
