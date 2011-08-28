
#ifndef UNIQUE_RESOURCE_NAMESPACE
#error UNIQUE_RESOURCE_NAMESPACE must be defined
#endif

namespace UNIQUE_RESOURCE_NAMESPACE
{
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
	unique_resource<ResourceTag>& unique_resource<ResourceTag>::operator=(unique_resource other)
	{
		swap(other);
		return *this;
	}

	template<typename ResourceTag>
	typename unique_resource<ResourceTag>::type unique_resource<ResourceTag>::operator->() const
	{
		return resource;
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
		if (resource != unique_resource_invalid(tag()))
		{
			FAIL_FAST_ON_THROW([&]{detail::unique_resource_reset<tag>(std::addressof(resource));});
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

	template<typename ResourceTag>
	bool unique_resource<ResourceTag>::empty() const
	{
		return resource == unique_resource_invalid(tag());
	}

	template<typename ResourceTag>
	unique_resource<ResourceTag>::operator typename unspecified_bool<unique_resource<ResourceTag>>::type() const
	{
		return unspecified_bool<this_type>::get(!empty());
	}

	template<typename ResourceTag>
	void unique_resource<ResourceTag>::swap(unique_resource& other)
	{
		using std::swap;
		swap(resource, other.resource);
	}

}
