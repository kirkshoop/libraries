
#ifndef UNIQUE_RESOURCE_NAMESPACE
#error UNIQUE_RESOURCE_NAMESPACE must be defined
#endif

namespace UNIQUE_RESOURCE_NAMESPACE
{

	template<typename UniqueResource>
	decltype(unique_resource_make(UniqueResource::tag()))
	make()
	{
		return unique_resource_make(UniqueResource::tag());
	}

	template<typename UniqueResource, TPLT_TEMPLATE_ARGUMENTS_DECL(1, Param)>
	auto 
	make(TPLT_FUNCTION_ARGUMENTS_DECL(1, Param, , &&)) 
		-> decltype(unique_resource_make(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward), UniqueResource::tag()))
	{
		return unique_resource_make(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward), UniqueResource::tag());
	}

	template<typename UniqueResource, TPLT_TEMPLATE_ARGUMENTS_DECL(2, Param)>
	auto 
	make(TPLT_FUNCTION_ARGUMENTS_DECL(2, Param, , &&)) 
		-> decltype(unique_resource_make(TPLT_FUNCTION_ARGUMENTS_CAST(2, Param, std::forward), UniqueResource::tag()))
	{
		return unique_resource_make(TPLT_FUNCTION_ARGUMENTS_CAST(2, Param, std::forward), UniqueResource::tag());
	}

	template<typename UniqueResource>
	auto
	at(const UniqueResource& resource, size_t index)
		-> decltype(unique_resource_at(resource.get(), index, UniqueResource::tag()))
	{
		return unique_resource_at(resource.get(), index, UniqueResource::tag());
	}

	template<typename UniqueResource>
	auto
	at(UniqueResource&& resource, size_t index)
		-> decltype(unique_resource_at(resource.get(), index, UniqueResource::tag()))
	{
		return unique_resource_at(resource.get(), index, UniqueResource::tag());
	}

	template<typename ResourceTag>
	unique_resource<ResourceTag>::~unique_resource()
	{
		reset();
	}

	template<typename ResourceTag>
	unique_resource<ResourceTag>::unique_resource()
		: resource(unique_resource_invalid(tag()))
	{
	}

	template<typename ResourceTag>
	unique_resource<ResourceTag>::unique_resource(type resourceArg)
		: resource(resourceArg)
	{
	}

	template<typename ResourceTag>
	unique_resource<ResourceTag>::unique_resource(unique_resource&& other)
		: resource(other.release())
	{
	}

	template<typename ResourceTag>
	unique_resource<ResourceTag>& 
	unique_resource<ResourceTag>::operator=(unique_resource other)
	{
		swap(other);
		return *this;
	}

	template<typename ResourceTag>
	typename unique_resource<ResourceTag>::optional_indirect_result
	unique_resource<ResourceTag>::operator->() const
	{
		return detail::optional_unique_resource_indirect<tag_type>(resource, 0);
	}

	template<typename ResourceTag>
	typename unique_resource<ResourceTag>::optional_indirect_result
	unique_resource<ResourceTag>::operator->()
	{
		return detail::optional_unique_resource_indirect<tag_type>(resource, 0);
	}

	template<typename ResourceTag>
	typename unique_resource<ResourceTag>::optional_at_result
	unique_resource<ResourceTag>::operator[] (size_t index) const
	{
		return detail::optional_unique_resource_at<tag_type>(resource, index, 0);
	}

	template<typename ResourceTag>
	typename unique_resource<ResourceTag>::optional_at_result
	unique_resource<ResourceTag>::operator[] (size_t index)
	{
		return detail::optional_unique_resource_at<tag_type>(resource, index, 0);
	}

	namespace detail 
	{
		template<typename ResourceTag, typename Resource>
		void unique_resource_reset(Resource* resource)
		{
			unique_resource_reset(*resource, ResourceTag());
		}
	}

	template<typename ResourceTag>
	void unique_resource<ResourceTag>::reset()
	{
		if (!empty())
		{
			FAIL_FAST_ON_THROW([&]{detail::unique_resource_reset<tag_type>(std::addressof(resource));});
			resource = unique_resource_invalid(tag());
		}
	}

	template<typename ResourceTag>
	void unique_resource<ResourceTag>::reset(type resourceArg)
	{
		reset();
		resource = std::move(resourceArg);
	}

	template<typename ResourceTag>
	typename unique_resource<ResourceTag>::pointer unique_resource<ResourceTag>::replace()
	{
		reset();
		return std::addressof(resource);
	}

	template<typename ResourceTag>
	typename unique_resource<ResourceTag>::type unique_resource<ResourceTag>::release()
	{
		type result = resource;
		resource = unique_resource_invalid(tag());
		return result;
	}

	template<typename ResourceTag>
	typename unique_resource<ResourceTag>::type unique_resource<ResourceTag>::get() const
	{
		return resource;
	}

	namespace detail
	{
		template<typename ResourceTag, typename ResourceType>
		auto 
		optional_unique_resource_empty(ResourceType&& resource, int)
			-> decltype(unique_resource_empty(std::forward<ResourceType>(resource), ResourceTag()))
		{
			return unique_resource_empty(std::forward<ResourceType>(resource), ResourceTag());
		}

		template<typename ResourceTag, typename ResourceType>
		bool 
		optional_unique_resource_empty(ResourceType&& resource, ...)
		{
			return resource == unique_resource_invalid(ResourceTag());
		}
	}

	template<typename ResourceTag>
	bool unique_resource<ResourceTag>::empty() const
	{
		return detail::optional_unique_resource_empty<tag_type>(resource, 0);
	}

	template<typename ResourceTag>
	unique_resource<ResourceTag>::operator typename cmn::unspecified_bool<unique_resource<ResourceTag>>::type() const
	{
		return cmn::unspecified_bool<this_type>::get(!empty());
	}

	template<typename ResourceTag>
	void unique_resource<ResourceTag>::swap(unique_resource& other)
	{
		using std::swap;
		swap(resource, other.resource);
	}

}
