
#ifndef UNIQUE_HRESULT_SOURCE
#define UNIQUE_HRESULT_SOURCE

namespace unique_hresult_def
{
	struct tag {};

	inline bool unique_error_ok(HRESULT hr, tag&&)
	{
		return SUCCEEDED(hr);
	}

	inline HRESULT unique_error_default(tag&&)
	{
		return S_OK;
	}
}

// 
//
// implementations of these must be included in the final module
//
void unique_error_report_initiated(HRESULT value, unique_hresult_def::tag&&);
void unique_error_report_reset(HRESULT value, unique_hresult_def::tag&&);

typedef
	UNIQUE_ERROR_NAMESPACE::unique_error<unique_hresult_def::tag>
unique_hresult;

inline unique_hresult::static_error hresult_cast(HRESULT raw)
{
	return unique_hresult::cast(raw);
}

#endif // UNIQUE_HRESULT_SOURCE

#ifdef UNIQUE_HRESULT_DEFINE_REPORTS
void unique_error_report_initiated(HRESULT value, unique_hresult_def::tag&&)
{
	static HRESULT anchor;
	anchor = value;
}

void unique_error_report_reset(HRESULT value, unique_hresult_def::tag&&)
{
	static HRESULT anchor;
	anchor = value;
}
#endif
