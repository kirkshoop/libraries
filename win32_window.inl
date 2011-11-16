
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

namespace msg
{
	namespace detail
	{
		struct nohandler
		{
			inline
			LRESULT operator()(...)
			{
				return 0;
			}

			std::pair<bool, LRESULT> dispatch()
			{
				return std::make_pair(false, 0);
			}
		};
	}

	struct UnhandledTag {};

	template<typename WindowClassTag, typename Target>
	std::pair<bool, LRESULT> optionalUnhandled(
		Target target, 
		const Context<WindowClassTag>& context, 
		decltype(
			cmn::instance_of<Target>::value->OnUnhandled(
				cmn::instance_of<Context<WindowClassTag>>::value 
			)
		) 
	)
	{
		LRESULT result = 0;
		window_message_error_contract(
			[&]
			{
				result = target->OnUnhandled(context);
			},
			context,
			UnhandledTag(),
			WindowClassTag()
		);
		return std::make_pair(true, result);
	}

	inline std::pair<bool, LRESULT> optionalUnhandled(...)
	{
		return std::make_pair(false, 0);
	}

	template<typename WindowClassTag, typename Target>
	struct base
	{
		typedef
			base
		type;

		~base() {}
		base(Target targetArg, const Context<WindowClassTag>* contextArg, BOOL* handledArg, LRESULT* resultArg)
			: target(targetArg)
			, context(contextArg)
			, handled(handledArg)
			, result(resultArg)
		{}
		base(base&& other)
			: target(std::move(other.target))
			, context(std::move(other.context))
			, handled(std::move(other.handled))
			, result(std::move(other.result))
		{}
		base& operator=(base other)
		{
			using std::swap;
			swap(other.target, target);
			swap(other.context, context);
			swap(other.handled, handled);
			swap(other.result, result);
		}

		std::pair<bool, LRESULT> dispatch()
		{
			std::tie(*handled, *result) = optionalUnhandled(target, *context);
			return std::make_pair(*handled ? true : false, *result);
		}

		Target target;
		const Context<WindowClassTag>* context;
		BOOL* handled;
		LRESULT* result;
	};

#	define WINDOW_MESSAGE_DEFINE_OPTIONAL
#	include "win32_messages.h"
#	undef WINDOW_MESSAGE_DEFINE_OPTIONAL

	namespace detail
	{
		template<typename WindowClassTag, typename Target, typename MessageChoice, typename Base = base<WindowClassTag, Target>>
		struct generator;

		template<typename WindowClassTag, typename Target, template<typename A, typename B, typename C> class MessageChoice, typename Base>
		struct generator<WindowClassTag, Target, MessageChoice<WindowClassTag, Target, base<WindowClassTag, Target>>, Base>
			: public Base
		{
			typedef
				MessageChoice<WindowClassTag, Target, typename Base::type>
			type;
		};

		template<typename WindowClassTag, typename Target, typename Base>
		struct generator<WindowClassTag, Target, nohandler, Base>
			: public Base
		{
		};

		template<typename WindowClassTag, typename Target, typename Base>
		struct generator_root
			: public Base
		{
		};
	}

	template<typename WindowClassTag, typename Target>
	struct generator
	{
		typedef
			typename detail::generator_root<WindowClassTag, Target
#	define WINDOW_MESSAGE_DEFINE_BEGIN_GENERATOR
#	include "win32_messages.h"
#	undef WINDOW_MESSAGE_DEFINE_BEGIN_GENERATOR

#	define WINDOW_MESSAGE_DEFINE_END_GENERATOR
#	include "win32_messages.h"
#	undef WINDOW_MESSAGE_DEFINE_END_GENERATOR
			>::type
		type;
	};

	template<typename WindowClassTag, typename Target>
	std::pair<bool, LRESULT> dispatch(Target target, const Context<WindowClassTag>& context)
	{
		BOOL handled = FALSE;
		LRESULT result = 0;
		return generator<WindowClassTag, Target>::type(base<WindowClassTag, Target>(target, &context, &handled, &result)).dispatch();
	}

}

 	template<typename WindowClassTag> 
	auto optional_window_class_construct(HWND hwnd, LPCREATESTRUCT createStruct, WindowClassTag&&, int) -> decltype(window_class_construct(hwnd, createStruct, WindowClassTag()))
	{ 
		return window_class_construct(hwnd, createStruct, WindowClassTag());
	} 

 	template<typename WindowClassTag> 
	std::unique_ptr<typename window_class<WindowClassTag>::traits::type> optional_window_class_construct(HWND , LPCREATESTRUCT , WindowClassTag&&, ...) 
	{ 
		typedef
			typename window_class<WindowClassTag>::traits::type
		Type;

		std::unique_ptr<Type> type(new (std::nothrow) Type);

		return std::move(type);
	}

	template<typename WindowClassTag, typename T> 
	auto optional_window_class_insert(HWND hwnd, T t, WindowClassTag&&, int) -> decltype(window_class_insert(hwnd, WindowClassTag()))
	{ 
		return window_class_insert(hwnd, std::move(t), WindowClassTag());
	} 

 	template<typename WindowClassTag> 
	bool optional_window_class_insert(HWND hwnd, std::unique_ptr<typename window_class<WindowClassTag>::traits::type> type, WindowClassTag&&, ...) 
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
	auto optional_window_class_find(HWND hwnd, WindowClassTag&&, int) -> decltype(window_class_find(hwnd, WindowClassTag()))
	{ 
		return window_class_find(hwnd, WindowClassTag());
	} 

 	template<typename WindowClassTag> 
	detail::raw_ptr<typename window_class<WindowClassTag>::traits::type> optional_window_class_find(HWND hwnd, WindowClassTag&&, ...) 
	{ 
		typedef
			typename window_class<WindowClassTag>::traits::type
		type;
		return detail::raw_ptr<type>(reinterpret_cast<type*>(GetWindowLongPtr(hwnd, GWLP_USERDATA)));
	}

 	template<typename Type, typename WindowClassTag> 
	auto optional_window_class_erase(HWND hwnd, Type type, WindowClassTag&&, int) -> decltype(window_class_erase(hwnd, type, WindowClassTag()))
	{ 
		return window_class_erase(hwnd, type, WindowClassTag());
	} 

 	template<typename Type, typename WindowClassTag> 
	void optional_window_class_erase(HWND hwnd, detail::raw_ptr<Type> , WindowClassTag&&, ...) 
	{ 
		SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
	}

	template<typename Type, typename WindowClassTag> 
	auto optional_window_class_destroy(HWND hwnd, Type type, WindowClassTag&&, int) -> decltype(window_class_erase(hwnd, type, WindowClassTag()))
	{ 
		return window_class_erase(hwnd, type, WindowClassTag());
	} 

 	template<typename Type, typename WindowClassTag> 
	void optional_window_class_destroy(HWND , detail::raw_ptr<Type> type, WindowClassTag&&, ...) 
	{ 
		delete type.raw;
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
			if (
				!optional_window_class_insert(
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

			std::tie(handled, result) = msg::dispatch(type, context);
			if (handled)
			{
				return result;
			}
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}

}
