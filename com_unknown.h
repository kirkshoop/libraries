#ifndef COM_UNKNOWN_SOURCE
#define COM_UNKNOWN_SOURCE

#ifndef COM_NAMESPACE
#error COM_NAMESPACE must be defined
#endif

namespace COM_NAMESPACE
{
	namespace ifset=INTERFACE_SET_NAMESPACE;

	namespace detail
	{
		template<typename ComUnknown, typename Interface, typename Base>
		struct qi_interface
			: public Base
		{
			static unique_hresult qi(ComUnknown* that, REFIID riid, void** outInterface)
			{
				if (IsEqualIID(__uuidof(Interface), riid))
				{
					ifset::interface_cast<Interface>(that)->AddRef();
					*outInterface = ifset::interface_cast<Interface>(that);
					return unique_hresult::cast(S_OK);
				}
				return Base::qi(that, riid, outInterface);
			}
		};

		template<typename ComUnknown>
		struct qi_end
		{
			static unique_hresult qi(ComUnknown* , REFIID , void** )
			{
				return unique_hresult::cast(E_NOINTERFACE);
			}
		};

		template<typename ComUnknown, typename Cursor, typename Begin, typename End>
		struct qi_generator
		{
			typedef
				qi_interface<ComUnknown, typename Cursor::type, typename qi_generator<ComUnknown, typename Cursor::increment, Begin, End>::type>
			type;
		};

		template<typename ComUnknown, typename Cursor, typename Begin>
		struct qi_generator<ComUnknown, Cursor, Begin, Cursor>
		{
			typedef
				qi_end<ComUnknown>
			type;
		};

		template<typename ComObjectTag, template<typename Interface> class InterfaceBase, typename Base>
		struct com_unknown
			: public InterfaceBase<IUnknown>
			, public Base
		{
			HRESULT STDMETHODCALLTYPE QueryInterface( 
				REFIID riid,
				void** ppvObject)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						typedef
							qi_generator<
								com_unknown<ComObjectTag, InterfaceBase, Base>,
								typename ifset::traits<ComObjectTag>::type::interfaces::begin,
								typename ifset::traits<ComObjectTag>::type::interfaces::begin,
								typename ifset::traits<ComObjectTag>::type::interfaces::end
							>::type
						qi_interface;
						return qi_interface::qi(this, riid, ppvObject);
					}, 
					ifset::interface_tag<IUnknown>(), 
					ComObjectTag()
				);
			}

			ULONG STDMETHODCALLTYPE AddRef()
			{
				return interface_storage(
					this,
					ifset::interface_tag<IUnknown>(), 
					ComObjectTag()
				)->increment();
			}

			ULONG STDMETHODCALLTYPE Release()
			{
				return interface_storage(
					this,
					ifset::interface_tag<IUnknown>(), 
					ComObjectTag()
				)->decrement_and_destroy(this);
			}
		};
	}

	struct refcount
	{
		virtual ~refcount() {}

		refcount()
			: count(0)
		{}

		ULONG increment()
		{
			return ++count;
		}

		ULONG decrement_and_destroy(refcount* that)
		{
			auto result = --count;
			if (result == 0)
			{
				delete that;
			}
			return result;
		}

		ULONG count;
	};

	template<typename Interface, typename InterfaceSet>
	typename WINDOWS_RESOURCES_NAMESPACE::unique_com_interface<Interface>::type 
	interface_cast(InterfaceSet* interfaces)
	{
		auto result = ifset::interface_cast<Interface>(interfaces);
		result->AddRef();
		return result;
	}
}

template<template<typename Interface> class InterfaceBase, typename Base, typename ComObjectTag>
COM_NAMESPACE::detail::com_unknown<ComObjectTag, InterfaceBase, Base> 
interface_implementation(COM_NAMESPACE::ifset::interface_tag<IUnknown>&&, ComObjectTag&&);

#endif
