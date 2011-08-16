
#ifndef LIBRARIES_SOURCE
#define LIBRARIES_SOURCE

#define COMMON_NAMESPACE nscommon
#include "common.h"

#define RANGE_NAMESPACE nsrange
#include "range.h"

#define UNWINDER_NAMESPACE nsunwinder
#include "unwinder.h"

#define UNIQUE_ERROR_NAMESPACE nsunqerr
#include "unique_error.h"
#include "unique_winerror.h"
#include "unique_hresult.h"

#define UNIQUE_RESOURCE_NAMESPACE nsunqrsrc
#include "unique_resource.h"

#define WINDOWS_RESOURCES_NAMESPACE nswinrsrc
#include "windows_resources.h"

#define WIN32_WINDOW_NAMESPACE nswin32window
#include "win32_window.h"

#ifndef LIBRARIES_NAMESPACE
#error LIBRARIES_NAMESPACE must be defined
#endif

namespace LIBRARIES_NAMESPACE
{
	using namespace COMMON_NAMESPACE;
	using namespace RANGE_NAMESPACE;
	using namespace UNIQUE_ERROR_NAMESPACE;
	using namespace UNIQUE_RESOURCE_NAMESPACE;
	using namespace WINDOWS_RESOURCES_NAMESPACE;
	using namespace WIN32_WINDOW_NAMESPACE;
}

#endif // LIBRARIES_SOURCE
