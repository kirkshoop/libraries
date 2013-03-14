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