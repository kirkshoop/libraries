
#ifndef WIN32_WINDOW_SOURCE
#define WIN32_WINDOW_SOURCE

#ifndef WIN32_WINDOW_NAMESPACE
#error WIN32_WINDOW_NAMESPACE must be defined
#endif

namespace WIN32_WINDOW_NAMESPACE
{
	using namespace COMMON_NAMESPACE;

	template<typename Type>
	struct window_class_traits_builder
	{
		typedef
			Type
		type;
	};

	template<typename WindowClassTag>
	class window_class
	{
	public:
		typedef 
			WindowClassTag
		tag;

		typedef
			decltype(window_class_traits(tag()))
		traits;

		static ATOM Register();

		template<typename T>
		static ATOM Register(T&& t);

	private:
		typedef
			std::unordered_map<HWND, std::shared_ptr<typename traits::type>>
		hwndToTypes;

		template<typename Instance>
		static Instance& use_types();

		static LRESULT CALLBACK WindowCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK WindowCallbackSafe(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		~window_class();
		window_class();
		window_class(window_class&);
		window_class& operator=(window_class&);
	};
}

#include "win32_window.inl"

#endif //WIN32_WINDOW_SOURCE