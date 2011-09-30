#ifndef INTERFACE_SET_SOURCE
#define INTERFACE_SET_SOURCE

#ifndef INTERFACE_SET_NAMESPACE
#error INTERFACE_SET_NAMESPACE must be defined
#endif

namespace INTERFACE_SET_NAMESPACE
{
	namespace cmn=COMMON_NAMESPACE;
	namespace ifset=INTERFACE_SET_NAMESPACE;

	template<typename InterfaceSetTag>
	struct traits 
		: public cmn::type_trait<decltype(interface_set_traits(InterfaceSetTag()))> {};

	template<typename Interface>
	struct interface_tag {}; 

	template<typename InterfaceSetTag, typename Interface>
	struct interface_traits
		: public cmn::type_trait<decltype(interface_tag_traits(interface_tag<Interface>(), InterfaceSetTag()))> {};

	template<typename InterfaceSetTag, typename Interface>
	struct interface_traits<InterfaceSetTag, interface_tag<Interface>>
		: public cmn::type_trait<decltype(interface_tag_traits(interface_tag<Interface>(), InterfaceSetTag()))> {};

	template<template<typename InterfaceSetTag, typename Base> class InterfaceImplementor, typename DefaultStorage>
	struct interface_traits_builder
	{
		template<typename InterfaceSetTag, typename Base>
		struct implementor_factory
			: public cmn::type_trait<InterfaceImplementor<InterfaceSetTag, Base>> {};

		typedef
			DefaultStorage
		default_storage;
	};

	namespace detail
	{
		template<typename Interface>
		class disambiguator
			: public Interface
		{
		};
	}

	template<typename Interface, typename InterfaceSet>
	Interface* interface_cast(InterfaceSet* interfaces)
	{
		return static_cast<Interface*>(static_cast<detail::disambiguator<Interface>*>(interfaces));
	}

	namespace detail
	{

		template<typename Disambiguator, typename Base>
		struct chain
			: public Disambiguator
			, public Base
		{
			~chain()
			{}

			chain()
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(1, Param)>
			explicit chain(TPLT_FUNCTION_ARGUMENTS_DECL(1, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward))
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(2, Param)>
			chain(TPLT_FUNCTION_ARGUMENTS_DECL(2, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(2, Param, std::forward))
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(3, Param)>
			chain(TPLT_FUNCTION_ARGUMENTS_DECL(3, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(3, Param, std::forward))
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(4, Param)>
			chain(TPLT_FUNCTION_ARGUMENTS_DECL(4, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(4, Param, std::forward))
			{}
		};

		template<typename InterfaceSetTag, typename Interface, typename Base>
		class root
			: public Base
		{
		private:
			void set_interface()
			{
				 interface_storage(
					this,
					ifset::interface_tag<Interface>(), 
					InterfaceSetTag()
				)->interface_constructed(ifset::interface_cast<Interface>(this), ifset::interface_tag<Interface>());
			}

		public:
			~root()
			{}

			root()
			{set_interface();}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(1, Param)>
			explicit root(TPLT_FUNCTION_ARGUMENTS_DECL(1, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward))
			{set_interface();}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(2, Param)>
			root(TPLT_FUNCTION_ARGUMENTS_DECL(2, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(2, Param, std::forward))
			{set_interface();}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(3, Param)>
			root(TPLT_FUNCTION_ARGUMENTS_DECL(3, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(3, Param, std::forward))
			{set_interface();}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(4, Param)>
			root(TPLT_FUNCTION_ARGUMENTS_DECL(4, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(4, Param, std::forward))
			{set_interface();}

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
				typename
				interface_traits<
					InterfaceSetTag, 
					interface_tag<typename Cursor::type>
				>::type::template implementor_factory<
					InterfaceSetTag,
					chain<disambiguator<typename Cursor::type>, next>
				>::type
			interface_implementor;

			typedef
				root<
					InterfaceSetTag,
					typename Cursor::type, 
					interface_implementor
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
}

#endif
