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
#ifndef WIN32_WINDOW_NAMESPACE
#error WIN32_WINDOW_NAMESPACE must be defined
#endif

namespace WIN32_WINDOW_NAMESPACE
{

	namespace detail
	{

		template<typename T>
		struct raw_ptr
		{
			explicit raw_ptr(T* raw) : raw(raw) {}
			operator typename cmn::unspecified_bool<raw_ptr>::type () { return cmn::unspecified_bool<raw_ptr>::get(!!raw); }
			T* operator ->() { return raw; }
			T* raw;
		};
	}

	template<typename WindowClassTag>
	//static
	ATOM window_class<WindowClassTag>::Register()
	{
		WNDCLASSEX wcex = {};
		wcex.cbSize = sizeof(WNDCLASSEX);

		// defaults that can be overriden
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.hInstance = GetCurrentInstance();
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

		window_class_register(&wcex, tag());

		// not overridable
		wcex.lpfnWndProc = WindowCallback<WindowClassTag>;

		return RegisterClassEx(&wcex);
	}

	template<typename WindowClassTag>
	template<typename T>
	//static
	ATOM window_class<WindowClassTag>::Register(T&& t)
	{
		WNDCLASSEX wcex = {};
		wcex.cbSize = sizeof(WNDCLASSEX);

		// defaults that can be overriden
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.hInstance = cmn::GetCurrentInstance();
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

		window_class_register(std::forward<T>(t), &wcex, tag());

		// not overridable
		wcex.lpfnWndProc = WindowCallback<WindowClassTag>;

		return RegisterClassEx(&wcex);
	}

	template<typename WindowClassTag>
	struct Context
	{
		HWND window;
		UINT message;
		WPARAM wParam;
		LPARAM lParam;
	};

 	template<typename WindowClassTag> 
	std::unique_ptr<typename window_class<WindowClassTag>::traits::type> 
	optional_window_class_constructor(HWND hwnd, LPCREATESTRUCT createStruct, decltype(new (std::nothrow) window_class<WindowClassTag>::traits::type(cmn::instance_of<HWND>::value, cmn::instance_of<CREATESTRUCT>::value)))
	{ 
		typedef
			typename window_class<WindowClassTag>::traits::type
		Type;

		std::unique_ptr<Type> type(new (std::nothrow) Type(hwnd, *createStruct));

		return std::move(type);
	} 

	template<typename WindowClassTag> 
	std::unique_ptr<typename window_class<WindowClassTag>::traits::type> 
	optional_window_class_constructor(HWND , LPCREATESTRUCT , ...) 
	{ 
		typedef
			typename window_class<WindowClassTag>::traits::type
		Type;

		std::unique_ptr<Type> type(new (std::nothrow) Type);

		return std::move(type);
	}

	template<typename WindowClassTag> 
	decltype(
		window_class_construct(
			cmn::instance_of<HWND>::value, 
			cmn::instance_of<LPCREATESTRUCT>::value, 
			WindowClassTag())) 
	optional_window_class_construct(HWND hwnd, LPCREATESTRUCT createStruct, WindowClassTag&&, int)
	{ 
		return window_class_construct(hwnd, createStruct, WindowClassTag());
	} 

 	template<typename WindowClassTag> 
	std::unique_ptr<typename window_class<WindowClassTag>::traits::type> 
	optional_window_class_construct(HWND hwnd, LPCREATESTRUCT createStruct, WindowClassTag&&, ...) 
	{ 
		return optional_window_class_constructor<WindowClassTag>(hwnd, createStruct, 0);
	}

	template<typename WindowClassTag, typename T> 
	decltype(
		window_class_insert(
			cmn::instance_of<HWND>::value, 
			WindowClassTag())) 
	optional_window_class_insert(HWND hwnd, T t, WindowClassTag&&, int) 
	{ 
		return window_class_insert(hwnd, std::move(t), WindowClassTag());
	} 

 	template<typename WindowClassTag> 
	bool optional_window_class_insert(
		HWND hwnd, 
		std::unique_ptr<typename window_class<WindowClassTag>::traits::type> type, 
		WindowClassTag&&, 
		...) 
	{ 
		if (!type)
		{
			return false;
		}

		SetLastError(0);

		auto result = SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(type.get()));
		unique_winerror winerror = make_winerror_if(!result);

		ON_UNWIND(UserDataUnwind, [&]{SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);});

		if (!winerror)
		{
			return false;
		}

		if (!!result)
		{
			return false;
		}

		type.release();
		UserDataUnwind.dismiss();
		return true;
	}

 	template<typename WindowClassTag> 
	decltype(
		window_class_find(
			cmn::instance_of<HWND>::value, 
			WindowClassTag())) 
	optional_window_class_find(HWND hwnd, WindowClassTag&&, int)
	{ 
		return window_class_find(hwnd, WindowClassTag());
	} 

 	template<typename WindowClassTag> 
	detail::raw_ptr<typename window_class<WindowClassTag>::traits::type> 
	optional_window_class_find(HWND hwnd, WindowClassTag&&, ...) 
	{ 
		typedef
			typename window_class<WindowClassTag>::traits::type
		type;
		return detail::raw_ptr<type>(reinterpret_cast<type*>(GetWindowLongPtr(hwnd, GWLP_USERDATA)));
	}

 	template<typename Type, typename WindowClassTag> 
	decltype(
		window_class_erase(
			cmn::instance_of<HWND>::value, 
			cmn::instance_of<Type>::value, 
			WindowClassTag())) 
	optional_window_class_erase(HWND hwnd, Type type, WindowClassTag&&, int) 
	{ 
		return window_class_erase(hwnd, type, WindowClassTag());
	} 

 	template<typename Type, typename WindowClassTag> 
	void optional_window_class_erase(HWND hwnd, detail::raw_ptr<Type> , WindowClassTag&&, ...) 
	{ 
		SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
	}

	template<typename Type, typename WindowClassTag> 
	decltype(
		window_class_destroy(
			cmn::instance_of<HWND>::value, 
			cmn::instance_of<Type>::value, 
			WindowClassTag())) 
	optional_window_class_destroy(HWND hwnd, Type type, WindowClassTag&&, int) 
	{ 
		return window_class_destroy(hwnd, type, WindowClassTag());
	} 

 	template<typename Type, typename WindowClassTag> 
	void optional_window_class_destroy(HWND , detail::raw_ptr<Type> type, WindowClassTag&&, ...) 
	{ 
		delete type.raw;
	}

    template<typename Type, typename WindowClassTag> 
	decltype(
		window_class_dispatch(
			cmn::instance_of<Type>::value, 
            cmn::instance_of<Context<WindowClassTag>>::value,
			WindowClassTag())) 
	optional_window_class_dispatch(Type type, const Context<WindowClassTag>& context, WindowClassTag&&, int) 
	{ 
        return window_message_error_contract(
            [type] (const Context<WindowClassTag>& context) 
            {
                return window_class_dispatch(type, context, WindowClassTag());
            },
            context,
            WindowClassTag()
        );
	} 
    
    typedef std::pair<bool, LRESULT> dispatch_result;

    template<typename Type, typename WindowClassTag> 
	dispatch_result optional_window_class_dispatch(detail::raw_ptr<Type> type, const Context<WindowClassTag>& context, WindowClassTag&&, ...) 
	{ 
        return window_message_error_contract(
            [type] (const Context<WindowClassTag>& context) 
            {
                return type->window_proc(context.window, context.message, context.wParam, context.LParam);
            },
            context,
            WindowClassTag()
        );
	}

	namespace detail
	{
		template<typename WindowClassTag>
		LRESULT CALLBACK WindowCallbackSafe(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			bool handled = false;
			LRESULT result = 0;

			if (message == WM_NCCREATE)
			{
				auto existingType = optional_window_class_find(hWnd, WindowClassTag(), 0);
				if  (existingType)
				{
                    // the slot where we would store our type instance is full. abort.
                    return FALSE;
                }
				if (!optional_window_class_insert(
						hWnd, 
						optional_window_class_construct(
							hWnd, 
							reinterpret_cast<LPCREATESTRUCT>(lParam), 
							WindowClassTag(), 
							0
						),
						WindowClassTag(), 
						0
					)
				)
				{
					return FALSE;
				}
			}

			auto type = optional_window_class_find(hWnd, WindowClassTag(), 0);

			ON_UNWIND_AUTO(
				[&]
				{
					if (type && message == WM_NCDESTROY)
					{
						optional_window_class_erase(hWnd, type, WindowClassTag(), 0);
						optional_window_class_destroy(hWnd, type, WindowClassTag(), 0);
					}
				}
			);

			if (type)
			{
				Context<WindowClassTag> context = {hWnd, message, wParam, lParam};

				std::tie(handled, result) = optional_window_class_dispatch(type, context, WindowClassTag(), 0);
				if (handled)
				{
					return result;
				}
			}

			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	template<typename WindowClassTag>
	LRESULT CALLBACK WindowCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		__try
		{
			return detail::WindowCallbackSafe<WindowClassTag>(hWnd, message, wParam, lParam);
		}
		__except(cmn::FailFastFilter(GetExceptionInformation()))
		{
		}
		return 0;
	}

}
