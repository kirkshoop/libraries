
#ifndef COMMON_SOURCE
#define COMMON_SOURCE

#ifndef COMMON_NAMESPACE
#error COMMON_NAMESPACE must be defined
#endif

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

#define TPLT_COMMA ,

#if 0
#define TPLT_HAS_MAX_ARG(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) _15
#define TPLT_HAS_COMMA(...) TPLT_HAS_MAX_ARG(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0)
#define TPLT_HAS_NO_COMMA(...) TPLT_HAS_MAX_ARG(__VA_ARGS__, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1)
#define TPLT_TRIGGER_PARENTHESIS_(...) ,
 
#define TPLT_HAS_ZERO_OR_ONE_ARGS(...) \
 TPLT_DETAIL_HAS_ZERO_OR_ONE_ARGS( \
   /* test if there is just one argument, eventually an empty \
   one */ \
   TPLT_HAS_COMMA(__VA_ARGS__), \
   /* test if _TRIGGER_PARENTHESIS_ together with the argument \
   adds a comma */ \
   TPLT_HAS_COMMA(TPLT_TRIGGER_PARENTHESIS_ __VA_ARGS__), \
   /* test if the argument together with a parenthesis \
   adds a comma */ \
   TPLT_HAS_COMMA(__VA_ARGS__ (~)), \
   /* test if placing it between _TRIGGER_PARENTHESIS_ and the \
   parenthesis adds a comma */ \
   TPLT_HAS_COMMA(TPLT_TRIGGER_PARENTHESIS_ __VA_ARGS__ (~)) \
 )
 
#define TPLT_PASTE5(_0, _1, _2, _3, _4) _0 ## _1 ## _2 ## _3 ## _4
#define TPLT_DETAIL_HAS_ZERO_OR_ONE_ARGS(_0, _1, _2, _3) TPLT_HAS_NO_COMMA(TPLT_PASTE5(TPLT_IS_EMPTY_CASE_, _0, _1, _2, _3))
#define TPLT_IS_EMPTY_CASE_0001 ,

#define TPLT_VA0(...) TPLT_HAS_ZERO_OR_ONE_ARGS(__VA_ARGS__)
#define TPLT_VA1(...) TPLT_HAS_ZERO_OR_ONE_ARGS(__VA_ARGS__)
#define TPLT_VA2(...) 2
#define TPLT_VA3(...) 3
#define TPLT_VA4(...) 4
#define TPLT_VA5(...) 5
#define TPLT_VA6(...) 6
#define TPLT_VA7(...) 7
#define TPLT_VA8(...) 8
#define TPLT_VA9(...) 9
#define TPLT_VA10(...) 10
#define TPLT_VA11(...) 11
#define TPLT_VA12(...) 12
#define TPLT_VA13(...) 13
#define TPLT_VA14(...) 14
#define TPLT_VA15(...) 15
#define TPLT_VA16(...) 16
 
#define TPLT_VA_NUM_ARGS(...) TPLT_VA_NUM_ARGS_IMPL(__VA_ARGS__, TPLT_PP_RSEQ_N(__VA_ARGS__)) 
#define TPLT_VA_NUM_ARGS_IMPL(...) TPLT_VA_NUM_ARGS_N(__VA_ARGS__,,,,,,,,,,,,,,,,,,)

#define TPLT_VA_NUM_ARGS_N( \
 _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
 _11,_12,_13,_14,_15,_16,N,...) N 

#define TPLT_PP_RSEQ_N(...) \
 TPLT_VA16(__VA_ARGS__),TPLT_VA15(__VA_ARGS__),TPLT_VA14(__VA_ARGS__),TPLT_VA13(__VA_ARGS__),\
 TPLT_VA12(__VA_ARGS__),TPLT_VA11(__VA_ARGS__),TPLT_VA10(__VA_ARGS__),TPLT_VA9(__VA_ARGS__),\
 TPLT_VA8(__VA_ARGS__),TPLT_VA7(__VA_ARGS__),TPLT_VA6(__VA_ARGS__),TPLT_VA5(__VA_ARGS__),\
 TPLT_VA4(__VA_ARGS__),TPLT_VA3(__VA_ARGS__),TPLT_VA2(__VA_ARGS__),TPLT_VA1(__VA_ARGS__),\
 TPLT_VA0(__VA_ARGS__) 
#endif

#define TPLT_CALL( Op, ArgList ) Op ArgList

#define TPLT_NON_ZERO( Count, ... ) TPLT_CALL(MAKE_IDENTIFIER_EXPLICIT(TPLT_NON_ZERO_, Count), (__VA_ARGS__))
#define TPLT_NON_ZERO_0( ... )  
#define TPLT_NON_ZERO_1( ... )   __VA_ARGS__
#define TPLT_NON_ZERO_2( ... )   __VA_ARGS__
#define TPLT_NON_ZERO_3( ... )   __VA_ARGS__
#define TPLT_NON_ZERO_4( ... )   __VA_ARGS__
#define TPLT_NON_ZERO_5( ... )   __VA_ARGS__
#define TPLT_NON_ZERO_6( ... )   __VA_ARGS__
#define TPLT_NON_ZERO_7( ... )   __VA_ARGS__
#define TPLT_NON_ZERO_8( ... )   __VA_ARGS__
#define TPLT_NON_ZERO_9( ... )   __VA_ARGS__
#define TPLT_NON_ZERO_10( ... )  __VA_ARGS__

#define TPLT_EXTRACT( Index, ... ) TPLT_CALL(MAKE_IDENTIFIER_EXPLICIT(TPLT_EXTRACT_, Index), (__VA_ARGS__,,,,,,,,,,))
#define TPLT_EXTRACT_0( A0, ... )  A0
#define TPLT_EXTRACT_1( A0, A1, ... )  A1
#define TPLT_EXTRACT_2( A0, A1, A2, ... )  A2
#define TPLT_EXTRACT_3( A0, A1, A2, A3, ... )  A3
#define TPLT_EXTRACT_4( A0, A1, A2, A3, A4, ... )  A4
#define TPLT_EXTRACT_5( A0, A1, A2, A3, A4, A5, ... )  A5
#define TPLT_EXTRACT_6( A0, A1, A2, A3, A4, A5, A6, ... )  A6
#define TPLT_EXTRACT_7( A0, A1, A2, A3, A4, A5, A6, A7, ... )  A7
#define TPLT_EXTRACT_8( A0, A1, A2, A3, A4, A5, A6, A7, A8, ... )  A8
#define TPLT_EXTRACT_9( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, ... )  A9
#define TPLT_EXTRACT_10( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, ... ) A10

#define TPLT_ARGUMENTS_APPEND_LIST( ListCount, List, ...) (__VA_ARGS__, MAKE_IDENTIFIER_EXPLICIT(TPLT_ARGUMENTS_APPEND_LIST_, ListCount) List)
#define TPLT_ARGUMENTS_APPEND_LIST_0( )   
#define TPLT_ARGUMENTS_APPEND_LIST_1( A0 )  A0 
#define TPLT_ARGUMENTS_APPEND_LIST_2( A0, A1 )  A0, A1
#define TPLT_ARGUMENTS_APPEND_LIST_3( A0, A1, A2 )  A0, A1, A2
#define TPLT_ARGUMENTS_APPEND_LIST_4( A0, A1, A2, A3 )  A0, A1, A2, A3
#define TPLT_ARGUMENTS_APPEND_LIST_5( A0, A1, A2, A3, A4 )  A0, A1, A2, A3, A4
#define TPLT_ARGUMENTS_APPEND_LIST_6( A0, A1, A2, A3, A4, A5 )  A0, A1, A2, A3, A4, A5
#define TPLT_ARGUMENTS_APPEND_LIST_7( A0, A1, A2, A3, A4, A5, A6 )  A0, A1, A2, A3, A4, A5, A6
#define TPLT_ARGUMENTS_APPEND_LIST_8( A0, A1, A2, A3, A4, A5, A6, A7 )  A0, A1, A2, A3, A4, A5, A6, A7
#define TPLT_ARGUMENTS_APPEND_LIST_9( A0, A1, A2, A3, A4, A5, A6, A7, A8 )  A0, A1, A2, A3, A4, A5, A6, A7, A8
#define TPLT_ARGUMENTS_APPEND_LIST_10( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9 )  A0, A1, A2, A3, A4, A5, A6, A7, A8, A9

#define TPLT_ARGUMENTS_CALL( Count, Argument) MAKE_IDENTIFIER_EXPLICIT(TPLT_ARGUMENTS_CALL_, Count) (Argument)
#define TPLT_ARGUMENTS_CALL_1( Argument )  Argument 
#define TPLT_ARGUMENTS_CALL_2( Argument )  TPLT_ARGUMENTS_CALL_1( Argument ), Argument
#define TPLT_ARGUMENTS_CALL_3( Argument )  TPLT_ARGUMENTS_CALL_2( Argument ), Argument
#define TPLT_ARGUMENTS_CALL_4( Argument )  TPLT_ARGUMENTS_CALL_3( Argument ), Argument
#define TPLT_ARGUMENTS_CALL_5( Argument )  TPLT_ARGUMENTS_CALL_4( Argument ), Argument
#define TPLT_ARGUMENTS_CALL_6( Argument )  TPLT_ARGUMENTS_CALL_5( Argument ), Argument
#define TPLT_ARGUMENTS_CALL_7( Argument )  TPLT_ARGUMENTS_CALL_6( Argument ), Argument
#define TPLT_ARGUMENTS_CALL_8( Argument )  TPLT_ARGUMENTS_CALL_7( Argument ), Argument
#define TPLT_ARGUMENTS_CALL_9( Argument )  TPLT_ARGUMENTS_CALL_8( Argument ), Argument
#define TPLT_ARGUMENTS_CALL_10( Argument ) TPLT_ARGUMENTS_CALL_9( Argument ), Argument

#define TPLT_TEMPLATE_ARGUMENTS_DECL( Count, Prefix ) TPLT_CALL(MAKE_IDENTIFIER_EXPLICIT(TPLT_TEMPLATE_ARGUMENTS_DECL_, Count), (Prefix))
#define TPLT_TEMPLATE_ARGUMENTS_DECL_0( Prefix )  
#define TPLT_TEMPLATE_ARGUMENTS_DECL_1( Prefix )  typename Prefix ## _T1 
#define TPLT_TEMPLATE_ARGUMENTS_DECL_2( Prefix )  TPLT_TEMPLATE_ARGUMENTS_DECL_1( Prefix ), typename Prefix ## _T2 
#define TPLT_TEMPLATE_ARGUMENTS_DECL_3( Prefix )  TPLT_TEMPLATE_ARGUMENTS_DECL_2( Prefix ), typename Prefix ## _T3 
#define TPLT_TEMPLATE_ARGUMENTS_DECL_4( Prefix )  TPLT_TEMPLATE_ARGUMENTS_DECL_3( Prefix ), typename Prefix ## _T4 
#define TPLT_TEMPLATE_ARGUMENTS_DECL_5( Prefix )  TPLT_TEMPLATE_ARGUMENTS_DECL_4( Prefix ), typename Prefix ## _T5 
#define TPLT_TEMPLATE_ARGUMENTS_DECL_6( Prefix )  TPLT_TEMPLATE_ARGUMENTS_DECL_5( Prefix ), typename Prefix ## _T6 
#define TPLT_TEMPLATE_ARGUMENTS_DECL_7( Prefix )  TPLT_TEMPLATE_ARGUMENTS_DECL_6( Prefix ), typename Prefix ## _T7 
#define TPLT_TEMPLATE_ARGUMENTS_DECL_8( Prefix )  TPLT_TEMPLATE_ARGUMENTS_DECL_7( Prefix ), typename Prefix ## _T8 
#define TPLT_TEMPLATE_ARGUMENTS_DECL_9( Prefix )  TPLT_TEMPLATE_ARGUMENTS_DECL_8( Prefix ), typename Prefix ## _T9 
#define TPLT_TEMPLATE_ARGUMENTS_DECL_10( Prefix ) TPLT_TEMPLATE_ARGUMENTS_DECL_9( Prefix ), typename Prefix ## _T10

#define TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL( Count, Prefix, Default ) MAKE_IDENTIFIER_EXPLICIT(TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_, Count)(Prefix, Default)
#define TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_1( Prefix, Default )  typename Prefix ## _T1 = Default
#define TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_2( Prefix, Default )  TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_1( Prefix, Default ), typename Prefix ## _T2  = Default
#define TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_3( Prefix, Default )  TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_2( Prefix, Default ), typename Prefix ## _T3  = Default
#define TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_4( Prefix, Default )  TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_3( Prefix, Default ), typename Prefix ## _T4  = Default
#define TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_5( Prefix, Default )  TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_4( Prefix, Default ), typename Prefix ## _T5  = Default
#define TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_6( Prefix, Default )  TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_5( Prefix, Default ), typename Prefix ## _T6  = Default
#define TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_7( Prefix, Default )  TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_6( Prefix, Default ), typename Prefix ## _T7  = Default
#define TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_8( Prefix, Default )  TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_7( Prefix, Default ), typename Prefix ## _T8  = Default
#define TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_9( Prefix, Default )  TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_8( Prefix, Default ), typename Prefix ## _T9  = Default
#define TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_10( Prefix, Default ) TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL_9( Prefix, Default ), typename Prefix ## _T10 = Default

#define TPLT_TEMPLATE_ARGUMENTS_CALL( Count, Prefix) MAKE_IDENTIFIER_EXPLICIT(TPLT_TEMPLATE_ARGUMENTS_CALL_, Count)(Prefix)
#define TPLT_TEMPLATE_ARGUMENTS_CALL_1( Prefix )  Prefix ## _T1 
#define TPLT_TEMPLATE_ARGUMENTS_CALL_2( Prefix )  TPLT_TEMPLATE_ARGUMENTS_CALL_1( Prefix ), Prefix ## _T2 
#define TPLT_TEMPLATE_ARGUMENTS_CALL_3( Prefix )  TPLT_TEMPLATE_ARGUMENTS_CALL_2( Prefix ), Prefix ## _T3 
#define TPLT_TEMPLATE_ARGUMENTS_CALL_4( Prefix )  TPLT_TEMPLATE_ARGUMENTS_CALL_3( Prefix ), Prefix ## _T4 
#define TPLT_TEMPLATE_ARGUMENTS_CALL_5( Prefix )  TPLT_TEMPLATE_ARGUMENTS_CALL_4( Prefix ), Prefix ## _T5 
#define TPLT_TEMPLATE_ARGUMENTS_CALL_6( Prefix )  TPLT_TEMPLATE_ARGUMENTS_CALL_5( Prefix ), Prefix ## _T6 
#define TPLT_TEMPLATE_ARGUMENTS_CALL_7( Prefix )  TPLT_TEMPLATE_ARGUMENTS_CALL_6( Prefix ), Prefix ## _T7 
#define TPLT_TEMPLATE_ARGUMENTS_CALL_8( Prefix )  TPLT_TEMPLATE_ARGUMENTS_CALL_7( Prefix ), Prefix ## _T8 
#define TPLT_TEMPLATE_ARGUMENTS_CALL_9( Prefix )  TPLT_TEMPLATE_ARGUMENTS_CALL_8( Prefix ), Prefix ## _T9 
#define TPLT_TEMPLATE_ARGUMENTS_CALL_10( Prefix ) TPLT_TEMPLATE_ARGUMENTS_CALL_9( Prefix ), Prefix ## _T10 

#define TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL( Count, Prefix) MAKE_IDENTIFIER_EXPLICIT(TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL_, Count)(Prefix)
#define TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL_1( Prefix )  Prefix ## _T2 
#define TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL_2( Prefix )  TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL_1( Prefix ), Prefix ## _T3 
#define TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL_3( Prefix )  TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL_2( Prefix ), Prefix ## _T4 
#define TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL_4( Prefix )  TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL_3( Prefix ), Prefix ## _T5 
#define TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL_5( Prefix )  TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL_4( Prefix ), Prefix ## _T6 
#define TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL_6( Prefix )  TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL_5( Prefix ), Prefix ## _T7 
#define TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL_7( Prefix )  TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL_6( Prefix ), Prefix ## _T8 
#define TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL_8( Prefix )  TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL_7( Prefix ), Prefix ## _T9 
#define TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL_9( Prefix )  TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL_8( Prefix ), Prefix ## _T10 

#define TPLT_FUNCTION_ARGUMENTS_DECL( Count, Prefix, PreType, PostType ) MAKE_IDENTIFIER_EXPLICIT(TPLT_FUNCTION_ARGUMENTS_DECL_, Count)(Prefix, PreType, PostType)
#define TPLT_FUNCTION_ARGUMENTS_DECL_0( Prefix, PreType, PostType )  
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

#define TPLT_FUNCTION_ARGUMENTS_CALL( Count, Prefix, PreVar, PostVar ) MAKE_IDENTIFIER_EXPLICIT(TPLT_FUNCTION_ARGUMENTS_CALL_, Count)(Prefix, PreVar, PostVar)
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

#define TPLT_FUNCTION_ARGUMENTS_CAST( Count, Prefix, Cast ) MAKE_IDENTIFIER_EXPLICIT(TPLT_FUNCTION_ARGUMENTS_CAST_, Count)(Prefix, Cast)
#define TPLT_FUNCTION_ARGUMENTS_CAST_0( Prefix, Cast )  
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

#define TPLT_FUNCTION_ARGUMENT_INSTANCES( Count, ... ) TPLT_CALL(MAKE_IDENTIFIER_EXPLICIT(TPLT_FUNCTION_ARGUMENT_INSTANCES_, Count), (__VA_ARGS__,,,,,,,,,,))
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_0(...)  
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_1( A1, ... )  COMMON_NAMESPACE::instance_of<A1>::value
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_2( A1, A2, ... )  TPLT_FUNCTION_ARGUMENT_INSTANCES_1( A1 ),  COMMON_NAMESPACE::instance_of<A2>::value
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_3( A1, A2, A3, ... )  TPLT_FUNCTION_ARGUMENT_INSTANCES_2( A1, A2 ),  COMMON_NAMESPACE::instance_of<A3>::value
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_4( A1, A2, A3, A4, ... )  TPLT_FUNCTION_ARGUMENT_INSTANCES_3( A1, A2, A3 ),  COMMON_NAMESPACE::instance_of<A4>::value
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_5( A1, A2, A3, A4, A5, ... )  TPLT_FUNCTION_ARGUMENT_INSTANCES_4( A1, A2, A3, A4 ),  COMMON_NAMESPACE::instance_of<A5>::value
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_6( A1, A2, A3, A4, A5, A6, ... )  TPLT_FUNCTION_ARGUMENT_INSTANCES_5( A1, A2, A3, A4, A5 ),  COMMON_NAMESPACE::instance_of<A6>::value
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_7( A1, A2, A3, A4, A5, A6, A7, ... )  TPLT_FUNCTION_ARGUMENT_INSTANCES_6( A1, A2, A3, A4, A5, A6 ),  COMMON_NAMESPACE::instance_of<A7>::value
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_8( A1, A2, A3, A4, A5, A6, A7, A8, ... )  TPLT_FUNCTION_ARGUMENT_INSTANCES_7( A1, A2, A3, A4, A5, A6, A7 ),  COMMON_NAMESPACE::instance_of<A8>::value
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_9( A1, A2, A3, A4, A5, A6, A7, A8, A9, ... )  TPLT_FUNCTION_ARGUMENT_INSTANCES_8( A1, A2, A3, A4, A5, A6, A7, A8 ),  COMMON_NAMESPACE::instance_of<A9>::value
#define TPLT_FUNCTION_ARGUMENT_INSTANCES_10( A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, ... ) TPLT_FUNCTION_ARGUMENT_INSTANCES_9( A1, A2, A3, A4, A5, A6, A7, A8, A9 ), COMMON_NAMESPACE::instance_of<A10>::value


#define MAKE_IDENTIFIER_EXPLICIT_PASTER(Prefix, Suffix) Prefix ## Suffix

#define MAKE_IDENTIFIER_EXPLICIT_PASTER_1(Prefix, Suffix) MAKE_IDENTIFIER_EXPLICIT_PASTER(Prefix, Suffix)
#define MAKE_IDENTIFIER_EXPLICIT_PASTER_2(Prefix, Suffix) MAKE_IDENTIFIER_EXPLICIT_PASTER_1(Prefix, Suffix)
#define MAKE_IDENTIFIER_EXPLICIT_PASTER_3(Prefix, Suffix) MAKE_IDENTIFIER_EXPLICIT_PASTER_2(Prefix, Suffix)
#define MAKE_IDENTIFIER_EXPLICIT_PASTER_4(Prefix, Suffix) MAKE_IDENTIFIER_EXPLICIT_PASTER_3(Prefix, Suffix)
#define MAKE_IDENTIFIER_EXPLICIT_PASTER_5(Prefix, Suffix) MAKE_IDENTIFIER_EXPLICIT_PASTER_4(Prefix, Suffix)
#define MAKE_IDENTIFIER_EXPLICIT(Prefix, Suffix) MAKE_IDENTIFIER_EXPLICIT_PASTER_5(Prefix, Suffix)

#define MAKE_IDENTIFIER(Prefix) MAKE_IDENTIFIER_EXPLICIT(Prefix, __LINE__)

#define FAIL_FAST_FILTER() \
	__except(COMMON_NAMESPACE::FailFastFilter(GetExceptionInformation())) \
	{ \
	} do {} while(0,0)

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
		return EXCEPTION_CONTINUE_SEARCH;
	}

	template<typename Function>
	auto FailFastOnThrow(Function&& function) -> decltype(std::forward<Function>(function)())
	{
		//
		// __ try must be isolated in its own function in order for the 
		// compiler to reason about C++ unwind in the calling and called 
		// functions.
		//
		__try 
		{ 
			return std::forward<Function>(function)();
		} 
		FAIL_FAST_FILTER();
	}

	template<typename T>
	void inspect(T&& t)
	{
		static_assert(false, "inspector");
	}
}

#define FAIL_FAST_ON_THROW(Function) \
	COMMON_NAMESPACE::FailFastOnThrow((Function))

#define FAIL_FAST(Code) \
	FAIL_FAST_ON_THROW([&]{RaiseException((Code), EXCEPTION_NONCONTINUABLE, 0, nullptr);})

#define FAIL_FAST_IF(Expression, Code) \
	if (Expression) \
	{ \
		FAIL_FAST(Code); \
	} else {} do {} while(0,0)

#endif // COMMON_SOURCE