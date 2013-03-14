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
#ifndef TYPE_VECTOR_SOURCE
#define TYPE_VECTOR_SOURCE

#ifndef TYPE_VECTOR_NAMESPACE
#error TYPE_VECTOR_NAMESPACE must be defined
#endif

namespace TYPE_VECTOR_NAMESPACE
{
	namespace cmn=COMMON_NAMESPACE;

	struct invalid {};

#define TVEC_VECTOR_IMPL(Count) \
	typedef \
		TPLT_TEMPLATE_ARGUMENTS_CALL( 1, Type) \
	head; \
	typedef \
		vector_ ## Count <TPLT_TEMPLATE_ARGUMENTS_CALL_TAIL( Count, Type)> \
	tail; 

	template<TPLT_TEMPLATE_ARGUMENTS_DECL( 1, Type)> struct vector_1 
	{
		typedef 
			TPLT_TEMPLATE_ARGUMENTS_CALL( 1, Type) 
		head; 

		typedef 
			invalid
		tail; 
	};
	template<TPLT_TEMPLATE_ARGUMENTS_DECL( 2, Type)> struct vector_2  {TVEC_VECTOR_IMPL( 1)};
	template<TPLT_TEMPLATE_ARGUMENTS_DECL( 3, Type)> struct vector_3  {TVEC_VECTOR_IMPL( 2)};
	template<TPLT_TEMPLATE_ARGUMENTS_DECL( 4, Type)> struct vector_4  {TVEC_VECTOR_IMPL( 3)};
	template<TPLT_TEMPLATE_ARGUMENTS_DECL( 5, Type)> struct vector_5  {TVEC_VECTOR_IMPL( 4)};
	template<TPLT_TEMPLATE_ARGUMENTS_DECL( 6, Type)> struct vector_6  {TVEC_VECTOR_IMPL( 5)};
	template<TPLT_TEMPLATE_ARGUMENTS_DECL( 7, Type)> struct vector_7  {TVEC_VECTOR_IMPL( 6)};
	template<TPLT_TEMPLATE_ARGUMENTS_DECL( 8, Type)> struct vector_8  {TVEC_VECTOR_IMPL( 7)};
	template<TPLT_TEMPLATE_ARGUMENTS_DECL( 9, Type)> struct vector_9  {TVEC_VECTOR_IMPL( 8)};
	template<TPLT_TEMPLATE_ARGUMENTS_DECL(10, Type)> struct vector_10 {TVEC_VECTOR_IMPL( 9)};

	template<typename Vector>
	struct forward_iterator
	{
		typedef
			typename Vector::head
		type;

		typedef
			forward_iterator<typename Vector::tail>
		increment;
	};

	template<>
	struct forward_iterator<invalid>
	{
		typedef
			invalid
		type;

		typedef
			forward_iterator<invalid>
		increment;
	};

	typedef
		forward_iterator<invalid>
	end_forward_iterator;

	template <typename Begin = forward_iterator<invalid>, typename End = forward_iterator<invalid>>
	struct vector
	{
		typedef
			Begin
		begin;

		typedef
			End
		end;
	};

	template<TPLT_TEMPLATE_ARGUMENTS_DEFAULT_DECL(10, Type, invalid)> struct factory 
		: public cmn::type_trait<vector<forward_iterator<vector_10<TPLT_TEMPLATE_ARGUMENTS_CALL(10, Type)>>>> {};

	template<TPLT_TEMPLATE_ARGUMENTS_DECL( 9, Type)> 
	struct factory<TPLT_TEMPLATE_ARGUMENTS_CALL( 9, Type), TPLT_ARGUMENTS_CALL(1, invalid)>
		: public cmn::type_trait<vector<forward_iterator<vector_9<TPLT_TEMPLATE_ARGUMENTS_CALL( 9, Type)>>>> {};

	template<TPLT_TEMPLATE_ARGUMENTS_DECL( 8, Type)> 
	struct factory<TPLT_TEMPLATE_ARGUMENTS_CALL( 8, Type), TPLT_ARGUMENTS_CALL(2, invalid)>
		: public cmn::type_trait<vector<forward_iterator<vector_8<TPLT_TEMPLATE_ARGUMENTS_CALL( 8, Type)>>>> {};

	template<TPLT_TEMPLATE_ARGUMENTS_DECL( 7, Type)> 
	struct factory<TPLT_TEMPLATE_ARGUMENTS_CALL( 7, Type), TPLT_ARGUMENTS_CALL(3, invalid)>
		: public cmn::type_trait<vector<forward_iterator<vector_7<TPLT_TEMPLATE_ARGUMENTS_CALL( 7, Type)>>>> {};

	template<TPLT_TEMPLATE_ARGUMENTS_DECL( 6, Type)> 
	struct factory<TPLT_TEMPLATE_ARGUMENTS_CALL( 6, Type), TPLT_ARGUMENTS_CALL(4, invalid)>
		: public cmn::type_trait<vector<forward_iterator<vector_6<TPLT_TEMPLATE_ARGUMENTS_CALL( 6, Type)>>>> {};

	template<TPLT_TEMPLATE_ARGUMENTS_DECL( 5, Type)> 
	struct factory<TPLT_TEMPLATE_ARGUMENTS_CALL( 5, Type), TPLT_ARGUMENTS_CALL(5, invalid)>
		: public cmn::type_trait<vector<forward_iterator<vector_5<TPLT_TEMPLATE_ARGUMENTS_CALL( 5, Type)>>>> {};

	template<TPLT_TEMPLATE_ARGUMENTS_DECL( 4, Type)> 
	struct factory<TPLT_TEMPLATE_ARGUMENTS_CALL( 4, Type), TPLT_ARGUMENTS_CALL(6, invalid)>
		: public cmn::type_trait<vector<forward_iterator<vector_4<TPLT_TEMPLATE_ARGUMENTS_CALL( 4, Type)>>>> {};

	template<TPLT_TEMPLATE_ARGUMENTS_DECL( 3, Type)> 
	struct factory<TPLT_TEMPLATE_ARGUMENTS_CALL( 3, Type), TPLT_ARGUMENTS_CALL(7, invalid)>
		: public cmn::type_trait<vector<forward_iterator<vector_3<TPLT_TEMPLATE_ARGUMENTS_CALL( 3, Type)>>>> {};

	template<TPLT_TEMPLATE_ARGUMENTS_DECL( 2, Type)> 
	struct factory<TPLT_TEMPLATE_ARGUMENTS_CALL( 2, Type), TPLT_ARGUMENTS_CALL(8, invalid)>
		: public cmn::type_trait<vector<forward_iterator<vector_2<TPLT_TEMPLATE_ARGUMENTS_CALL( 2, Type)>>>> {};

	template<TPLT_TEMPLATE_ARGUMENTS_DECL( 1, Type)> 
	struct factory<TPLT_TEMPLATE_ARGUMENTS_CALL( 1, Type), TPLT_ARGUMENTS_CALL(9, invalid)>
		: public cmn::type_trait<vector<forward_iterator<vector_1<TPLT_TEMPLATE_ARGUMENTS_CALL( 1, Type)>>>> {};

	template<> 
	struct factory<TPLT_ARGUMENTS_CALL(10, invalid)>
		: public cmn::type_trait<vector<>> {};


	template<typename Cursor, typename End, typename InitialValue, template<typename Value, typename Current> class Function>
	struct accumulate
		: public accumulate<typename Cursor::increment, End, typename Function<InitialValue, typename Cursor::type>::type, Function>
	{
	};

	template<typename Cursor, typename FinalValue, template<typename Value, typename Current> class Function>
	struct accumulate<Cursor, Cursor, FinalValue, Function>
		: public cmn::type_trait<FinalValue>
	{
	};

	template<typename Cursor, typename End, typename SearchValue, template<typename SearchValue, typename Iterator> class Function, typename Result=Cursor, bool Found = false>
	struct find_if
		: public find_if<typename Cursor::increment, End, SearchValue, Function, Cursor, Function<SearchValue, Cursor>::value>
	{
	};

	template<typename Cursor, typename End, typename SearchValue, template<typename Value, typename Current> class Function, typename Result>
	struct find_if<Cursor, End, SearchValue, Function, Result, true>
		: public cmn::type_trait<Result>
	{
	};

	template<typename End, typename SearchValue, template<typename Value, typename Current> class Function, typename Result>
	struct find_if<End, End, SearchValue, Function, Result, false>
		: public cmn::type_trait<End>
	{
	};

	namespace detail
	{
		template<typename Cursor, typename End, typename Result>
		struct distance
			: public detail::distance<typename Cursor::increment, End, std::integral_constant<size_t, 1 + Result::value>>
		{
		};

		template<typename Cursor, typename Result>
		struct distance<Cursor, Cursor, Result>
			: public Result
		{
		};
	}

	template<typename Cursor, typename End>
	struct distance
		: public detail::distance<typename Cursor, End, std::integral_constant<size_t, 0>>
	{
	};

	template<typename Cursor, typename End, size_t At, size_t Index = 0>
	struct at
		: public cmn::type_trait<typename std::conditional<At == Index, typename Cursor::type, typename at<typename Cursor::increment, End, At, Index + 1>::type>::type>
	{
	};

	template<typename Cursor, size_t At, size_t Index>
	struct at<Cursor, Cursor, At, Index>
		: public cmn::type_trait<invalid>
	{
	};

}

#endif // TYPE_VECTOR_SOURCE
