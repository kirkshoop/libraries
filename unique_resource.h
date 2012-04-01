
#ifndef UNIQUE_RESOURCE_SOURCE
#define UNIQUE_RESOURCE_SOURCE

#ifndef UNIQUE_RESOURCE_NAMESPACE
#error UNIQUE_RESOURCE_NAMESPACE must be defined
#endif

namespace UNIQUE_RESOURCE_NAMESPACE
{
	namespace cmn=COMMON_NAMESPACE;

	//
	// unique_resource will act like unique_ptr, but for non-pointer resources
	//

	namespace detail
	{
		template<typename ResourceTag>
		struct resource_type
		{
			typedef
				decltype(unique_resource_invalid(ResourceTag()))
			type;
		};

		template<typename ResourceTag, typename ResourceType>
		decltype(unique_resource_indirect(cmn::instance_of<ResourceType>::value, ResourceTag()))
		optional_unique_resource_indirect(ResourceType&& resource, int)
		{
			return unique_resource_indirect(std::forward<ResourceType>(resource), ResourceTag());
		}

		struct no_indirection_support {};

		template<typename ResourceTag>
		no_indirection_support 
		optional_unique_resource_indirect(...)
		{
			return no_indirection_support();
		}

		template<typename ResourceTag, typename ResourceType>
		decltype(unique_resource_at(cmn::instance_of<ResourceType>::value, cmn::instance_of<size_t>::value, ResourceTag()))
		optional_unique_resource_at(ResourceType&& resource, size_t index, int)
		{
			return unique_resource_at(std::forward<ResourceType>(resource), index, ResourceTag());
		}

		struct no_indexing_support {};

		template<typename ResourceTag>
		no_indexing_support 
		optional_unique_resource_at(...)
		{
			return no_indexing_support();
		}
	}

	template<typename ResourceTag>
	class unique_resource
	{
	private:
		typedef
			decltype(detail::optional_unique_resource_indirect<ResourceTag>(
					cmn::instance_of<typename detail::resource_type<ResourceTag>::type>::value,
					0))
		optional_indirect_result;

		typedef
			decltype(detail::optional_unique_resource_at<ResourceTag>(
					cmn::instance_of<typename detail::resource_type<ResourceTag>::type>::value,
					cmn::instance_of<size_t>::value,
					0))
		optional_at_result;

	public:
		typedef 
			unique_resource
		this_type;

		typedef 
			ResourceTag
		tag_type;

		static tag_type tag() { return tag_type(); }

		typedef
			typename detail::resource_type<ResourceTag>::type
		type;

		typedef
			type*
		pointer;

		~unique_resource();

		unique_resource();

		unique_resource(type resource);

		// moveable
		unique_resource(unique_resource&& other);
		unique_resource& operator=(unique_resource other);

		operator typename cmn::unspecified_bool<this_type>::type() const;

		optional_indirect_result
		operator->() const;

		optional_indirect_result
		operator->();

		optional_at_result
		operator[] (size_t index) const;

		optional_at_result
		operator[] (size_t index);

		void reset();
		void reset(type resource);
		pointer replace();

		type release();

		type get() const;

		bool empty() const;

		void swap(unique_resource& other);

	private:
		type resource;

		// copy not supported

		unique_resource(unique_resource& other);
		//unique_resource& operator= (unique_resource& other);
	};

	template<typename UniqueResource>
	decltype(unique_resource_make(UniqueResource::tag())) make(); 

	template<typename UniqueResource, TPLT_TEMPLATE_ARGUMENTS_DECL(1, Param)>
	auto make(TPLT_FUNCTION_ARGUMENTS_DECL(1, Param, , &&)) 
		-> decltype(unique_resource_make(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward), UniqueResource::tag()));

	template<typename UniqueResource, TPLT_TEMPLATE_ARGUMENTS_DECL(2, Param)>
	auto make(TPLT_FUNCTION_ARGUMENTS_DECL(2, Param, , &&)) 
		-> decltype(unique_resource_make(TPLT_FUNCTION_ARGUMENTS_CAST(2, Param, std::forward), UniqueResource::tag()));

	template<typename UniqueResource>
	auto
	at(const UniqueResource& resource, size_t index)
		-> decltype(unique_resource_at(resource.get(), index, UniqueResource::tag()));

	template<typename UniqueResource>
	auto
	at(UniqueResource&& resource, size_t index)
		-> decltype(unique_resource_at(resource.get(), index, UniqueResource::tag()));

}

#include "unique_resource.inl"

#endif //UNIQUE_RESOURCE_SOURCE
