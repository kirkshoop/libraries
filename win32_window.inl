
#ifndef WIN32_WINDOW_NAMESPACE
#error WIN32_WINDOW_NAMESPACE must be defined
#endif

// missing from windowsx.h
#ifndef HANDLE_WM_PRINTCLIENT
/* void Cls_OnPrintClient(HWND hwnd, HDC hdc, DWORD flags) */
#define HANDLE_WM_PRINTCLIENT(hwnd, wParam, lParam, fn) \
    ((fn)(hwnd, (HDC)(wParam), (DWORD)(lParam)), 0L)
#define FORWARD_WM_PRINTCLIENT(hwnd, hdc, flags, fn) \
    (void)(fn)((hwnd), WM_PRINTCLIENT, (WPARAM)(HDC)(hdc), (LPARAM)(DWORD)(flags))
#endif

namespace WIN32_WINDOW_NAMESPACE
{

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
		wcex.lpfnWndProc = WindowCallback;

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
		wcex.lpfnWndProc = WindowCallback;

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

	struct nohandler
	{
		inline
		LRESULT operator()(...)
		{
			return 0;
		}
	};

namespace msg
{
#	define WINDOW_MESSAGE_DEFINE_OPTIONAL
#	include "win32_messages.h"
#	undef WINDOW_MESSAGE_DEFINE_OPTIONAL

	template<typename WindowClassTag, typename Target>
	std::pair<bool, LRESULT> dispatch(Target target, const Context<WindowClassTag>& context)
	{
		BOOL handled = FALSE;
		LRESULT result = 0;

#		define WINDOW_MESSAGE_DEFINE_DISPATCH
#		include "win32_messages.h"
#		undef WINDOW_MESSAGE_DEFINE_DISPATCH

		return std::make_pair(!!handled, result);
	}
}

 	template<typename WindowClassTag> 
	auto optional_window_class_insert(HWND hwnd, WindowClassTag&&, int) -> decltype(window_class_insert(hwnd, WindowClassTag()))
	{ 
		return window_class_insert(hwnd, WindowClassTag());
	} 

 	template<typename WindowClassTag> 
	bool optional_window_class_insert(HWND hwnd, WindowClassTag&&, ...) 
	{ 
		typedef
			typename window_class<WindowClassTag>::traits::type
		Type;

		std::unique_ptr<Type> type(new (std::nothrow) Type);
		if (!type)
		{
			return false;
		}

		SetLastError(0);

		auto result = SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(type.get()));
		ON_UNWIND(UserDataUnwind, [&]{SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);});

		unique_winerror winerror = make_winerror_if(!result);

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
	auto optional_window_class_find(HWND hwnd, WindowClassTag&&, int) -> decltype(window_class_find(hwnd, WindowClassTag()))
	{ 
		return window_class_find(hwnd, WindowClassTag());
	} 

 	template<typename WindowClassTag> 
	typename window_class<WindowClassTag>::traits::type* optional_window_class_find(HWND hwnd, WindowClassTag&&, ...) 
	{ 
		return reinterpret_cast<typename window_class<WindowClassTag>::traits::type*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

 	template<typename Type, typename WindowClassTag> 
	auto optional_window_class_erase(HWND hwnd, Type* type, WindowClassTag&&, int) -> decltype(window_class_erase(hwnd, type, WindowClassTag()))
	{ 
		return window_class_erase(hwnd, type, WindowClassTag());
	} 

 	template<typename Type, typename WindowClassTag> 
	void optional_window_class_erase(HWND hwnd, Type* type, WindowClassTag&&, ...) 
	{ 
		SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
		delete type;
	}

	template<typename WindowClassTag>
	//static 
	LRESULT CALLBACK window_class<WindowClassTag>::WindowCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		__try
		{
			return WindowCallbackSafe(hWnd, message, wParam, lParam);
		}
		__except(cmn::FailFastFilter(GetExceptionInformation()))
		{
		}
		return 0;
	}

	template<typename WindowClassTag>
	//static 
	LRESULT CALLBACK window_class<WindowClassTag>::WindowCallbackSafe(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		bool handled = false;
		LRESULT result = 0;

		if (message == WM_NCCREATE)
		{
			if (!optional_window_class_insert(hWnd, WindowClassTag(), 0))
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
				}
			}
		);

		if (type)
		{
			Context<WindowClassTag> context = {hWnd, message, wParam, lParam};

			std::tie(handled, result) = msg::dispatch(type, context);
			if (handled)
			{
				return result;
			}
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}

}
