#ifndef __cxx_hpp__
#define __cxx_hpp__

namespace cxx 
{
	template <typename type_t,
		  typename type2_t>
	type_t &&assign(type_t&& t, 
			type2_t&& t2) 
	{
		return (t=t2);
	}

	template <typename type_t> 
	type_t &&increment(type_t&& t)
	{
		return (t++);
	}

	template <typename type_t, typename type2_t>
	auto add(type_t&& t, type2_t&& t2)
	-> decltype((t+t2))
	{
		return (t+t2);
	}


	auto less_equal(auto&& t, auto&& t2)
	-> decltype((t<=t2))
	{
		return (t<=t2);
	}

	auto and_(auto&&t, auto&&t2)
	-> decltype((t and t2))
	{
		return t and t2;
	}

	auto or_(auto&&t, auto&&t2)
	-> decltype((t or t2))
	{
		return t or t2;
	}

	auto equals(auto&& t, auto&& t2)
	-> decltype((t==t2))
	{
		return (t==t2);
	}

	auto not_equals(auto&& t, auto&& t2)
	-> decltype((t!=t2))
	{
		return (t!=t2);
	}
}
#endif
