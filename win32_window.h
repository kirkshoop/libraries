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
#ifndef WIN32_WINDOW_SOURCE
#define WIN32_WINDOW_SOURCE

#ifndef WIN32_WINDOW_NAMESPACE
#error WIN32_WINDOW_NAMESPACE must be defined
#endif

namespace WIN32_WINDOW_NAMESPACE
{
	namespace cmn=COMMON_NAMESPACE;

	template<typename Type>
	struct traits_builder
	{
		typedef
			Type
		type;
	};

	template<typename WindowClassTag>
	struct traits
	{
		typedef
			decltype(window_class_traits(WindowClassTag()))
		type;
	};

	template<typename WindowClassTag>
	LRESULT CALLBACK WindowCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	template<typename WindowClassTag>
	class window_class
	{
	public:
		typedef 
			WindowClassTag
		tag;

		typedef
			typename traits<tag>::type
		traits;

		static ATOM Register();

		template<typename T>
		static ATOM Register(T&& t);

	private:
		~window_class();
		window_class();
		window_class(window_class&);
		window_class& operator=(window_class&);
	};

	template<typename WindowSubclassTag>
	LRESULT CALLBACK WindowSubclassCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

	template<typename WindowSubclassTag>
	WINDOWS_RESOURCES_NAMESPACE::unique_remove_window_subclass set_window_subclass(HWND window, INT_PTR id = 0L, DWORD_PTR data = 0L);
}

#include "win32_window.inl"

#endif //WIN32_WINDOW_SOURCE