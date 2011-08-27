
#ifndef COMMON_SOURCE
#define COMMON_SOURCE

#ifndef COMMON_NAMESPACE
#error COMMON_NAMESPACE must be defined
#endif

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

#define TPLT_TEMPLATE_ARGUMENTS( Count, Prefix ) TPLT_TEMPLATE_ARGUMENTS_ ## Count (Prefix)
#define TPLT_TEMPLATE_ARGUMENTS_1( Prefix )  typename Prefix ## _T1 
#define TPLT_TEMPLATE_ARGUMENTS_2( Prefix )  TPLT_TEMPLATE_ARGUMENTS_1( Prefix ), typename Prefix ## _T2 
#define TPLT_TEMPLATE_ARGUMENTS_3( Prefix )  TPLT_TEMPLATE_ARGUMENTS_2( Prefix ), typename Prefix ## _T3 
#define TPLT_TEMPLATE_ARGUMENTS_4( Prefix )  TPLT_TEMPLATE_ARGUMENTS_3( Prefix ), typename Prefix ## _T4 
#define TPLT_TEMPLATE_ARGUMENTS_5( Prefix )  TPLT_TEMPLATE_ARGUMENTS_4( Prefix ), typename Prefix ## _T5 
#define TPLT_TEMPLATE_ARGUMENTS_6( Prefix )  TPLT_TEMPLATE_ARGUMENTS_5( Prefix ), typename Prefix ## _T6 
#define TPLT_TEMPLATE_ARGUMENTS_7( Prefix )  TPLT_TEMPLATE_ARGUMENTS_6( Prefix ), typename Prefix ## _T7 
#define TPLT_TEMPLATE_ARGUMENTS_8( Prefix )  TPLT_TEMPLATE_ARGUMENTS_7( Prefix ), typename Prefix ## _T8 
#define TPLT_TEMPLATE_ARGUMENTS_9( Prefix )  TPLT_TEMPLATE_ARGUMENTS_8( Prefix ), typename Prefix ## _T9 
#define TPLT_TEMPLATE_ARGUMENTS_10( Prefix ) TPLT_TEMPLATE_ARGUMENTS_9( Prefix ), typename Prefix ## _T10

#define TPLT_FUNCTION_ARGUMENTS_DECL( Count, Prefix, PreType, PostType ) TPLT_FUNCTION_ARGUMENTS_DECL_ ## Count (Prefix, PreType, PostType)
#define TPLT_FUNCTION_ARGUMENTS_DECL_1( Prefix, PreType, PostType )  PreType Prefix ## _T1 PostType Prefix ## _t1
#define TPLT_FUNCTION_ARGUMENTS_DECL_2( Prefix, PreType, PostType )  TPLT_FUNCTION_ARGUMENTS_DECL_1( Prefix, PreType, PostType ), PreType Prefix ## _T2 PostType Prefix ## _t2
#define TPLT_FUNCTION_ARGUMENTS_DECL_3( Prefix, PreType, PostType )  TPLT_FUNCTION_ARGUMENTS_DECL_2( Prefix, PreType, PostType ), PreType Prefix ## _T3 PostType Prefix ## _t3
#define TPLT_FUNCTION_ARGUMENTS_DECL_4( Prefix, PreType, PostType )  TPLT_FUNCTION_ARGUMENTS_DECL_3( Prefix, PreType, PostType ), PreType Prefix ## _T4 PostType Prefix ## _t4
#define TPLT_FUNCTION_ARGUMENTS_DECL_5( Prefix, PreType, PostType )  TPLT_FUNCTION_ARGUMENTS_DECL_4( Prefix, PreType, PostType ), PreType Prefix ## _T5 PostType Prefix ## _t5
#define TPLT_FUNCTION_ARGUMENTS_DECL_6( Prefix, PreType, PostType )  TPLT_FUNCTION_ARGUMENTS_DECL_5( Prefix, PreType, PostType ), PreType Prefix ## _T6 PostType Prefix ## _t6
#define TPLT_FUNCTION_ARGUMENTS_DECL_7( Prefix, PreType, PostType )  TPLT_FUNCTION_ARGUMENTS_DECL_6( Prefix, PreType, PostType ), PreType Prefix ## _T7 PostType Prefix ## _t7
#define TPLT_FUNCTION_ARGUMENTS_DECL_8( Prefix, PreType, PostType )  TPLT_FUNCTION_ARGUMENTS_DECL_7( Prefix, PreType, PostType ), PreType Prefix ## _T8 PostType Prefix ## _t8
#define TPLT_FUNCTION_ARGUMENTS_DECL_9( Prefix, PreType, PostType )  TPLT_FUNCTION_ARGUMENTS_DECL_8( Prefix, PreType, PostType ), PreType Prefix ## _T9 PostType Prefix ## _t9
#define TPLT_FUNCTION_ARGUMENTS_DECL_10( Prefix, PreType, PostType ) TPLT_FUNCTION_ARGUMENTS_DECL_9( Prefix, PreType, PostType ), PreType Prefix ## _T10 PostType Prefix ## _t10

#define TPLT_FUNCTION_ARGUMENTS_CALL( Count, Prefix, PreVar, PostVar ) TPLT_FUNCTION_ARGUMENTS_CALL_ ## Count (Prefix, PreVar, PostVar)
#define TPLT_FUNCTION_ARGUMENTS_CALL_1( Prefix, PreVar, PostVar )  PreVar Prefix ## _t1 PostVar
#define TPLT_FUNCTION_ARGUMENTS_CALL_2( Prefix, PreVar, PostVar )  TPLT_FUNCTION_ARGUMENTS_CALL_1( Prefix, PreVar, PostVar ), PreVar Prefix ## _t2 PostVar 
#define TPLT_FUNCTION_ARGUMENTS_CALL_3( Prefix, PreVar, PostVar )  TPLT_FUNCTION_ARGUMENTS_CALL_2( Prefix, PreVar, PostVar ), PreVar Prefix ## _t3 PostVar 
#define TPLT_FUNCTION_ARGUMENTS_CALL_4( Prefix, PreVar, PostVar )  TPLT_FUNCTION_ARGUMENTS_CALL_3( Prefix, PreVar, PostVar ), PreVar Prefix ## _t4 PostVar 
#define TPLT_FUNCTION_ARGUMENTS_CALL_5( Prefix, PreVar, PostVar )  TPLT_FUNCTION_ARGUMENTS_CALL_4( Prefix, PreVar, PostVar ), PreVar Prefix ## _t5 PostVar 
#define TPLT_FUNCTION_ARGUMENTS_CALL_6( Prefix, PreVar, PostVar )  TPLT_FUNCTION_ARGUMENTS_CALL_5( Prefix, PreVar, PostVar ), PreVar Prefix ## _t6 PostVar 
#define TPLT_FUNCTION_ARGUMENTS_CALL_7( Prefix, PreVar, PostVar )  TPLT_FUNCTION_ARGUMENTS_CALL_6( Prefix, PreVar, PostVar ), PreVar Prefix ## _t7 PostVar 
#define TPLT_FUNCTION_ARGUMENTS_CALL_8( Prefix, PreVar, PostVar )  TPLT_FUNCTION_ARGUMENTS_CALL_7( Prefix, PreVar, PostVar ), PreVar Prefix ## _t8 PostVar 
#define TPLT_FUNCTION_ARGUMENTS_CALL_9( Prefix, PreVar, PostVar )  TPLT_FUNCTION_ARGUMENTS_CALL_8( Prefix, PreVar, PostVar ), PreVar Prefix ## _t9 PostVar 
#define TPLT_FUNCTION_ARGUMENTS_CALL_10( Prefix, PreVar, PostVar ) TPLT_FUNCTION_ARGUMENTS_CALL_9( Prefix, PreVar, PostVar ), PreVar Prefix ## _t10 PostVar 

#define TPLT_FUNCTION_ARGUMENTS_CAST( Count, Prefix, Cast ) TPLT_FUNCTION_ARGUMENTS_CAST_ ## Count (Prefix, Cast)
#define TPLT_FUNCTION_ARGUMENTS_CAST_1( Prefix, Cast )  Cast <Prefix ## _T1>  (Prefix ## _t1)
#define TPLT_FUNCTION_ARGUMENTS_CAST_2( Prefix, Cast )  TPLT_FUNCTION_ARGUMENTS_CAST_1( Prefix, Cast ), Cast <Prefix ## _T2>  (Prefix ## _t2)
#define TPLT_FUNCTION_ARGUMENTS_CAST_3( Prefix, Cast )  TPLT_FUNCTION_ARGUMENTS_CAST_2( Prefix, Cast ), Cast <Prefix ## _T3>  (Prefix ## _t3)
#define TPLT_FUNCTION_ARGUMENTS_CAST_4( Prefix, Cast )  TPLT_FUNCTION_ARGUMENTS_CAST_3( Prefix, Cast ), Cast <Prefix ## _T4>  (Prefix ## _t4)
#define TPLT_FUNCTION_ARGUMENTS_CAST_5( Prefix, Cast )  TPLT_FUNCTION_ARGUMENTS_CAST_4( Prefix, Cast ), Cast <Prefix ## _T5>  (Prefix ## _t5)
#define TPLT_FUNCTION_ARGUMENTS_CAST_6( Prefix, Cast )  TPLT_FUNCTION_ARGUMENTS_CAST_5( Prefix, Cast ), Cast <Prefix ## _T6>  (Prefix ## _t6)
#define TPLT_FUNCTION_ARGUMENTS_CAST_7( Prefix, Cast )  TPLT_FUNCTION_ARGUMENTS_CAST_6( Prefix, Cast ), Cast <Prefix ## _T7>  (Prefix ## _t7)
#define TPLT_FUNCTION_ARGUMENTS_CAST_8( Prefix, Cast )  TPLT_FUNCTION_ARGUMENTS_CAST_7( Prefix, Cast ), Cast <Prefix ## _T8>  (Prefix ## _t8)
#define TPLT_FUNCTION_ARGUMENTS_CAST_9( Prefix, Cast )  TPLT_FUNCTION_ARGUMENTS_CAST_8( Prefix, Cast ), Cast <Prefix ## _T9>  (Prefix ## _t9)
#define TPLT_FUNCTION_ARGUMENTS_CAST_10( Prefix, Cast ) TPLT_FUNCTION_ARGUMENTS_CAST_9( Prefix, Cast ), Cast <Prefix ## _T10>  (Prefix ## _t10)

#define TPLT_FUNCTION_ARGUMENT_INSTANCES( Count, ... ) TPLT_FUNCTION_ARGUMENT_INSTANCES_ ## Count (__VA_ARGS__)
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_1( A1 )  WIN32_WINDOW_NAMESPACE::instance_of<A1>::value
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_2( A1, A2 )  TPLT_FUNCTION_ARGUMENT_INSTANCES_1( A1 ),  WIN32_WINDOW_NAMESPACE::instance_of<A2>::value
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_3( A1, A2, A3 )  TPLT_FUNCTION_ARGUMENT_INSTANCES_2( A1, A2 ),  WIN32_WINDOW_NAMESPACE::instance_of<A3>::value
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_4( A1, A2, A3, A4 )  TPLT_FUNCTION_ARGUMENT_INSTANCES_3( A1, A2, A3 ),  WIN32_WINDOW_NAMESPACE::instance_of<A4>::value
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_5( A1, A2, A3, A4, A5 )  TPLT_FUNCTION_ARGUMENT_INSTANCES_4( A1, A2, A3, A4 ),  WIN32_WINDOW_NAMESPACE::instance_of<A5>::value
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_6( A1, A2, A3, A4, A5, A6 )  TPLT_FUNCTION_ARGUMENT_INSTANCES_5( A1, A2, A3, A4, A5 ),  WIN32_WINDOW_NAMESPACE::instance_of<A6>::value
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_7( A1, A2, A3, A4, A5, A6, A7 )  TPLT_FUNCTION_ARGUMENT_INSTANCES_6( A1, A2, A3, A4, A5, A6 ),  WIN32_WINDOW_NAMESPACE::instance_of<A7>::value
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_8( A1, A2, A3, A4, A5, A6, A7, A8 )  TPLT_FUNCTION_ARGUMENT_INSTANCES_7( A1, A2, A3, A4, A5, A6, A7 ),  WIN32_WINDOW_NAMESPACE::instance_of<A8>::value
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_9( A1, A2, A3, A4, A5, A6, A7, A8, A9 )  TPLT_FUNCTION_ARGUMENT_INSTANCES_8( A1, A2, A3, A4, A5, A6, A7, A8 ),  WIN32_WINDOW_NAMESPACE::instance_of<A9>::value
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_10( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10 ) TPLT_FUNCTION_ARGUMENT_INSTANCES_9( A1, A2, A3, A4, A5, A6, A7, A8, A9 ), WIN32_WINDOW_NAMESPACE::instance_of<A10>::value

#define MAKE_IDENTIFIER_EXPLICIT_PASTER(Prefix, Suffix) Prefix ## Suffix

#define MAKE_IDENTIFIER_EXPLICIT(Prefix, Suffix) MAKE_IDENTIFIER_EXPLICIT_PASTER(Prefix, Suffix)

#define MAKE_IDENTIFIER(Prefix) MAKE_IDENTIFIER_EXPLICIT(Prefix, __LINE__)

namespace COMMON_NAMESPACE
{
	template<typename T>
	struct instance_of
	{
		static T value;
	};

	template<typename T>
	class unspecified_bool
	{
	private:
		inline void bool_true () {};
	public:
		typedef
			void (unspecified_bool::*type)();

		static type get(bool value)
		{
			return value ? &unspecified_bool::bool_true : nullptr;
		}
	};

	template<typename L, typename R>
	bool operator==(typename unspecified_bool<L>::type, typename unspecified_bool<R>::type);

	template<typename L, typename R>
	bool operator!=(typename unspecified_bool<L>::type, typename unspecified_bool<R>::type);

	template<typename L, typename R>
	bool operator<(typename unspecified_bool<L>::type, typename unspecified_bool<R>::type);


	template<typename T>
	struct type_trait
	{
		typedef T type;
	};

	inline
	HINSTANCE GetCurrentInstance(){ return ((HINSTANCE)&__ImageBase); }

	inline
	LONG WINAPI FailFastFilter(__in  struct _EXCEPTION_POINTERS *exceptionInfo)
	{
		RaiseFailFastException(exceptionInfo->ExceptionRecord, exceptionInfo->ContextRecord, 0);
		return EXCEPTION_CONTINUE_EXECUTION;
	}

}


#endif // COMMON_SOURCE