
#ifndef UNWINDER_SOURCE
#define UNWINDER_SOURCE

#ifndef UNWINDER_NAMESPACE
#error UNWINDER_NAMESPACE must be defined
#endif

namespace UNWINDER_NAMESPACE
{
	namespace cmn=COMMON_NAMESPACE;

	template<typename Function>
	class unwinder
	{
	public:
		~unwinder()
		{
			if (!!function)
			{
				FAIL_FAST_ON_THROW([&]{(*function)();});
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

#define ON_UNWIND(Name, Function) \
	ON_UNWIND_EXPLICIT(uwfunc_ ## Name, Name, Function)

#define ON_UNWIND_AUTO(Function) \
	ON_UNWIND_EXPLICIT(MAKE_IDENTIFIER(uwfunc_), MAKE_IDENTIFIER(unwind_), Function)

#define ON_UNWIND_EXPLICIT(FunctionName, UnwinderName, Function) \
	auto FunctionName = (Function); \
	UNWINDER_NAMESPACE::unwinder<decltype(FunctionName)> UnwinderName(std::addressof(FunctionName))

#endif // UNWINDER_SOURCE