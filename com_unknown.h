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

		template<typename ComObjectTag, typename Base>
		struct com_unknown
			: public Base
		{
			~com_unknown()
			{}

			com_unknown()
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(1, Param)>
			explicit com_unknown(TPLT_FUNCTION_ARGUMENTS_DECL(1, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward))
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(2, Param)>
			com_unknown(TPLT_FUNCTION_ARGUMENTS_DECL(2, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(2, Param, std::forward))
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(3, Param)>
			com_unknown(TPLT_FUNCTION_ARGUMENTS_DECL(3, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(3, Param, std::forward))
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(4, Param)>
			com_unknown(TPLT_FUNCTION_ARGUMENTS_DECL(4, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(4, Param, std::forward))
			{}

			HRESULT STDMETHODCALLTYPE QueryInterface( 
				REFIID riid,
				void** ppvObject)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						typedef
							qi_generator<
								com_unknown<ComObjectTag, Base>,
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
			: count(1)
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

template<typename Base, typename ComObjectTag>
COM_NAMESPACE::detail::com_unknown<ComObjectTag, Base> 
interface_implementation(COM_NAMESPACE::ifset::interface_tag<IUnknown>&&, ComObjectTag&&);

#endif
