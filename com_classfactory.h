#ifndef COM_CLASSFACTORY_SOURCE
#define COM_CLASSFACTORY_SOURCE

#ifndef COM_NAMESPACE
#error COM_NAMESPACE must be defined
#endif

namespace COM_NAMESPACE
{
	namespace ifset=INTERFACE_SET_NAMESPACE;

	namespace detail
	{

		template<typename ComObjectTag, typename Base>
		struct com_classfactory
			: public Base
		{
			~com_classfactory()
			{}

			com_classfactory()
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(1, Param)>
			explicit com_classfactory(TPLT_FUNCTION_ARGUMENTS_DECL(1, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward))
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(2, Param)>
			com_classfactory(TPLT_FUNCTION_ARGUMENTS_DECL(2, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(2, Param, std::forward))
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(3, Param)>
			com_classfactory(TPLT_FUNCTION_ARGUMENTS_DECL(3, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(3, Param, std::forward))
			{}

			template<TPLT_TEMPLATE_ARGUMENTS_DECL(4, Param)>
			com_classfactory(TPLT_FUNCTION_ARGUMENTS_DECL(4, Param, , &&))
				: Base(TPLT_FUNCTION_ARGUMENTS_CAST(4, Param, std::forward))
			{}

			HRESULT STDMETHODCALLTYPE CreateInstance( 
				/* [annotation][unique][in] */ 
				_In_opt_  IUnknown *pUnkOuter,
				/* [annotation][in] */ 
				_In_  REFIID riid,
				/* [annotation][iid_is][out] */ 
				_COM_Outptr_  void **ppvObject)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						return interface_storage(
							storage_get(),
							ifset::interface_tag<IClassFactory>(), 
							ComObjectTag()
						)->create(pUnkOuter, riid, ppvObject);
					}, 
					ifset::interface_tag<IClassFactory>(), 
					ComObjectTag()
				);
			}
        
			HRESULT STDMETHODCALLTYPE LockServer( 
				/* [in] */ BOOL fLock)
			{
				return com_function_contract_hresult(
					[&]() -> unique_hresult
					{
						if (fLock)
						{
							return interface_storage(
								storage_get(),
								ifset::interface_tag<IClassFactory>(), 
								ComObjectTag()
							)->lock();
						}
						else
						{
							return interface_storage(
								storage_get(),
								ifset::interface_tag<IClassFactory>(), 
								ComObjectTag()
							)->unlock();
						}
					}, 
					ifset::interface_tag<IClassFactory>(), 
					ComObjectTag()
				);
			}

		};
	}

	template<typename FactoryTag>
	struct classfactory : public aggregating_refcount
	{
		classfactory()
			: count(1)
		{}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(1, Param)>
		explicit classfactory(TPLT_FUNCTION_ARGUMENTS_DECL(1, Param, , &&))
			: aggregating_refcount(TPLT_FUNCTION_ARGUMENTS_CAST(1, Param, std::forward))
		{}

		using aggregating_refcount::interface_constructed;
		void interface_constructed(IClassFactory*, ifset::interface_tag<IClassFactory>&&) 
		{}

		unique_hresult create(IUnknown *pUnkOuter, REFIID riid, void **ppvObject)
		{
			return factory_create(pUnkOuter, riid, ppvObject, FactoryTag());
		}

		unique_hresult lock()
		{
			++count;
			return hresult_cast(E_NOTIMPL);
		}

		unique_hresult unlock()
		{
			--count;
			return hresult_cast(E_NOTIMPL);
		}

		ULONG count;
	};

}

template<typename ComObjectTag>
COM_NAMESPACE::ifset::interface_traits_builder<COM_NAMESPACE::detail::com_classfactory , COM_NAMESPACE::classfactory<void>>
interface_tag_traits(COM_NAMESPACE::ifset::interface_tag<IClassFactory>&&, ComObjectTag&&);

#endif
