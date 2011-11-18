
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
}

#include "win32_window.inl"

#endif //WIN32_WINDOW_SOURCE