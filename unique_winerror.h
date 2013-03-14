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
#ifndef UNIQUE_WINERROR_SOURCE
#define UNIQUE_WINERROR_SOURCE

namespace unique_winerror_def
{
	struct tag {};

	inline bool unique_error_ok(DWORD winerror, tag&&)
	{
		return winerror == ERROR_SUCCESS;
	}

	inline DWORD unique_error_default(tag&&)
	{
		return ERROR_SUCCESS;
	}
}

// 
//
// implementations of these must be included in the final module
//
void unique_error_report_initiated(DWORD value, unique_winerror_def::tag&&);
void unique_error_report_reset(DWORD value, unique_winerror_def::tag&&);

typedef
	UNIQUE_ERROR_NAMESPACE::unique_error<unique_winerror_def::tag>
unique_winerror;

inline unique_winerror make_winerror_if(BOOL is_last_error)
{
	unique_winerror result;
	if (is_last_error)
	{
		return std::move(result.reset(GetLastError()));
	}
	return std::move(result);
}

inline unique_winerror::static_error winerror_cast(DWORD raw)
{
	return unique_winerror::cast(raw);
}

#endif // UNIQUE_WINERROR_SOURCE

#ifdef UNIQUE_WINERROR_DEFINE_REPORTS
void unique_error_report_initiated(DWORD value, unique_winerror_def::tag&&)
{
	static DWORD anchor;
	anchor = value;
}

void unique_error_report_reset(DWORD value, unique_winerror_def::tag&&)
{
	static DWORD anchor;
	anchor = value;
}
#endif
