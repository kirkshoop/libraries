#ifndef WINDOWS_RESOURCE_SOURCE
#define WINDOWS_RESOURCE_SOURCE

#ifndef UNIQUE_RESOURCE_NAMESPACE
#error UNIQUE_RESOURCE_NAMESPACE must be defined
#endif

#ifndef WINDOWS_RESOURCES_NAMESPACE
#error WINDOWS_RESOURCES_NAMESPACE must be defined
#endif

namespace WINDOWS_RESOURCES_NAMESPACE
{
	using namespace COMMON_NAMESPACE;

	namespace file
	{
		struct tag {};
		HANDLE unique_resource_invalid(tag&) { return INVALID_HANDLE_VALUE; }
		void unique_resource_reset(HANDLE resource, tag&) { CloseHandle(resource); }
		typedef
			UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag>
		unique;
	}

	namespace window
	{
		struct tag {};
		inline HWND unique_resource_invalid(tag&) { return NULL; }
		inline void unique_resource_reset(HWND resource, tag&) { CloseWindow(resource); }
		typedef
			UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag>
		unique;
	}

	namespace gdi_delete_dc
	{
		struct tag {};
		inline HDC unique_resource_invalid(tag&) { return NULL; }
		inline void unique_resource_reset(HDC resource, tag&) { DeleteDC(resource); }
		typedef
			UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag>
		unique;
	}

	namespace gdi_release_dc
	{
		struct tag {};
		inline std::pair<HWND, HDC> unique_resource_invalid(tag&) { return std::make_pair(nullptr, nullptr); }
		inline void unique_resource_reset(std::pair<HWND, HDC> resource, tag&) { ReleaseDC(resource.first, resource.second); }
		typedef
			UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag>
		unique;
	}

	namespace gdi_end_paint
	{
		struct tag {};
		inline std::pair<HWND, PAINTSTRUCT*> unique_resource_invalid(tag&) { return std::make_pair(nullptr, nullptr); }
		inline void unique_resource_reset(std::pair<HWND, PAINTSTRUCT*> resource, tag&) { EndPaint(resource.first, resource.second); }
		typedef
			UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag>
		unique;
	}

	namespace com_interface
	{
		template<typename Interface>
		struct tag {};

		template<typename Interface>
		Interface* unique_resource_invalid(tag<Interface>&) { return nullptr; }

		template<typename Interface>
		void unique_resource_reset(Interface* resource, tag<Interface>&) { resource->Release(); }

		template<typename Interface>
		struct make_unique : public type_trait<UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag<Interface>>>
		{
		};
	}

	template<typename Interface>
	typename com_interface::make_unique<Interface>::type ComCreateInstance(CLSID classId, unique_hresult* hr = nullptr, DWORD clsContext = CLSCTX_LOCAL_SERVER)
	{
		typename com_interface::make_unique<Interface>::type result;
		if (hr)
		{
			hr->reset(CoCreateInstance(classId, nullptr, clsContext, __uuidof(Interface), (LPVOID*)result.replace()));
		}
		else
		{
			unique_hresult::make(CoCreateInstance(classId, nullptr, clsContext, __uuidof(Interface), (LPVOID*)result.replace())).throw_if();
		}
		return std::move(result);
	}

	template<typename Interface>
	unique_hresult ComCreateInstance(CLSID classId, UNIQUE_RESOURCE_NAMESPACE::unique_resource<com_interface::tag<Interface>>* result, DWORD clsContext = CLSCTX_LOCAL_SERVER)
	{
		return unique_hresult::make(CoCreateInstance(classId, nullptr, clsContext, __uuidof(Interface), (LPVOID*)result->replace()));
	}

	inline
	unique_winerror LoadStringRaw(HINSTANCE instance, UINT id, const RANGE_NAMESPACE::range<WCHAR*>& space, RANGE_NAMESPACE::range<WCHAR*>* spaceUsed, size_t* spaceRequested)
	{
		if (spaceUsed)
		{
			*spaceUsed = space;
			spaceUsed->advance_end(-space.size());
		}

		if (spaceRequested)
		{
			*spaceRequested = space.size();
		}

		SetLastError(ERROR_SUCCESS);

		int loadResult = LoadStringW(instance, id, space.begin(), space.size());

		auto winerror = make_winerror_if(TRUE);

		if (loadResult >= 0)
		{
			if ((loadResult + 1) < space.size())
			{
				if (winerror.ok())
				{
					*spaceUsed = space;
					spaceUsed->advance_end(loadResult - space.size());
				}
			}
			else
			{
				*spaceRequested = static_cast<size_t>(loadResult * 1.5);

				if (winerror.ok())
				{
					winerror = winerror_cast(ERROR_MORE_DATA);
				}
			}
		}
		else
		{
			if (winerror.ok())
			{
				winerror = winerror_cast(ERROR_UNIDENTIFIED_ERROR);
			}
		}

		return winerror;
	}

	inline
	unique_winerror LoadStdString(HINSTANCE instance, UINT id, std::wstring* string)
	{
		unique_winerror winerror(winerror_cast(ERROR_MORE_DATA));
		RANGE_NAMESPACE::range<WCHAR*> spaceUsed;
		size_t spaceRequested = 80;

		while(winerror == winerror_cast(ERROR_MORE_DATA) && spaceRequested < 2048)
		{
			winerror.suppress();
			string->resize(spaceRequested);
			winerror = LoadStringRaw(instance, id, RANGE_NAMESPACE::make_range_raw(*string), &spaceUsed, &spaceRequested);
		}

		return winerror;
	}
}

#endif //WINDOWS_RESOURCE_SOURCE
