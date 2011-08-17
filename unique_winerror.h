
#ifndef UNIQUE_WINERROR_SOURCE
#define UNIQUE_WINERROR_SOURCE

namespace unique_winerror_def
{
	struct tag {};

	inline bool unique_error_ok(DWORD winerror, tag&&)
	{
		return winerror == ERROR_SUCCESS;
	}

	inline DWORD unique_error_default(tag&&)
	{
		return ERROR_SUCCESS;
	}
}

typedef
	UNIQUE_ERROR_NAMESPACE::unique_error<unique_winerror_def::tag>
unique_winerror;

inline unique_winerror make_winerror_if(BOOL is_last_error)
{
	unique_winerror result;
	if (!is_last_error)
	{
		return std::move(result.reset(GetLastError()));
	}
	return std::move(result);
}

inline unique_winerror::static_error winerror_cast(DWORD raw)
{
	return unique_winerror::cast(raw);
}

#endif // UNIQUE_WINERROR_SOURCE