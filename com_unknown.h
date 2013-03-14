// Copyright (c) 2013, Kirk Shoop (kirk.shoop@gmail.com)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, 
//  are permitted provided that the following conditions are met:
//
//  - Redistributions of source code must retain the above copyright notice, 
//      this list of conditions and the following disclaimer.
//  - Redistributions in binary form must reproduce the above copyright notice, 
//      this list of conditions and the following disclaimer in the documentation 
//      and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
// USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
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
					return hresult_cast(S_OK);
				}
				return Base::qi(that, riid, outInterface);
			}
		};

		template<typename ComUnknown>
		struct qi_end
		{
			static unique_hresult qi(ComUnknown* , REFIID , void** )
			{
				return hresult_cast(E_NOINTERFACE);
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
						unique_hresult hresult(hresult_cast(E_NOINTERFACE));

						if (InlineIsEqualGUID(IID_IUnknown, riid))
						{
							// ensure that IUnknown is sent to the outer object
							hresult = interface_storage(
								storage_get(),
								ifset::interface_tag<IUnknown>(), 
								ComObjectTag()
							)->outer_qi(riid, ppvObject);
						}
						if (hresult == hresult_cast(E_NOINTERFACE))
						{
							hresult = qi_interface::qi(this, riid, ppvObject);
						}
						if (hresult == hresult_cast(E_NOINTERFACE))
						{
							// pass unsupported interface requests to the outer object
							hresult = interface_storage(
								storage_get(),
								ifset::interface_tag<IUnknown>(), 
								ComObjectTag()
							)->outer_qi(riid, ppvObject);
						}
						return hresult;
					}, 
					ifset::interface_tag<IUnknown>(), 
					ComObjectTag()
				);
			}

			ULONG STDMETHODCALLTYPE AddRef()
			{
				return interface_storage(
					storage_get(),
					ifset::interface_tag<IUnknown>(), 
					ComObjectTag()
				)->increment();
			}

			ULONG STDMETHODCALLTYPE Release()
			{
				return interface_storage(
					storage_get(),
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

		void interface_constructed(IUnknown*, ifset::interface_tag<IUnknown>&&) 
		{}

		unique_hresult outer_qi( 
			REFIID,// riid,
			void**)// ppvObject)
		{
			return hresult_cast(E_NOINTERFACE);
		}

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

	struct aggregating_refcount
	{
		virtual ~aggregating_refcount() {}

		aggregating_refcount()
			: count(1)
		{}

		aggregating_refcount(IUnknown* outerArg)
			: count(1)
			, outer(outerArg)
		{
			if (outer)
			{
				outer->AddRef();
			}
		}

		void interface_constructed(IUnknown*, ifset::interface_tag<IUnknown>&&) 
		{}

		unique_hresult outer_qi( 
			REFIID riid,
			void** ppvObject)
		{
			if (outer)
			{
				return hresult_cast(outer->QueryInterface(riid, ppvObject));
			}
			return hresult_cast(E_NOINTERFACE);
		}

		ULONG increment()
		{
			return ++count;
		}

		ULONG decrement_and_destroy(aggregating_refcount* that)
		{
			auto result = --count;
			if (result == 0)
			{
				delete that;
			}
			return result;
		}

		ULONG count;
		WINDOWS_RESOURCES_NAMESPACE::unique_com_unknown outer;
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

template<typename ComObjectTag>
COM_NAMESPACE::ifset::interface_traits_builder<COM_NAMESPACE::detail::com_unknown , COM_NAMESPACE::refcount>
interface_tag_traits(COM_NAMESPACE::ifset::interface_tag<IUnknown>&&, ComObjectTag&&);

#endif
