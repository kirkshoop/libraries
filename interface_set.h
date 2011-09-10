#ifndef INTERFACE_SET_SOURCE
#define INTERFACE_SET_SOURCE

#ifndef INTERFACE_SET_NAMESPACE
#error INTERFACE_SET_NAMESPACE must be defined
#endif

namespace INTERFACE_SET_NAMESPACE
{
	namespace cmn=COMMON_NAMESPACE;

	template<typename InterfaceSetTag>
	struct traits 
		: public cmn::type_trait<decltype(interface_set_traits(InterfaceSetTag()))> {};

	template<typename Interface>
	struct interface_tag {}; 

	namespace detail
	{
		template<typename Interface>
		class disambiguator
			: public Interface
		{
		};

		template<typename Interface, typename Base>
		class root
			: public Base
		{
		public:
			~root()
			{}

			root()
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(1, Param)>
			explicit root(TPLT_FUNCTION_ARGUMENTS_DECL(1, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward))
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(2, Param)>
			root(TPLT_FUNCTION_ARGUMENTS_DECL(2, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(2, Param, std::forward))
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(3, Param)>
			root(TPLT_FUNCTION_ARGUMENTS_DECL(3, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(3, Param, std::forward))
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(4, Param)>
			root(TPLT_FUNCTION_ARGUMENTS_DECL(4, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(4, Param, std::forward))
			{}

		private:
			root(const root&);
			root& operator=(const root&);
		};

		template<typename InterfaceSetTag, typename Cursor, typename Begin, typename End, typename Storage>
		class generator
		{
		public:
			typedef
				typename generator<InterfaceSetTag, typename Cursor::increment, Begin, End, Storage>::type
			next;

			typedef
				root<
					typename Cursor::type, 
					decltype(
						interface_implementation<
							disambiguator,
							next
						>(interface_tag<typename Cursor::type>(), InterfaceSetTag())
					)
				>
			type;
		};

		template<typename InterfaceSetTag, typename Cursor, typename Begin, typename Storage>
		class generator<InterfaceSetTag, Cursor, Begin, Cursor, Storage>
		{
		public:
			typedef
				Storage
			type;
		};
	}

	template<typename Interfaces, typename Storage>
	struct traits_builder
	{
		typedef
			Interfaces
		interfaces;

		typedef
			Storage
		storage;
	};

	template<typename InterfaceSetTag>
	class interface_set
		: public detail::generator<
			InterfaceSetTag,
			typename traits<InterfaceSetTag>::type::interfaces::begin,
			typename traits<InterfaceSetTag>::type::interfaces::begin,
			typename traits<InterfaceSetTag>::type::interfaces::end,
			typename traits<InterfaceSetTag>::type::storage
		>::type
	{
	public:
		typedef
			typename detail::generator<
				InterfaceSetTag,
				typename traits<InterfaceSetTag>::type::interfaces::begin,
				typename traits<InterfaceSetTag>::type::interfaces::begin,
				typename traits<InterfaceSetTag>::type::interfaces::end,
				typename traits<InterfaceSetTag>::type::storage
			>::type
		base;

		~interface_set()
		{}

		interface_set() 
		{}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(1, Param)>
		explicit interface_set(TPLT_FUNCTION_ARGUMENTS_DECL(1, Param, , &&))
			: base(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward))
		{}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(2, Param)>
		interface_set(TPLT_FUNCTION_ARGUMENTS_DECL(2, Param, , &&))
			: base(TPLT_FUNCTION_ARGUMENTS_CAST(2, Param, std::forward))
		{}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(3, Param)>
		interface_set(TPLT_FUNCTION_ARGUMENTS_DECL(3, Param, , &&))
			: base(TPLT_FUNCTION_ARGUMENTS_CAST(3, Param, std::forward))
		{}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(4, Param)>
		interface_set(TPLT_FUNCTION_ARGUMENTS_DECL(4, Param, , &&))
			: base(TPLT_FUNCTION_ARGUMENTS_CAST(4, Param, std::forward))
		{}

	private:
		interface_set(const interface_set&);
		interface_set& operator=(const interface_set&);
	};

	template<typename Interface, typename InterfaceSet>
	Interface* interface_cast(InterfaceSet* interfaces)
	{
		return static_cast<Interface*>(static_cast<detail::disambiguator<Interface>*>(interfaces));
	}
}

#endif
