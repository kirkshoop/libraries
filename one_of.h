#ifndef ONE_OF_SOURCE
#define ONE_OF_SOURCE

#ifndef ONE_OF_NAMESPACE
#error ONE_OF_NAMESPACE must be defined
#endif

namespace ONE_OF_NAMESPACE
{
	namespace cmn=COMMON_NAMESPACE;
	namespace tv=TYPE_VECTOR_NAMESPACE;

	namespace detail
	{
		template<typename Cursor, typename Begin, typename End, size_t Index = 0>
		struct traits
			: public traits<typename Cursor::increment, Begin, End, Index + 1>
		{
			typedef
				typename Cursor::type
			type;

			typedef
				traits<typename Cursor::increment, Begin, End, Index + 1>
			base;

			typedef
				traits<Begin, Begin, End>
			derived;

			static const size_t index = Index;
			union types
			{
				type* pointer;
				typename base::types next;
			};

			template<size_t At>
			static typename tv::at<Begin, End, At>::type* get_at(types& current, typename std::enable_if<At == index, void**>::type x = 0)
			{
				UNREFERENCED_PARAMETER(x);
				return current.pointer;
			}

			template<size_t At>
			static typename tv::at<Begin, End, At>::type* get_at(types& current, ...)
			{
				return base::get_at<At>(current.next);
			}

			template<size_t At>
			static const typename tv::at<Begin, End, At>::type* get_at(const types& current, typename std::enable_if<At == index, void**>::type x = 0)
			{
				UNREFERENCED_PARAMETER(x);
				return current.pointer;
			}

			template<size_t At>
			static const typename tv::at<Begin, End, At>::type* get_at(const types& current, ...)
			{
				return base::get_at<At>(current.next);
			}

			template<size_t At>
			static void set_at(types& current, void* raw)
			{
				if (0, At == index)
				{
					current.pointer = reinterpret_cast<type*>(raw);
				}
				base::set_at<At>(current.next, raw);
			}

			template<typename State, typename Functor>
			static void each(void* storage, size_t* selector, types& current, State&& state, Functor&& functor)
			{
				if (std::forward<Functor>(functor)(storage, size, selector, index, std::forward<State>(state), &current.pointer))
				{
					return ;
				}
				return base::each(storage, selector, current.next, std::forward<State>(state), std::forward<Functor>(functor));
			}

			template<typename State, typename Functor>
			static void each(const void* storage, const size_t* selector, const types& current, State&& state, Functor&& functor)
			{
				if (std::forward<Functor>(functor)(storage, size, selector, index, std::forward<State>(state), &current.pointer))
				{
					return ;
				}
				return base::each(storage, selector, current.next, std::forward<State>(state), std::forward<Functor>(functor));
			}
		};

		template<typename Cursor, typename Begin, size_t Index>
		struct traits<Cursor, Begin, Cursor, Index>
		{
			typedef
				traits<Begin, Begin, Cursor>
			derived;

			struct terminator {};

			template <typename Previous, typename Current>
			struct largest
				: public cmn::type_trait<typename std::conditional<sizeof(Previous) < sizeof(Current), Current, Previous>::type>
			{
			};
			template <typename Previous, typename Current>
			struct maxAligned
				: public cmn::type_trait<typename std::conditional<((Previous::value) < (std::alignment_of<Current>::value)), std::alignment_of<Current>, Previous>::type>
			{
			};
			static const size_t size = Index;
			static const size_t maxSize = sizeof(typename tv::accumulate<Begin, Cursor, BYTE, largest>::type);
			static const size_t maxAlign = tv::accumulate<Begin, Cursor, std::alignment_of<BYTE>, maxAligned>::type::value;
			typedef
				typename std::aligned_storage<maxSize, maxAlign>::type 
			storage;

			union types
			{
				terminator* pointer;
			};

			template<size_t At>
			static typename tv::at<Begin, Cursor, At>::type* get_at(types& )
			{
				return nullptr;
			}

			template<size_t At>
			static const typename tv::at<Begin, Cursor, At>::type* get_at(const types& )
			{
				return nullptr;
			}

			template<size_t At>
			static void set_at(types& , void* )
			{
			}

			template<typename State, typename Functor>
			static void each(void* storage, size_t* selector, types& current, State&& state, Functor&& functor)
			{
				std::forward<Functor>(functor)(storage, size, selector, size, std::forward<State>(state));
			}

			template<typename State, typename Functor>
			static void each(const void* storage, const size_t* selector, const types& current, State&& state, Functor&& functor)
			{
				std::forward<Functor>(functor)(storage, size, selector, size, std::forward<State>(state));
			}
		};

		template <typename SearchValue, typename Cursor>
		struct sameType
			: public std::is_same<SearchValue, typename Cursor::type>
		{
		};

		template <typename SearchValue, typename Cursor>
		struct convertableType
			: public std::is_convertible<SearchValue, typename Cursor::type>
		{
		};

		struct Reset
		{
			Reset() {}

			struct State {};

			template<typename T>
			bool operator()(void* , size_t size, size_t* selector, size_t current, State&&, T** storage)
			{
				if (*selector == current)
				{
					(*storage)->~T();
					*storage = nullptr;
					*selector = size;
					return true;
				}
				return false;
			}

			bool operator()(void* , size_t , size_t* , size_t , State&&)
			{
				// terminator
				return false;
			}
		};

		struct ResetValue
		{
			ResetValue() {}

			template<typename Value, typename T>
			auto operator()(void* raw, size_t , size_t* selector, size_t current, Value&& value, T** storage)
				-> decltype((new (raw) T(std::forward<Value>(value))), true)
			{
				new (raw) T(std::forward<Value>(value));
				*storage = reinterpret_cast<T*>(raw);
				*selector = current;
				return true;
			}

			bool operator()(void* , size_t , size_t* , size_t , ... )
			{
				// no conversion
				return false;
			}

			template<typename Value>
			bool operator()(void* , size_t , size_t* , size_t , Value&& )
			{
				// terminator
				return false;
			}

		private:
			ResetValue(const ResetValue&);
			ResetValue& operator=(const ResetValue&);
		};

		struct Call
		{
			Call() {}

			template<typename Functor, typename T>
			bool operator()(const void* , size_t , const size_t* selector, size_t current, Functor&& functor, T* const* storage)
			{
				if (*selector == current)
				{
					auto t = *storage;
					std::forward<Functor>(functor)(*t);
					return true;
				}
				return false;
			}

			template<typename Functor>
			bool operator()(const void* , size_t , const size_t* , size_t , Functor&& functor )
			{
				// terminator
				std::forward<Functor>(functor)();
				return false;
			}

		private:
			Call(const Call&);
			Call& operator=(const Call&);
		};

		struct Copy
		{
			Copy() {}

			template<typename That, typename T>
			bool operator()(const void* , size_t , const size_t* selector, size_t current, That&& that, T* const* storage)
			{
				if (*selector == current)
				{
					auto t = *storage;
					std::forward<That>(that)->reset(*t);
					return true;
				}
				return false;
			}

			template<typename That>
			bool operator()(const void* , size_t , const size_t* , size_t , That&& )
			{
				// terminator
				return false;
			}

		private:
			Copy(const Copy&);
			Copy& operator=(const Copy&);
		};

		struct Move
		{
			Move() {}

			template<typename That, typename T>
			bool operator()(void* , size_t size, size_t* selector, size_t current, That&& that, T** storage)
			{
				if (*selector == current)
				{
					auto t = *storage;
					std::forward<That>(that)->reset(std::move(*t));
					(*storage)->~T();
					*storage = nullptr;
					*selector = size;
					return true;
				}
				return false;
			}

			template<typename That>
			bool operator()(void* , size_t , size_t* , size_t , That&& )
			{
				// terminator
				return false;
			}

		private:
			Move(const Move&);
			Move& operator=(const Move&);
		};
	}

	template<typename Vector>
	class one_of
	{
	private:
		typedef
			typename detail::traits<typename Vector::begin, typename Vector::begin, typename Vector::end>
		traits;

		typedef
			one_of
		this_type;

		struct reset_at_selector {};
		template<size_t At, typename T>
		void selected_reset(T&& value, reset_at_selector&&)
		{
			reset_at<At>(std::forward<T>(value));
		}

		struct reset_value_selector {};
		template<size_t At, typename T>
		void selected_reset(T&& value, reset_value_selector&&)
		{
			detail::ResetValue resetFunc;
			traits::each(&storage, &selector, types, std::forward<T>(value), resetFunc);
		}

	public:
		~one_of()
		{
			reset();
		}

		one_of()
			: selector(traits::size)
		{
		}

		template<typename T>
		explicit one_of(T&& value, typename std::enable_if<!std::is_same<typename std::decay<T>::type, this_type>::value, void**>::type x = nullptr)
			: selector(traits::size)
		{
			reset(std::forward<T>(value));
		}

		one_of(const one_of& other)
			: selector(traits::size)
		{
			detail::Copy copyFunc;
			traits::each(&other.storage, &other.selector, other.types, this, copyFunc);
		}

		one_of(one_of&& other)
			: selector(traits::size)
		{
			detail::Move moveFunc;
			traits::each(&other.storage, &other.selector, other.types, this, moveFunc);
		}

		one_of& operator=(one_of other)
		{
			reset();
			detail::Move moveFunc;
			other::traits::each(&other.storage, &other.selector, other.types, this, moveFunc);
			return *this;
		}

		operator typename cmn::unspecified_bool<this_type>::type() const
		{
			return cmn::unspecified_bool<this_type>::get(!empty());
		}

		bool empty()
		{
			return selector == traits::size;
		}

		void reset()
		{
			if (!empty())
			{
				detail::Reset resetFunc;
				traits::each(&storage, &selector, types, detail::Reset::State(), resetFunc);
			}
		}

		template<typename T>
		void reset(T&& value)
		{
			reset();

			typedef
				typename tv::find_if<typename Vector::begin, typename Vector::end, std::decay<T>::type, detail::sameType>::type
			convertable_iterator;

			static_assert(!std::is_same<convertable_iterator, typename Vector::end>::value, "type cannot be stored");

			typedef
				typename tv::find_if<typename Vector::begin, typename Vector::end, std::decay<T>::type, detail::sameType>::type
			type_iterator;

			typedef
				tv::distance<typename Vector::begin, type_iterator>
			type_at;

			selected_reset<type_at::value>(
				std::forward<T>(value), 
				typename std::conditional<
					type_at::value == traits::size, 
					reset_value_selector, 
					reset_at_selector>::type());
		}

		template<size_t At, typename T>
		void reset_at(T&& value)
		{
			reset();
			typedef
				typename tv::at<typename Vector::begin, typename Vector::end, At>::type
			Value;
			new (&storage) Value(std::forward<T>(value));
			traits::set_at<At>(types, &storage);
			selector = At;
		}

		template<typename T>
		this_type& convert(const one_of<T>& other)
		{
			if (&other.storage == &storage)
			{
				return *this;
			}
			reset();
			detail::Copy copyFunc;
			one_of<T>::traits::each(&other.storage, &other.selector, other.types, this, copyFunc);
			return *this;
		}

		template<typename T>
		this_type& convert(one_of<T>&& other)
		{
			if (&other.storage == &storage)
			{
				return *this;
			}
			reset();
			detail::Move moveFunc;
			one_of<T>::traits::each(&other.storage, &other.selector, other.types, this, moveFunc);
			return *this;
		}

		template<size_t At>
		const typename tv::at<typename Vector::begin, typename Vector::end, At>::type*
		get() const
		{
			return traits::get_at<At>(types);
		}

		template<size_t At>
		const typename tv::at<typename Vector::begin, typename Vector::end, At>::type*
		get()
		{
			return traits::get_at<At>(types);
		}

		template<typename Functor>
		void call(Functor&& functor)
		{
			detail::Call callFunc;
			traits::each(&storage, &selector, types, std::forward<Functor>(functor), callFunc);
		}

		template<typename Functor>
		void call(Functor&& functor) const
		{
			detail::Call callFunc;
			traits::each(&storage, &selector, types, std::forward<Functor>(functor), callFunc);
		}

		template<size_t At, typename FunctorIf, typename FunctorElse>
		auto call_at_else(FunctorIf&& functorIf, FunctorElse&& functorElse)
			-> decltype(std::forward<FunctorIf>(functorIf)(*traits::get_at<At>(cmn::instance_of<traits::types>::value)))
		{
			if (selector == At)
			{
				return std::forward<FunctorIf>(functorIf)(*traits::get_at<At>(types));
			}
			return std::forward<FunctorElse>(functorElse)();
		}

		template<size_t At, typename FunctorIf, typename FunctorElse>
		auto call_at_else(FunctorIf&& functorIf, FunctorElse&& functorElse) const
			-> decltype(std::forward<FunctorIf>(functorIf)(*traits::get_at<At>(cmn::instance_of<traits::types>::value)))
		{
			if (selector == At)
			{
				return std::forward<FunctorIf>(functorIf)(*traits::get_at<At>(types));
			}
			return std::forward<FunctorElse>(functorElse)();
		}

#define ONE_OF_SWITCH_CASE(Selector, Prefix) \
	case Selector - 1: \
		return std::forward<Prefix ## _T ## Selector>(Prefix ## _t ## Selector)(*traits::get_at<Selector - 1>(types));

#define ONE_OF_SWITCH_CASES(Count, Value, Prefix) \
	static_assert(traits::size == Count, "need a function for each type, plus a default. functions needed=1 + 1 + " # Count); \
	switch (Value) \
	{ \
		ONE_OF_SWITCH_CASES_ ## Count (Prefix) \
	}
#define ONE_OF_SWITCH_CASES_1(Prefix)                               ONE_OF_SWITCH_CASE(1, Prefix)
#define ONE_OF_SWITCH_CASES_2(Prefix) ONE_OF_SWITCH_CASES_1(Prefix) ONE_OF_SWITCH_CASE(2, Prefix)
#define ONE_OF_SWITCH_CASES_3(Prefix) ONE_OF_SWITCH_CASES_2(Prefix) ONE_OF_SWITCH_CASE(3, Prefix)
#define ONE_OF_SWITCH_CASES_4(Prefix) ONE_OF_SWITCH_CASES_3(Prefix) ONE_OF_SWITCH_CASE(4, Prefix)
#define ONE_OF_SWITCH_CASES_5(Prefix) ONE_OF_SWITCH_CASES_4(Prefix) ONE_OF_SWITCH_CASE(5, Prefix)
#define ONE_OF_SWITCH_CASES_6(Prefix) ONE_OF_SWITCH_CASES_5(Prefix) ONE_OF_SWITCH_CASE(6, Prefix)
#define ONE_OF_SWITCH_CASES_7(Prefix) ONE_OF_SWITCH_CASES_6(Prefix) ONE_OF_SWITCH_CASE(7, Prefix)
#define ONE_OF_SWITCH_CASES_8(Prefix) ONE_OF_SWITCH_CASES_7(Prefix) ONE_OF_SWITCH_CASE(8, Prefix)
#define ONE_OF_SWITCH_CASES_9(Prefix) ONE_OF_SWITCH_CASES_8(Prefix) ONE_OF_SWITCH_CASE(9, Prefix)
#define ONE_OF_SWITCH_CASES_10(Prefix) ONE_OF_SWITCH_CASES_9(Prefix) ONE_OF_SWITCH_CASE(10, Prefix)


		template<TPLT_TEMPLATE_ARGUMENTS_DECL(1, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(1, FunctorCase, , &&), FunctorDefault&& functorDefault)
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(1, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(1, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(1, FunctorCase, , &&), FunctorDefault&& functorDefault) const
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(1, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(2, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(2, FunctorCase, , &&), FunctorDefault&& functorDefault)
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(2, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(2, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(2, FunctorCase, , &&), FunctorDefault&& functorDefault) const
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(2, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(3, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(3, FunctorCase, , &&), FunctorDefault&& functorDefault)
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(3, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(3, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(3, FunctorCase, , &&), FunctorDefault&& functorDefault) const
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(3, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}


		template<TPLT_TEMPLATE_ARGUMENTS_DECL(4, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(4, FunctorCase, , &&), FunctorDefault&& functorDefault)
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(4, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(4, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(4, FunctorCase, , &&), FunctorDefault&& functorDefault) const
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(4, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(5, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(5, FunctorCase, , &&), FunctorDefault&& functorDefault)
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(5, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(5, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(5, FunctorCase, , &&), FunctorDefault&& functorDefault) const
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(5, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(6, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(6, FunctorCase, , &&), FunctorDefault&& functorDefault)
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(6, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(6, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(6, FunctorCase, , &&), FunctorDefault&& functorDefault) const
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(6, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(7, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(7, FunctorCase, , &&), FunctorDefault&& functorDefault) 
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(7, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(7, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(7, FunctorCase, , &&), FunctorDefault&& functorDefault) const
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(7, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(8, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(8, FunctorCase, , &&), FunctorDefault&& functorDefault)
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(8, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(8, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(8, FunctorCase, , &&), FunctorDefault&& functorDefault) const
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(8, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(9, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(9, FunctorCase, , &&), FunctorDefault&& functorDefault)
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(9, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(9, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(9, FunctorCase, , &&), FunctorDefault&& functorDefault) const
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(9, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(10, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(10, FunctorCase, , &&), FunctorDefault&& functorDefault)
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(10, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}

		template<TPLT_TEMPLATE_ARGUMENTS_DECL(10, FunctorCase), typename FunctorDefault>
		auto call_switch(TPLT_FUNCTION_ARGUMENTS_DECL(10, FunctorCase, , &&), FunctorDefault&& functorDefault) const
			-> decltype(std::forward<FunctorCase_T1>(FunctorCase_t1)(*traits::get_at<0>(cmn::instance_of<traits::types>::value)))
		{
			ONE_OF_SWITCH_CASES(10, selector, FunctorCase);
			return std::forward<FunctorDefault>(functorDefault)();
		}

	private:
		template<typename T> friend class one_of;
		
	private:
		size_t selector;
		typename traits::types types;
		typename traits::storage storage;
	};
}

#endif
