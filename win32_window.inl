
#ifndef WIN32_WINDOW_NAMESPACE
#error WIN32_WINDOW_NAMESPACE must be defined
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
		wcex.hInstance = GetCurrentInstance();
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

		window_class_register(std::forward<T>(t), &wcex, tag());

		// not overridable
		wcex.lpfnWndProc = WindowCallback;

		return RegisterClassEx(&wcex);
	}

	template<typename Type>
	struct Context
	{
		Type* type;
		HWND window;
		UINT message;
		WPARAM wParam;
		LPARAM lParam;
		BOOL* handled;
		LRESULT* result;
	};

	struct nohandler
	{
		inline
		LRESULT operator()(...)
		{
			return 0;
		}
	};


#define WINDOW_MESSAGE_OPTIONAL( CapitalMessage, CasedMessage, ParamCount, ...) \
	template<typename Type> \
	struct optional ## CasedMessage ## Choice \
	{ \
		optional ## CasedMessage ## Choice(Context<Type>* contextArg) \
			: context(contextArg) \
		{ } \
 \
		template<TPLT_TEMPLATE_ARGUMENTS_DECL(ParamCount, Param)> \
		LRESULT operator()(TPLT_FUNCTION_ARGUMENTS_DECL(ParamCount, Param, , &&)) \
		{ \
			if (context->message == WM_ ## CapitalMessage) \
			{ \
				*context->handled = TRUE; \
				*context->result = context->type->On ## CasedMessage (const_cast<const Context<Type>*>(context), TPLT_FUNCTION_ARGUMENTS_CAST(ParamCount, Param, std::forward)); \
			} \
			return 0; \
		} \
 \
		Context<Type>* context; \
	}; \
 \
 	template<typename Type> \
	optional ## CasedMessage ## Choice<Type> optional ## CasedMessage(Context<Type>* context, decltype(instance_of<Type>::value.On ## CasedMessage (instance_of<Context<Type>*>::value, TPLT_FUNCTION_ARGUMENT_INSTANCES(ParamCount, __VA_ARGS__))) ) \
	{ \
		return optional ## CasedMessage ## Choice<Type>(context); \
	} \
 \
	inline nohandler optional ## CasedMessage (...) \
	{ \
		return nohandler(); \
	}

#pragma warning(push)
#pragma warning( disable : 4003) //not enough actual parameters for macro
#include "win32_messages.h"
#pragma warning (pop)

#undef WINDOW_MESSAGE_OPTIONAL

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
		ON_UNWIND(UserDataUnwind, [&]{SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));});

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
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));
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
		__except(FailFastFilter(GetExceptionInformation()))
		{
		}
		return 0;
	}

	template<typename WindowClassTag>
	//static 
	LRESULT CALLBACK window_class<WindowClassTag>::WindowCallbackSafe(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		LRESULT result = 0;
		BOOL handled = FALSE;

		if (message == WM_NCCREATE)
		{
			if (!optional_window_class_insert(hWnd, tag(), 0))
			{
				return FALSE;
			}
		}

		auto type = optional_window_class_find(hWnd, tag(), 0);

		if (type)
		{
			Context<traits::type> context = {type, hWnd, message, wParam, lParam, &handled, &result};

#			define WINDOW_MESSAGE_OPTIONAL( CapitalMessage, CasedMessage, ParamCount, ...) \
						HANDLE_WM_ ## CapitalMessage(hWnd, wParam, lParam, optional ## CasedMessage(&context, 0));

#			include "win32_messages.h"

#			undef WINDOW_MESSAGE_OPTIONAL

			if (message == WM_NCDESTROY)
			{
				optional_window_class_erase(hWnd, type, tag(), 0);
			}

			if (handled)
			{
				return result;
			}
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}

}
