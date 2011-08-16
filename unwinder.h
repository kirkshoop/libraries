
#ifndef UNWINDER_SOURCE
#define UNWINDER_SOURCE

#ifndef UNWINDER_NAMESPACE
#error UNWINDER_NAMESPACE must be defined
#endif

namespace UNWINDER_NAMESPACE
{
	using namespace COMMON_NAMESPACE;

	template<typename Function>
	class unwinder
	{
	public:
		~unwinder()
		{
			if (!!function)
			{
				__try
				{
					(*function)();
				}
				__except(FailFastFilter(GetExceptionInformation()))
				{
				}
			}
		}

		explicit unwinder(Function* functionArg)
			: function(functionArg)
		{
		}

		void dismiss()
		{
			function = nullptr;
		}

	private:
		unwinder();
		unwinder(const unwinder&);
		unwinder& operator=(const unwinder&);

		Function* function;
	};

}

#define MAKE_IDENTIFIER(Prefix) Prefix ## __LINE__

#define ON_UNWIND(Function) \
	auto MAKE_IDENTIFIER(uwfunc_) = (Function); \
	UNWINDER_NAMESPACE::unwinder<decltype(MAKE_IDENTIFIER(uwfunc_))> MAKE_IDENTIFIER(unwind_)(std::addressof(MAKE_IDENTIFIER(uwfunc_)))

#define ON_UNWIND_NAMED(Name, Function) \
	auto uwfunc_ ## Name = (Function); \
	UNWINDER_NAMESPACE::unwinder<decltype(uwfunc_ ## Name)> Name(std::addressof(uwfunc_ ## Name))

#endif // UNWINDER_SOURCE