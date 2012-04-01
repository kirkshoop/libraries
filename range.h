#ifndef RANGE_SOURCE
#define RANGE_SOURCE

#ifndef RANGE_NAMESPACE
#error RANGE_NAMESPACE must be defined
#endif

namespace RANGE_NAMESPACE
{
	namespace cmn=COMMON_NAMESPACE;

	template< class Range >
	auto range_begin( Range&& r ) -> decltype( std::forward<Range>(r).begin() )
	{
		return std::forward<Range>(r).begin();
	}

	template< class Iterator >
	Iterator range_begin( const std::pair<Iterator,Iterator>& p )
	{
		return p.first;
	}

	template< class T, size_t N >
	T* range_begin( T (&arrayArg)[N] )
	{
		return arrayArg;
	}

	template< class Range >
	auto begin( Range&& r ) -> decltype( range_begin(std::forward<Range>(r)) )
	{
		return range_begin(std::forward<Range>(r));
	}

	template< class Range >
	auto range_end( Range&& r ) -> decltype( std::forward<Range>(r).end() )
	{
		return std::forward<Range>(r).end();
	}

	template< class Iterator >
	Iterator range_end( const std::pair<Iterator,Iterator>& p )
	{
		return p.second;
	}

	template< class T, size_t N >
	T* range_end( T (&arrayArg)[N] )
	{
		return arrayArg + N;
	}

	template< class Range >
	auto end( Range&& r ) -> decltype( range_end(std::forward<Range>(r)) )
	{
		return range_end(std::forward<Range>(r));
	}

	template< class RangeTo, class RangeFrom >
	auto range_copy( RangeFrom&& r, RangeTo* ) -> decltype( RangeTo(RANGE_NAMESPACE::begin(std::forward<RangeFrom>(r)), RANGE_NAMESPACE::end(std::forward<RangeFrom>(r))) )
	{
		return RangeTo(RANGE_NAMESPACE::begin(std::forward<RangeFrom>(r)), RANGE_NAMESPACE::end(std::forward<RangeFrom>(r)));
	}

	template< class RangeTo, class RangeFrom >
	auto copy( RangeFrom&& r ) -> decltype( range_copy(std::forward<RangeFrom>(r), reinterpret_cast<RangeTo*>(nullptr)) )
	{
		return range_copy(std::forward<RangeFrom>(r), reinterpret_cast<RangeTo*>(nullptr));
	}

	template< class Range >
	struct range_iterator : public cmn::type_trait< decltype(RANGE_NAMESPACE::begin(cmn::instance_of<Range>::value)) > {};

	template< class BidirectionalRange >
	struct range_reverse_iterator : public cmn::type_trait< std::reverse_iterator<typename range_iterator<BidirectionalRange>::type> > {};

	template< class Range >
	struct range_value : public cmn::type_trait< typename std::iterator_traits< typename range_iterator<Range>::type >::value_type > {};

	template< class Range >
	struct range_reference : public cmn::type_trait< typename std::iterator_traits< typename range_iterator<Range>::type >::reference > {};

	template< class Range >
	struct range_pointer : public cmn::type_trait< typename std::iterator_traits< typename range_iterator<Range>::type >::pointer > {};
 
	template< class Range >
	struct range_difference : public cmn::type_trait< typename std::iterator_traits< typename range_iterator<Range>::type >::difference_type > {};

	template< class Range >
	struct range_category : public cmn::type_trait< typename std::iterator_traits< typename range_iterator<Range>::type >::iterator_category > {};

	template< class Range >
	bool empty( const Range& r )
	{
		return RANGE_NAMESPACE::begin(r) == RANGE_NAMESPACE::end(r);
	}

	template< class RandomAccessRange >
	typename range_difference<RandomAccessRange>::type 
	size( const RandomAccessRange& r )
	{
		return std::distance(RANGE_NAMESPACE::begin(r),RANGE_NAMESPACE::end(r));
	}

	template< class BidirectionalRange >
	typename range_reverse_iterator<BidirectionalRange>::type 
	rbegin( BidirectionalRange&& r )
	{
		return typename range_reverse_iterator<BidirectionalRange>::type(RANGE_NAMESPACE::end(r));
	}

	template< class BidirectionalRange >
	typename range_reverse_iterator<BidirectionalRange>::type
	rend( BidirectionalRange&& r )
	{
		return typename range_reverse_iterator<BidirectionalRange>::type(RANGE_NAMESPACE::begin(r));
	}

	template< class Range >
	typename range_iterator<const Range>::type 
	const_begin( const Range& r )
	{
		return RANGE_NAMESPACE::begin(r);
	}

	template< class Range >
	typename range_iterator<const Range>::type 
	const_end( const Range& r )
	{
		return RANGE_NAMESPACE::end(r);
	}

	template< class BidirectionalRange >
	typename range_reverse_iterator<const BidirectionalRange>::type 
	const_rbegin( const BidirectionalRange& r )
	{
		return RANGE_NAMESPACE::rbegin(r);
	}

	template< class BidirectionalRange >
	typename range_reverse_iterator<const BidirectionalRange>::type 
	const_rend( const BidirectionalRange& r )
	{
		return RANGE_NAMESPACE::rend(r);
	}

    template< class Iterator >
    class range
    {
    public: // types
        typedef range                                                this_type;
        typedef typename std::iterator_traits<Iterator>::value_type       value_type;
        typedef typename std::iterator_traits<Iterator>::reference        reference;
        typedef typename std::iterator_traits<Iterator>::difference_type  difference_type;
        typedef Iterator                                             iterator;
        typedef Iterator                                             const_iterator;
        
    public: // construction, assignment
		range() : beginIterator(), endIterator() {}
                
        template< class Iterator2 >
        range( const Iterator2& begin, const Iterator2& end )
			: beginIterator(begin)
			, endIterator(end)
		{
		}
                        
        template< class Range >
        range( Range&& r )
			: beginIterator(RANGE_NAMESPACE::begin(r))
			, endIterator(RANGE_NAMESPACE::end(r))
		{
		}
        
        template< class Range >
        range& operator=( Range&& r )
		{
			beginIterator = RANGE_NAMESPACE::begin(r);
			endIterator = RANGE_NAMESPACE::end(r);
			return *this;
		}
        
    public: // forward range functions
        iterator        begin() const
		{
			return beginIterator;
		}

		iterator        end() const
		{
			return endIterator;
		}

		difference_type size() const
		{
			return std::distance(begin(),end());
		}

		bool            empty() const
		{
			return begin() == end();
		}

	public: // convenience

		operator    typename cmn::unspecified_bool<this_type>::type() const
		{
			return cmn::unspecified_bool<this_type>::get(!empty());
		}

		bool        equal( const range& r ) const
		{
			return begin() == r.begin() && end() == r.end();
		}

		reference   front() const
		{
			return *begin();
		}

		reference   back() const
		{
			auto result = endIterator;
			return *--result;
		}

		reference   operator[]( difference_type at ) const
		{
			return *(begin() + at);
		}

		range&      advance_begin( difference_type n )
		{
			std::advance(beginIterator,n);
			return *this;
		}

		range&      advance_end( difference_type n )
		{
			std::advance(endIterator,n);
			return *this;
		}
        
    private:
        Iterator beginIterator;
		Iterator endIterator;
    }; 

    template< class Range >
    class sub_range : public range< typename range_iterator<Range>::type >
    {
    public: 
        typedef range< typename range_iterator<Range>::type >        base_type;
        typedef typename range_iterator<Range>::type                 iterator;
        typedef typename range_iterator<const Range>::type           const_iterator;
        typedef typename std::iterator_traits<const_iterator>::reference  const_reference;
        using base_type::value_type;
        using base_type::reference;
        using base_type::difference_type;
                
    public: // construction, assignment
        sub_range()
			: range()
		{
		}
                
        template< class Iterator >
        sub_range( const Iterator& begin, const Iterator& end )
			: range(begin, end)
		{
		}
                
        template< class Range2 >
        sub_range( Range2&& r )
			: range(r)
		{
		}
                 
        template< class Range2 >
        sub_range& operator=( Range2&& r )
		{
			base_type::operator=(r);
			return *this;
		}
                
    public:  // forward range functions 
        iterator        begin()
		{
			return base_type::begin();
		}

		const_iterator  begin() const
		{
			return base_type::begin();
		}

		iterator        end()
		{
			return base_type::end();
		}

		const_iterator  end() const
		{
			return base_type::end();
		}
                
    public: // convenience 
        reference        front()
		{
			return base_type::front();
		}

		const_reference  front() const
		{
			return base_type::front();
		}

        reference        back()
		{
			return base_type::back();
		}

        const_reference  back() const
		{
			return base_type::back();
		}

		reference        operator[]( difference_type at )
		{
			return base_type::operator[](at);
		}

        const_reference  operator[]( difference_type at ) const
		{
			return base_type::operator[](at);
		}

        sub_range&       advance_begin( difference_type n )
		{
			return base_type::advance_begin(n);
		}

        sub_range&       advance_end( difference_type n )
		{
			return base_type::advance_end(n);
		}

    };

	// external construction
	template< class Iterator >
	range<Iterator>
	make_range( const Iterator& begin, const Iterator& end )
	{
		return range<Iterator>(begin,end);
	}
   
	template< class Range >
	range<typename range_iterator<Range>::type> 
	make_range( Range&& r )
	{
		return range<typename range_iterator<Range>::type>(r);
	}

	template< class Range >
	range<typename range_iterator<Range>::type> 
	make_range( Range&& r, typename range_difference<Range>::type advance_begin,
						   typename range_difference<Range>::type advance_end )
	{
		range<typename range_iterator<Range>::type> tmp(r); 
		tmp.advance_begin(advance_begin); 
		tmp.advance_end(advance_end); 
		return tmp;
	}

	//
	// raw ranges to interoperate with c functions
	//

	template< class Range >
	auto
	make_range_raw( Range&& r ) -> decltype(RANGE_NAMESPACE::make_range(&std::forward<Range>(r)[0], &std::forward<Range>(r)[0] + RANGE_NAMESPACE::size(std::forward<Range>(r))))
	{
		if (RANGE_NAMESPACE::size(r) == 0)
		{
			decltype(RANGE_NAMESPACE::make_range(&std::forward<Range>(r)[0], &std::forward<Range>(r)[0] + RANGE_NAMESPACE::size(std::forward<Range>(r)))) result;
			return result;
		}
		return RANGE_NAMESPACE::make_range(&std::forward<Range>(r)[0], &std::forward<Range>(r)[0] + RANGE_NAMESPACE::size(std::forward<Range>(r)));
	}

	template< class Range >
	auto
	make_range_raw( Range&& r,	typename range_difference<Range>::type advance_begin,
								typename range_difference<Range>::type advance_end ) 
		-> decltype(RANGE_NAMESPACE::make_range(&std::forward<Range>(r)[0], &std::forward<Range>(r)[0] + RANGE_NAMESPACE::size(std::forward<Range>(r))))
	{
		decltype(RANGE_NAMESPACE::make_range(&std::forward<Range>(r)[0], &std::forward<Range>(r)[0] + RANGE_NAMESPACE::size(std::forward<Range>(r)))) result;
		if (RANGE_NAMESPACE::size(std::forward<Range>(r)) != 0)
		{
			result = RANGE_NAMESPACE::make_range(&std::forward<Range>(r)[0], &std::forward<Range>(r)[0] + RANGE_NAMESPACE::size(std::forward<Range>(r)));
		}
		result.advance_begin(advance_begin); 
		result.advance_end(advance_end); 
		return result;
	}

	template< class NewIterator, class OldIterator >      
	auto range_const_cast( const range<OldIterator*>& r ) -> decltype(range<NewIterator>(const_cast<NewIterator>(RANGE_NAMESPACE::begin(r)),const_cast<NewIterator>(RANGE_NAMESPACE::end(r))))
	{
		return range<NewIterator>(const_cast<NewIterator>(RANGE_NAMESPACE::begin(r)),const_cast<NewIterator>(RANGE_NAMESPACE::end(r)));
	}

	template< class NewIterator, class OldIterator >      
	auto range_static_cast( const range<OldIterator*>& r ) -> decltype(range<NewIterator>(static_cast<NewIterator>(RANGE_NAMESPACE::begin(r)),static_cast<NewIterator>(RANGE_NAMESPACE::end(r))))
	{
		return range<NewIterator>(static_cast<NewIterator>(RANGE_NAMESPACE::begin(r)),static_cast<NewIterator>(RANGE_NAMESPACE::end(r)));
	}

	template< class NewIterator, class OldIterator >      
	auto range_reinterpret_cast( const range<OldIterator*>& r ) -> decltype(range<NewIterator>(reinterpret_cast<NewIterator>(RANGE_NAMESPACE::begin(r)),reinterpret_cast<NewIterator>(RANGE_NAMESPACE::end(r))))
	{
		return range<NewIterator>(reinterpret_cast<NewIterator>(RANGE_NAMESPACE::begin(r)),reinterpret_cast<NewIterator>(RANGE_NAMESPACE::end(r)));
	}


	template< class ResultType, class InputType >
	ResultType
	size_cast( InputType size )
	{
		const static size_t bitsOfPositiveRepresentationInResultType = 
			(sizeof(ResultType) * 8) - static_cast<ResultType>(std::is_signed<ResultType>::value);
		const static size_t bitsOfPositiveRepresentationInInputType = 
			(sizeof(InputType) * 8) - static_cast<InputType>(std::is_signed<InputType>::value);
		typedef
			std::conditional<
				bitsOfPositiveRepresentationInResultType <
					bitsOfPositiveRepresentationInInputType,
				InputType,
				ResultType
			>::type
		check_type;
		check_type size_check = static_cast<check_type>(size);
		FAIL_FAST_IF(
			(false, (std::is_signed<InputType>::value && size < 0)) ||
				(size_check >> (bitsOfPositiveRepresentationInResultType - 1)) != 0, 
			ERROR_INVALID_PARAMETER
		);
		return static_cast<ResultType>(size);
	}

	//
	// comparisons
	//

	template< class Iterator, class Iterator2 >
	bool operator==( range<Iterator> l, range<Iterator2> r )
	{
		for(;!l.empty() && !r.empty(); l.advance_begin(1), r.advance_begin(1))
		{
			if (l.front() != r.front())
			{
				return false;
			}
		}
		return l.empty() && r.empty();
	}

	template< class Iterator, class Range >
	bool operator==( const range<Iterator>& l, const Range& r )
	{
		auto rrange = make_range(r);
		for(;!l.empty() && !rrange.empty(); l.advance_begin(1), rrange.advance_begin(1))
		{
			if (l.front() != rrange.front())
			{
				return false;
			}
		}
		return l.empty() && rrange.empty();
	}

	template< class Iterator, class Range >
	bool operator==( const Range& l, const range<Iterator>& r )
	{
		auto lrange = make_range(l);
		for(;!lrange.empty() && !r.empty(); lrange.advance_begin(1), r.advance_begin(1))
		{
			if (lrange.front() != r.front())
			{
				return false;
			}
		}
		return lrange.empty() && r.empty();
	}

	template< class Iterator, class Iterator2 >
	bool operator!=( const range<Iterator>& l, const range<Iterator2>& r )
	{
		return !(l == r);
	}

	template< class Iterator, class Range >
	bool operator!=( const range<Iterator>& l, const Range& r )
	{
		return !(l == r);
	}

	template< class Iterator, class Range >
	bool operator!=( const Range& l, const range<Iterator>& r )
	{
		return !(l == r);
	}

	template< class Iterator, class Iterator2 >
	bool operator<( const range<Iterator>& l, const range<Iterator2>& r )
	{
		return std::lexicographical_compare(RANGE_NAMESPACE::begin(l),RANGE_NAMESPACE::end(l),RANGE_NAMESPACE::begin(r), RANGE_NAMESPACE::end(r));
	}

	template< class Iterator, class Range >
	bool operator<( const range<Iterator>& l, const Range& r )
	{
		return std::lexicographical_compare(RANGE_NAMESPACE::begin(l),RANGE_NAMESPACE::end(l),RANGE_NAMESPACE::begin(r), RANGE_NAMESPACE::end(r));
	}

	template< class Iterator, class Range >
	bool operator<( const Range& l, const range<Iterator>& r )
	{
		return std::lexicographical_compare(RANGE_NAMESPACE::begin(l),RANGE_NAMESPACE::end(l),RANGE_NAMESPACE::begin(r), RANGE_NAMESPACE::end(r));
	}

	template< class Range, class Range2 >
	bool operator==( const sub_range<Range>& l, const sub_range<Range2>& r )
	{
		return static_cast<sub_range<Range>::base_type>(l) == static_cast<sub_range<Range2>::base_type>(r);
	}

	template< class Range, class Range2 >
	bool operator!=( const sub_range<Range>& l, const sub_range<Range2>& r )
	{
		return !(l==r);
	}

	template< class Range, class Range2 >
	bool operator<( const sub_range<Range>& l, const sub_range<Range2>& r )
	{
		return static_cast<sub_range<Range>::base_type>(l) < static_cast<sub_range<Range2>::base_type>(r);
	}

           
	template< class ForwardRange >
	typename range_difference<ForwardRange>::type
	distance( const ForwardRange& r )
	{
		return std::distance(RANGE_NAMESPACE::begin(r),RANGE_NAMESPACE::end(r));
	}

	template< class Range >
	range<typename range_iterator<Range>::type> 
	as_literal( Range&& r )
	{
		auto result = range<typename range_iterator<Range>::type>(r);
		while (!result.empty() && result.back() == 0)
		{
			result.advance_end(-1);
		}
		return result;
	}

}

#endif // RANGE_SOURCE
