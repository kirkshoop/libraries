
#ifndef LIBRARIES_SOURCE
#define LIBRARIES_SOURCE

#define COMMON_NAMESPACE nscommon
#include "common.h"

#define TYPE_VECTOR_NAMESPACE nstypvec
#include "type_vector.h"

#define ONE_OF_NAMESPACE nsoneof
#include "one_of.h"

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

#define INTERFACE_SET_NAMESPACE nsintset
#include "interface_set.h"

#ifndef LIBRARIES_VC11_ICE
#define WINDOWS_RESOURCES_NAMESPACE nswinrsrc
#include "windows_resources.h"

#define COM_NAMESPACE nscom
#include "com_unknown.h"

#define WIN32_WINDOW_NAMESPACE nswin32window
#include "win32_window.h"
#endif

#ifndef LIBRARIES_NAMESPACE
#error LIBRARIES_NAMESPACE must be defined
#endif

namespace LIBRARIES_NAMESPACE
{
	namespace cmn=COMMON_NAMESPACE;
	namespace rng=RANGE_NAMESPACE;
	namespace tv=TYPE_VECTOR_NAMESPACE;
	namespace of=ONE_OF_NAMESPACE;
	namespace ifset=INTERFACE_SET_NAMESPACE;
#ifndef LIBRARIES_VC11_ICE
	namespace wr=WINDOWS_RESOURCES_NAMESPACE;
	namespace wnd=WIN32_WINDOW_NAMESPACE;
	namespace com=COM_NAMESPACE;
#endif
}

#endif // LIBRARIES_SOURCE
