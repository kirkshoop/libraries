
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
		auto 
		find_unique_resource_indirect(int)
			-> std::pair<std::true_type, decltype(unique_resource_indirect(cmn::instance_of<ResourceType>::value, ResourceTag()))>;

		template<typename ResourceTag, typename ResourceType>
		std::pair<std::false_type, void**> 
		find_unique_resource_indirect(...);

		template<typename ResourceTag>
		struct find_unique_resource_indirect_result
		{
			typedef
				decltype(find_unique_resource_indirect<ResourceTag, typename resource_type<ResourceTag>::type>(0))
			type;
		};

		template<typename ResourceTag>
		struct optional_indirect_result : 
			public std::enable_if<
				find_unique_resource_indirect_result<ResourceTag>::type::first_type::value, 
				typename find_unique_resource_indirect_result<ResourceTag>::type::second_type
			>
		{};


		template<typename ResourceTag, typename ResourceType>
		auto 
		find_unique_resource_at(int)
			-> std::pair<std::true_type, decltype(unique_resource_at(cmn::instance_of<ResourceType>::value, instance_of<size_t>::value, ResourceTag()))>;

		template<typename ResourceTag, typename ResourceType>
		std::pair<std::false_type, void**> 
		find_unique_resource_at(...);

		template<typename ResourceTag>
		struct find_unique_resource_at_result
		{
			typedef
				decltype(find_unique_resource_at<ResourceTag, typename resource_type<ResourceTag>::type>(0))
			type;
		};

		template<typename ResourceTag>
		struct optional_at_result : 
			public std::enable_if<
				find_unique_resource_at_result<ResourceTag>::type::first_type::value, 
				typename find_unique_resource_at_result<ResourceTag>::type::second_type
			>
		{};


		template<typename ResourceTag>
		auto 
		find_unique_resource_make_default(int)
			-> std::pair<std::true_type, decltype(unique_resource_make(ResourceTag()))>;

		template<typename ResourceTag>
		std::pair<std::false_type, void**> 
		find_unique_resource_make_default(...);

		template<typename ResourceTag>
		struct find_unique_resource_make_default_result
		{
			typedef
				decltype(find_unique_resource_make_default<ResourceTag>(0))
			type;
		};

		template<typename ResourceTag>
		struct optional_make_default_result : 
			public std::enable_if<
				find_unique_resource_make_default_result<ResourceTag>::type::first_type::value, 
				typename find_unique_resource_make_default_result<ResourceTag>::type::second_type
			>
		{};
	}

	template<typename ResourceTag>
	class unique_resource
	{
	public:
		typedef 
			unique_resource
		this_type;

		typedef 
			ResourceTag
		tag;

		typedef
			typename detail::resource_type<ResourceTag>::type
		type;

		typedef
			type*
		pointer;

		static 
		typename detail::optional_make_default_result<tag>::type
		make();

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(1, Param)>
		static auto make(TPLT_FUNCTION_ARGUMENTS_DECL(1, Param, , &&)) 
			-> decltype(unique_resource_make(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward), tag()));

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(2, Param)>
		static auto make(TPLT_FUNCTION_ARGUMENTS_DECL(2, Param, , &&)) 
			-> decltype(unique_resource_make(TPLT_FUNCTION_ARGUMENTS_CAST(2, Param, std::forward), tag()));

		~unique_resource();

		unique_resource();

		unique_resource(type resource);

		// moveable
		unique_resource(unique_resource&& other);
		unique_resource& operator=(unique_resource other);

		operator typename cmn::unspecified_bool<this_type>::type() const;

		typename detail::optional_indirect_result<tag>::type
		operator->() const;

		typename detail::optional_indirect_result<tag>::type
		operator->();

		typename detail::optional_at_result<tag>::type
		operator[] (size_t index) const;

		typename detail::optional_at_result<tag>::type
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
}

#include "unique_resource.inl"

#endif //UNIQUE_RESOURCE_SOURCE
