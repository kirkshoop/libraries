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

	namespace detail
	{
		template<typename Resource>
		std::pair<unique_winerror, Resource>
		winerror_and_resource(typename Resource::type resource)
		{
			Resource result;
			result.reset(resource);
			return std::make_pair(make_winerror_if(!result), std::move(result));
		}
	}

	namespace detail
	{
		namespace file
		{
			struct tag {};
			inline HANDLE unique_resource_invalid(tag&&) { return INVALID_HANDLE_VALUE; }
			inline void unique_resource_reset(HANDLE resource, tag&&) { CloseHandle(resource); }
		}
	}
	typedef
		UNIQUE_RESOURCE_NAMESPACE::unique_resource<detail::file::tag>
	unique_file;

	inline
	auto winerror_and_file(HANDLE result) -> decltype(detail::winerror_and_resource<unique_file>(result))
	{
		return detail::winerror_and_resource<unique_file>(result);
	}

	namespace detail
	{
		namespace close_window
		{
			struct tag {};
			inline HWND unique_resource_invalid(tag&&) { return NULL; }
			inline void unique_resource_reset(HWND resource, tag&&) { CloseWindow(resource); }
		}
	}
	typedef
		UNIQUE_RESOURCE_NAMESPACE::unique_resource<detail::close_window::tag>
	unique_close_window;

	inline
	auto winerror_and_close_window(HWND result) -> decltype(detail::winerror_and_resource<unique_close_window>(result))
	{
		return detail::winerror_and_resource<unique_close_window>(result);
	}

	namespace detail
	{
		namespace gdi_delete_dc
		{
			struct tag {};
			inline HDC unique_resource_invalid(tag&&) { return NULL; }
			inline void unique_resource_reset(HDC resource, tag&&) { DeleteDC(resource); }
		}
	}
	typedef
		UNIQUE_RESOURCE_NAMESPACE::unique_resource<detail::gdi_delete_dc::tag>
	unique_gdi_delete_dc;

	namespace detail
	{
		namespace gdi_release_dc
		{
			struct tag {};
			inline std::pair<HWND, HDC> unique_resource_invalid(tag&&) { return std::make_pair(nullptr, nullptr); }
			inline void unique_resource_reset(std::pair<HWND, HDC> resource, tag&&) { ReleaseDC(resource.first, resource.second); }
		}
	}
	typedef
		UNIQUE_RESOURCE_NAMESPACE::unique_resource<detail::gdi_release_dc::tag>
	unique_gdi_release_dc;

	namespace detail
	{
		namespace gdi_end_paint
		{
			struct tag {};
			inline std::pair<HWND, PAINTSTRUCT*> unique_resource_invalid(tag&&) { return std::make_pair(nullptr, nullptr); }
			inline void unique_resource_reset(std::pair<HWND, PAINTSTRUCT*> resource, tag&&) { EndPaint(resource.first, resource.second); }
		}
	}
	typedef
		UNIQUE_RESOURCE_NAMESPACE::unique_resource<detail::gdi_end_paint::tag>
	unique_gdi_end_paint;

	namespace detail
	{
		namespace com_interface
		{
			template<typename Interface>
			struct tag {};

			template<typename Interface>
			Interface* unique_resource_invalid(tag<Interface>&&) { return nullptr; }

			template<typename Interface>
			void unique_resource_reset(Interface* resource, tag<Interface>&&) { resource->Release(); }
		}
	}
	template<typename Interface>
	struct unique_com_interface : public type_trait<UNIQUE_RESOURCE_NAMESPACE::unique_resource<detail::com_interface::tag<Interface>>>
	{
	};

	template<typename Interface>
	std::pair<unique_hresult, typename unique_com_interface<Interface>::type> 
	ComCreateInstance(CLSID classId, DWORD clsContext = CLSCTX_LOCAL_SERVER, LPUNKNOWN outer = nullptr)
	{
		unique_hresult hr;
		typename unique_com_interface<Interface>::type result;

		hr.reset(CoCreateInstance(classId, outer, clsContext, __uuidof(Interface), (LPVOID*)result.replace()));

		return std::make_pair(std::move(hr), std::move(result));
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
	std::pair<unique_winerror, std::wstring> LoadStdString(HINSTANCE instance, UINT id)
	{
		unique_winerror winerror;
		std::wstring result;
		RANGE_NAMESPACE::range<WCHAR*> spaceUsed;
		size_t spaceRequested = 80;

		while(spaceRequested < 2048)
		{
			result.resize(spaceRequested);
			winerror = LoadStringRaw(instance, id, RANGE_NAMESPACE::make_range_raw(result), &spaceUsed, &spaceRequested);
			if (winerror == winerror_cast(ERROR_MORE_DATA))
			{
				winerror.suppress();
				continue;
			}
			break;
		}

		return std::make_pair(std::move(winerror), std::move(result));
	}
}

#endif //WINDOWS_RESOURCE_SOURCE
