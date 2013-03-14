// Copyright (c) 2013, Kirk Shoop (kirk.shoop@gmail.com)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, 
//  are permitted provided that the following conditions are met:
//
//  - Redistributions of source code must retain the above copyright notice, 
//      this list of conditions and the following disclaimer.
//  - Redistributions in binary form must reproduce the above copyright notice, 
//      this list of conditions and the following disclaimer in the documentation 
//      and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
// USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
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

#define WINDOWS_RESOURCES_NAMESPACE nswinrsrc
#include "windows_resources.h"

#define COM_NAMESPACE nscom
#include "com_unknown.h"
#include "com_classfactory.h"

#define WIN32_WINDOW_NAMESPACE nswin32window
#include "win32_window.h"


#ifndef LIBRARIES_NAMESPACE
#error LIBRARIES_NAMESPACE must be defined
#endif

namespace LIBRARIES_NAMESPACE
{
	namespace cmn=COMMON_NAMESPACE;
	namespace rng=RANGE_NAMESPACE;
	namespace tv=TYPE_VECTOR_NAMESPACE;
	namespace of=ONE_OF_NAMESPACE;
	namespace ur=UNIQUE_RESOURCE_NAMESPACE;
	namespace ifset=INTERFACE_SET_NAMESPACE;
	namespace wr=WINDOWS_RESOURCES_NAMESPACE;
	namespace wnd=WIN32_WINDOW_NAMESPACE;
	namespace com=COM_NAMESPACE;
}

#endif // LIBRARIES_SOURCE
