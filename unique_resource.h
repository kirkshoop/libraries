
#ifndef UNIQUE_RESOURCE_SOURCE
#define UNIQUE_RESOURCE_SOURCE

#ifndef UNIQUE_RESOURCE_NAMESPACE
#error UNIQUE_RESOURCE_NAMESPACE must be defined
#endif

namespace UNIQUE_RESOURCE_NAMESPACE
{
	using namespace COMMON_NAMESPACE;

	//
	// unique_resource will act like unique_ptr, but for non-pointer resources
	//

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
			decltype(unique_resource_invalid(tag()))
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

		operator typename unspecified_bool<this_type>::type() const
		{
			return unspecified_bool<this_type>::get(ok());
		}

		pointer operator->() const;

		void reset();
		void reset(type resource);
		pointer replace();

		type release();

		type get() const;

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
