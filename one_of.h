#ifndef ONE_OF_SOURCE
#define ONE_OF_SOURCE

#ifndef ONE_OF_NAMESPACE
#error ONE_OF_NAMESPACE must be defined
#endif

namespace ONE_OF_NAMESPACE
{
	using namespace COMMON_NAMESPACE;
	using namespace TYPE_VECTOR_NAMESPACE;

	namespace detail
	{
		template<typename Cursor, typename Begin, typename End, size_t Index = 0>
		struct traits
			: public traits<typename Cursor::increment, Begin, End, Index + 1>
			, type_trait<typename Cursor::type>
		{
			static const size_t index = Index;
		};

		template<typename Cursor, typename Begin, size_t Index>
		struct traits<Cursor, Begin, Cursor, Index>
		{
			template <typename Previous, typename Current>
			struct largest
				: public type_trait<typename std::conditional<sizeof(Previous) < sizeof(Current), Current, Previous>::type>
			{
			};

			template <typename Previous, typename Current>
			struct maxAligned
				: public type_trait<typename std::conditional<((Previous::value) < (std::alignment_of<Current>::value)), std::alignment_of<Current>, Previous>::type>
			{
			};

			static const size_t maxSize = sizeof(typename accumulate<Begin, end_forward_iterator, BYTE, largest>::type);
			static const size_t maxAlign = accumulate<Begin, end_forward_iterator, std::alignment_of<BYTE>, maxAligned>::type::value;
			typedef
				typename std::aligned_storage<maxSize, maxAlign>::type 
			storage;
		};
	}

	template<typename Vector>
	class one_of
	{
	public:
	private:
		typename detail::traits<typename Vector::begin, typename Vector::begin, typename Vector::end>::storage storage;
	};
}

#endif
