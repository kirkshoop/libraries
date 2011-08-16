
#ifndef WIN32_WINDOW_NAMESPACE
#error WIN32_WINDOW_NAMESPACE must be defined
#endif


namespace WIN32_WINDOW_NAMESPACE
{

	template<typename WindowClassTag>
	//static
	ATOM window_class<WindowClassTag>::Register()
	{
		use_types<hwndToTypes>();

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
		use_types<hwndToTypes>();

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
		std::shared_ptr<Type> type;
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
		template<TPLT_TEMPLATE_ARGUMENTS(ParamCount, Param)> \
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

#include "win32_messages.h"

#undef WINDOW_MESSAGE_OPTIONAL

	template<typename WindowClassTag>
	template<typename Instance>
	// static 
	typename Instance& window_class<WindowClassTag>::use_types()
	{
		static Instance instance;
		return instance;
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

		auto& types = use_types<hwndToTypes>();

		if (message == WM_NCCREATE)
		{
			try
			{
				types.insert(std::make_pair(hWnd, std::make_shared<traits::type>()));
			}
			catch(const std::bad_alloc&)
			{
				return FALSE;
			}
		}

		auto type = types.find(hWnd);

		if (type != types.end())
		{
			Context<traits::type> context = {type->second, hWnd, message, wParam, lParam, &handled, &result};

#			define WINDOW_MESSAGE_OPTIONAL( CapitalMessage, CasedMessage, ParamCount, ...) \
						HANDLE_WM_ ## CapitalMessage(hWnd, wParam, lParam, optional ## CasedMessage(&context, 0));

#			include "win32_messages.h"

#			undef WINDOW_MESSAGE_OPTIONAL

			if (message == WM_NCDESTROY)
			{
				types.erase(type);
			}

			if (handled)
			{
				return result;
			}
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}

}
