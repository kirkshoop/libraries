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
			inline void unique_resource_reset(HANDLE resource, tag&&) { 
				CloseHandle(resource); }
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

#pragma warning(push)
#pragma warning(disable:4345) //  behavior change: an object of POD type constructed with an initializer of the form () will be default-initialized
	namespace detail
	{
		namespace local
		{
			template<typename T>
			struct tag {};

			template<typename T>
			T* unique_resource_invalid(tag<T>&&, typename std::enable_if<!std::is_array<T>::value, void**>::type x = 0) 
			{
				UNREFERENCED_PARAMETER(x);
				return nullptr; 
			}

			template<typename T>
			void unique_resource_reset(T* resource, tag<T>&&, typename std::enable_if<!std::is_array<T>::value, void**>::type x = 0) 
			{ 
				UNREFERENCED_PARAMETER(x);
				resource->~T(); 
				LocalFree(resource); 
			}

			template<typename T>
			T* unique_resource_indirect(T* resource, tag<T>&&, typename std::enable_if<!std::is_array<T>::value, void**>::type x = 0) 
			{ 
				UNREFERENCED_PARAMETER(x);
				return resource; 
			}

			template<typename T>
			std::pair<unique_winerror, UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag<T>>> 
			unique_resource_make(tag<T>&&, typename std::enable_if<!std::is_array<T>::value, void**>::type x = 0) 
			{
				UNREFERENCED_PARAMETER(x);
				typedef
					UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag<T>>
				Unique;
				T* resource = nullptr;
				ON_UNWIND(unwindResource, [&] { if (resource) { LocalFree(resource); } });
				resource = reinterpret_cast<T*>(LocalAlloc(LMEM_FIXED, sizeof(T)));
				auto winerror = make_winerror_if(!resource);
				if (!winerror)
				{
					return std::make_pair(std::move(winerror), Unique());
				}
				new (resource) T();
				Unique unique;
				unique.reset(resource);
				unwindResource.dismiss();
				return std::make_pair(std::move(winerror), std::move(unique));
			}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(1, Param), typename T>
			std::pair<unique_winerror, UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag<T>>> 
			unique_resource_make(TPLT_FUNCTION_ARGUMENTS_DECL(1, Param, , &&), tag<T>&&, typename std::enable_if<!std::is_array<T>::value, void**>::type x = 0) 
			{
				UNREFERENCED_PARAMETER(x);
				typedef
					UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag<T>>
				Unique;
				T* resource = nullptr;
				ON_UNWIND(unwindResource, [&] { if (resource) { LocalFree(resource); } });
				resource = reinterpret_cast<T*>(LocalAlloc(LMEM_FIXED, sizeof(T)));
				auto winerror = make_winerror_if(!resource);
				if (!winerror)
				{
					return std::make_pair(std::move(winerror), Unique());
				}
				new (resource) T(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward));
				Unique unique;
				unique.reset(resource);
				unwindResource.dismiss();
				return std::make_pair(std::move(winerror), std::move(unique));
			}

			// support for arrays
			//

			template<typename T>
			RANGE_NAMESPACE::range<T*> unique_resource_invalid(tag<T[]>&&) { return RANGE_NAMESPACE::range<T*>(); }

			template<typename T>
			void destruct_workaround(T* t)
			{
				UNREFERENCED_PARAMETER(t);
				t->~T();
			}

			template<typename T>
			const RANGE_NAMESPACE::range<T*>* unique_resource_indirect(const RANGE_NAMESPACE::range<T*>& resource, tag<T[]>&&) 
			{ 
				return &resource; 
			}

			template<typename T>
			RANGE_NAMESPACE::range<T*>* unique_resource_indirect(RANGE_NAMESPACE::range<T*>& resource, tag<T[]>&&) 
			{ 
				return &resource; 
			}

			template<typename T>
			void unique_resource_reset(RANGE_NAMESPACE::range<T*> resource, tag<T[]>&&) 
			{ 
				std::for_each(
					resource.begin(),
					resource.end(),
					[&] (T& t)
					{
						destruct_workaround(&t); 
					}
				);
				LocalFree(resource.begin()); 
			}

			template<typename T>
			bool unique_resource_empty(RANGE_NAMESPACE::range<T*> resource, tag<T[]>&&) 
			{ 
				return resource.empty();
			}

			template<typename T>
			T& unique_resource_at(RANGE_NAMESPACE::range<T*> resource, size_t index, tag<T[]>&&) 
			{ 
				return resource[index]; 
			}

			template<typename T>
			const T& unique_resource_at(const RANGE_NAMESPACE::range<T*>& resource, size_t index, tag<T[]>&&) 
			{ 
				return resource[index]; 
			}

			template<typename T>
			std::pair<unique_winerror, UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag<T[]>>> 
			unique_resource_make(size_t count, tag<T[]>&&) 
			{
				typedef
					UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag<T[]>>
				Unique;
				T* resource = nullptr;
				size_t constructed = 0;
				ON_UNWIND(unwindResource, 
					[&] 
					{ 
						if (resource) 
						{ 
							auto resourceRange = RANGE_NAMESPACE::make_range(resource, resource + constructed);
							unique_resource_reset(resourceRange, tag<T[]>());
							constructed = 0;
							resource = nullptr;
						} 
					}
				);
				resource = reinterpret_cast<T*>(LocalAlloc(LMEM_FIXED, count * sizeof(T)));
				auto winerror = make_winerror_if(!resource);
				if (!winerror)
				{
					return std::make_pair(std::move(winerror), Unique());
				}
				auto resourceRange = RANGE_NAMESPACE::make_range(resource, resource + count);
				std::for_each(
					resourceRange.begin(),
					resourceRange.end(),
					[&] (T& t)
					{
						new (&t) T();
						++constructed;
					}
				);
				Unique unique;
				unique.reset(resourceRange);
				unwindResource.dismiss();
				return std::make_pair(std::move(winerror), std::move(unique));
			}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(1, Param), typename T>
			std::pair<unique_winerror, UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag<T[]>>> 
			unique_resource_make(size_t count, TPLT_FUNCTION_ARGUMENTS_DECL(1, Param, , &&), tag<T[]>&&) 
			{
				typedef
					UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag<T[]>>
				Unique;
				T* resource = nullptr;
				size_t constructed = 0;
				ON_UNWIND(unwindResource, 
					[&] 
					{ 
						if (resource) 
						{ 
							auto resourceRange = RANGE_NAMESPACE::make_range(resource, resource + constructed);
							unique_resource_reset(resourceRange, tag<T[]>());
							constructed = 0;
							resource = nullptr;
						} 
					}
				);
				resource = reinterpret_cast<T*>(LocalAlloc(LMEM_FIXED, count * sizeof(T)));
				auto winerror = make_winerror_if(!resource);
				if (!winerror)
				{
					return std::make_pair(std::move(winerror), Unique());
				}
				auto resourceRange = RANGE_NAMESPACE::make_range(resource, resource + count);
				std::for_each(
					resourceRange.begin(),
					resourceRange.end(),
					[&] (T& t)
					{
						new (&t) T(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward));
						++constructed;
					}
				);
				Unique unique;
				unique.reset(resourceRange);
				unwindResource.dismiss();
				return std::make_pair(std::move(winerror), std::move(unique));
			}
		}
	}
	template<typename T>
	struct unique_local_factory
	{
		typedef 
			UNIQUE_RESOURCE_NAMESPACE::unique_resource<detail::local::tag<T>>
		type;
	private:
		~unique_local_factory();
		unique_local_factory();
	};
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable:4345) //  behavior change: an object of POD type constructed with an initializer of the form () will be default-initialized
	namespace detail
	{
		namespace cotask
		{
			template<typename T>
			struct tag {};

			template<typename T>
			T* unique_resource_invalid(tag<T>&&, typename std::enable_if<!std::is_array<T>::value, void**>::type x = 0) 
			{
				UNREFERENCED_PARAMETER(x);
				return nullptr; 
			}

			template<typename T>
			void unique_resource_reset(T* resource, tag<T>&&, typename std::enable_if<!std::is_array<T>::value, void**>::type x = 0) 
			{ 
				UNREFERENCED_PARAMETER(x);
				resource->~T(); 
				CoTaskMemFree(resource); 
			}

			template<typename T>
			T* unique_resource_indirect(T* resource, tag<T>&&, typename std::enable_if<!std::is_array<T>::value, void**>::type x = 0) 
			{ 
				UNREFERENCED_PARAMETER(x);
				return resource; 
			}

			template<typename T>
			std::pair<unique_winerror, UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag<T>>> 
			unique_resource_make(tag<T>&&, typename std::enable_if<!std::is_array<T>::value, void**>::type x = 0) 
			{
				UNREFERENCED_PARAMETER(x);
				typedef
					UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag<T>>
				Unique;
				T* resource = nullptr;
				ON_UNWIND(unwindResource, [&] { if (resource) { CoTaskMemFree(resource); } });
				resource = reinterpret_cast<T*>(CoTaskMemAlloc(sizeof(T)));
				auto winerror = make_winerror_if(!resource);
				if (!winerror)
				{
					return std::make_pair(std::move(winerror), Unique());
				}
				new (resource) T();
				Unique unique;
				unique.reset(resource);
				unwindResource.dismiss();
				return std::make_pair(std::move(winerror), std::move(unique));
			}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(1, Param), typename T>
			std::pair<unique_winerror, UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag<T>>> 
			unique_resource_make(TPLT_FUNCTION_ARGUMENTS_DECL(1, Param, , &&), tag<T>&&, typename std::enable_if<!std::is_array<T>::value, void**>::type x = 0) 
			{
				UNREFERENCED_PARAMETER(x);
				typedef
					UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag<T>>
				Unique;
				T* resource = nullptr;
				ON_UNWIND(unwindResource, [&] { if (resource) { CoTaskMemFree(resource); } });
				resource = reinterpret_cast<T*>(CoTaskMemAlloc(sizeof(T)));
				auto winerror = make_winerror_if(!resource);
				if (!winerror)
				{
					return std::make_pair(std::move(winerror), Unique());
				}
				new (resource) T(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward));
				Unique unique;
				unique.reset(resource);
				unwindResource.dismiss();
				return std::make_pair(std::move(winerror), std::move(unique));
			}

			// support for arrays
			//

			template<typename T>
			RANGE_NAMESPACE::range<T*> unique_resource_invalid(tag<T[]>&&) { return RANGE_NAMESPACE::range<T*>(); }

			template<typename T>
			void destruct_workaround(T* t)
			{
				UNREFERENCED_PARAMETER(t);
				t->~T();
			}

			template<typename T>
			const RANGE_NAMESPACE::range<T*>* unique_resource_indirect(const RANGE_NAMESPACE::range<T*>& resource, tag<T[]>&&) 
			{ 
				return &resource; 
			}

			template<typename T>
			RANGE_NAMESPACE::range<T*>* unique_resource_indirect(RANGE_NAMESPACE::range<T*>& resource, tag<T[]>&&) 
			{ 
				return &resource; 
			}

			template<typename T>
			void unique_resource_reset(RANGE_NAMESPACE::range<T*> resource, tag<T[]>&&) 
			{ 
				std::for_each(
					resource.begin(),
					resource.end(),
					[&] (T& t)
					{
						destruct_workaround(&t); 
					}
				);
				CoTaskMemFree(resource.begin()); 
			}

			template<typename T>
			bool unique_resource_empty(RANGE_NAMESPACE::range<T*> resource, tag<T[]>&&) 
			{ 
				return resource.empty();
			}

			template<typename T>
			T& unique_resource_at(RANGE_NAMESPACE::range<T*> resource, size_t index, tag<T[]>&&) 
			{ 
				return resource[index]; 
			}

			template<typename T>
			const T& unique_resource_at(const RANGE_NAMESPACE::range<T*>& resource, size_t index, tag<T[]>&&) 
			{ 
				return resource[index]; 
			}

			template<typename T>
			std::pair<unique_winerror, UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag<T[]>>> 
			unique_resource_make(size_t count, tag<T[]>&&) 
			{
				typedef
					UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag<T[]>>
				Unique;
				T* resource = nullptr;
				size_t constructed = 0;
				ON_UNWIND(unwindResource, 
					[&] 
					{ 
						if (resource) 
						{ 
							auto resourceRange = RANGE_NAMESPACE::make_range(resource, resource + constructed);
							unique_resource_reset(resourceRange, tag<T[]>());
							constructed = 0;
							resource = nullptr;
						} 
					}
				);
				resource = reinterpret_cast<T*>(CoTaskMemAlloc(count * sizeof(T)));
				auto winerror = make_winerror_if(!resource);
				if (!winerror)
				{
					return std::make_pair(std::move(winerror), Unique());
				}
				auto resourceRange = RANGE_NAMESPACE::make_range(resource, resource + count);
				std::for_each(
					resourceRange.begin(),
					resourceRange.end(),
					[&] (T& t)
					{
						new (&t) T();
						++constructed;
					}
				);
				Unique unique;
				unique.reset(resourceRange);
				unwindResource.dismiss();
				return std::make_pair(std::move(winerror), std::move(unique));
			}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(1, Param), typename T>
			std::pair<unique_winerror, UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag<T[]>>> 
			unique_resource_make(size_t count, TPLT_FUNCTION_ARGUMENTS_DECL(1, Param, , &&), tag<T[]>&&) 
			{
				typedef
					UNIQUE_RESOURCE_NAMESPACE::unique_resource<tag<T[]>>
				Unique;
				T* resource = nullptr;
				size_t constructed = 0;
				ON_UNWIND(unwindResource, 
					[&] 
					{ 
						if (resource) 
						{ 
							auto resourceRange = RANGE_NAMESPACE::make_range(resource, resource + constructed);
							unique_resource_reset(resourceRange, tag<T[]>());
							constructed = 0;
							resource = nullptr;
						} 
					}
				);
				resource = reinterpret_cast<T*>(CoTaskMemAlloc(count * sizeof(T)));
				auto winerror = make_winerror_if(!resource);
				if (!winerror)
				{
					return std::make_pair(std::move(winerror), Unique());
				}
				auto resourceRange = RANGE_NAMESPACE::make_range(resource, resource + count);
				std::for_each(
					resourceRange.begin(),
					resourceRange.end(),
					[&] (T& t)
					{
						new (&t) T(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward));
						++constructed;
					}
				);
				Unique unique;
				unique.reset(resourceRange);
				unwindResource.dismiss();
				return std::make_pair(std::move(winerror), std::move(unique));
			}
		}
	}
	template<typename T>
	struct unique_cotask_factory
	{
		typedef 
			UNIQUE_RESOURCE_NAMESPACE::unique_resource<detail::cotask::tag<T>>
		type;
	private:
		~unique_cotask_factory();
		unique_cotask_factory();
	};
#pragma warning(pop)

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

			template<typename Interface>
			Interface* unique_resource_indirect(Interface* resource, tag<Interface>&&) { return resource; }
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
	unique_winerror 
	LoadStringRaw(HINSTANCE instance, UINT id, const RANGE_NAMESPACE::range<WCHAR*>& space, RANGE_NAMESPACE::range<WCHAR*>* spaceUsed, size_t* spaceRequested)
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
				*spaceRequested = std::max<size_t>(3, static_cast<size_t>(space.size() * 1.5));

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
	std::wstring 
	LoadStdString(HINSTANCE instance, UINT id, size_t sizeLimit = 2048, size_t initialSize = 80)
	{
		unique_winerror winerror;
		std::wstring result;
		RANGE_NAMESPACE::range<WCHAR*> spaceUsed;
		size_t spaceRequested = initialSize;

		while(spaceRequested < sizeLimit)
		{
			result.resize(spaceRequested);
			winerror = LoadStringRaw(instance, id, RANGE_NAMESPACE::make_range_raw(result), &spaceUsed, &spaceRequested);
			if (winerror != winerror_cast(ERROR_MORE_DATA))
			{
				winerror.throw_if();
				break;
			}
			winerror.suppress();
			continue;
		}

		return std::move(result);
	}

	template<typename UniqueResource> 
	std::pair<unique_winerror, UniqueResource>
	LoadStdString(HINSTANCE instance, UINT id, size_t sizeLimit = 2048, size_t initialSize = 80) 
	{
		unique_winerror winerror;
		UniqueResource result;
		RANGE_NAMESPACE::range<WCHAR*> spaceUsed;
		size_t spaceRequested = initialSize;

		while(spaceRequested < sizeLimit)
		{
			std::tie(winerror, result) = UniqueResource::make(spaceRequested);
			if (!winerror)
			{
				break;
			}
			winerror = LoadStringRaw(instance, id, result.get(), &spaceUsed, &spaceRequested);
			if (winerror != winerror_cast(ERROR_MORE_DATA))
			{
				break;
			}
			winerror.suppress();
			continue;
		}

		return std::make_pair(std::move(winerror), std::move(result));
	}
}

#endif //WINDOWS_RESOURCE_SOURCE
