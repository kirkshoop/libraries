
#define WINDOW_MESSAGE_CAPITAL_NAME           TPLT_CALL(TPLT_EXTRACT, TPLT_ARGUMENTS_APPEND_LIST(4, WINDOW_MESSAGE_DEFINITION, 0))
#define WINDOW_MESSAGE_CASED_NAME             TPLT_CALL(TPLT_EXTRACT, TPLT_ARGUMENTS_APPEND_LIST(4, WINDOW_MESSAGE_DEFINITION, 1))
#define WINDOW_MESSAGE_PARAMETER_COUNT        TPLT_CALL(TPLT_EXTRACT, TPLT_ARGUMENTS_APPEND_LIST(4, WINDOW_MESSAGE_DEFINITION, 2))
#define WINDOW_MESSAGE_PARAMETER_LIST         TPLT_CALL(TPLT_EXTRACT, TPLT_ARGUMENTS_APPEND_LIST(4, WINDOW_MESSAGE_DEFINITION, 3))

#ifdef WINDOW_MESSAGE_DEFINE_OPTIONAL

#	define WINDOW_MESSAGE_TAG TPLT_CALL(MAKE_IDENTIFIER_EXPLICIT, (WINDOW_MESSAGE_CASED_NAME, Tag))
#	define WINDOW_MESSAGE_CHOICE TPLT_CALL(MAKE_IDENTIFIER_EXPLICIT, (WINDOW_MESSAGE_CASED_NAME, Choice))
#	define WINDOW_MESSAGE_MACRO TPLT_CALL(MAKE_IDENTIFIER_EXPLICIT, (WM_, WINDOW_MESSAGE_CAPITAL_NAME))
#	define WINDOW_MESSAGE_TARGET_METHOD TPLT_CALL(MAKE_IDENTIFIER_EXPLICIT, (On, WINDOW_MESSAGE_CASED_NAME))
#	define WINDOW_MESSAGE_OPTIONAL TPLT_CALL(MAKE_IDENTIFIER_EXPLICIT, (optional, WINDOW_MESSAGE_CASED_NAME))
#	define WINDOW_MESSAGE_DISPATCH TPLT_CALL(MAKE_IDENTIFIER_EXPLICIT, (dispatch, WINDOW_MESSAGE_CASED_NAME))
#	define WINDOW_MESSAGE_HANDLER TPLT_CALL(MAKE_IDENTIFIER_EXPLICIT, (HANDLE_WM_, WINDOW_MESSAGE_CAPITAL_NAME))

#	define WINDOW_MESSAGE_PARAMETER_INSTANCES TPLT_CALL(TPLT_FUNCTION_ARGUMENT_INSTANCES, TPLT_ARGUMENTS_APPEND_LIST(WINDOW_MESSAGE_PARAMETER_COUNT, WINDOW_MESSAGE_PARAMETERS, WINDOW_MESSAGE_PARAMETER_COUNT))

	struct WINDOW_MESSAGE_TAG {};

    namespace detail
	{

		template<typename WindowClassTag, typename Target>
		struct WINDOW_MESSAGE_CHOICE
		{
			WINDOW_MESSAGE_CHOICE(Target targetArg, const Context<WindowClassTag>* contextArg, BOOL* handledArg, LRESULT* resultArg)
				: target(targetArg)
				, context(contextArg)
				, handled(handledArg)
				, result(resultArg)
			{ }

			TPLT_NON_ZERO(WINDOW_MESSAGE_PARAMETER_COUNT, template<TPLT_TEMPLATE_ARGUMENTS_DECL(WINDOW_MESSAGE_PARAMETER_COUNT, Param)>)
			LRESULT operator()(
				HWND 
				TPLT_NON_ZERO(WINDOW_MESSAGE_PARAMETER_COUNT, TPLT_COMMA TPLT_FUNCTION_ARGUMENTS_DECL(WINDOW_MESSAGE_PARAMETER_COUNT, Param, , &&)))
			{
				if (context->message == WINDOW_MESSAGE_MACRO)
				{
					window_message_error_contract(
						[&]
						{
							*handled = TRUE;
							*result = target->WINDOW_MESSAGE_TARGET_METHOD(
								*context 
								TPLT_NON_ZERO(WINDOW_MESSAGE_PARAMETER_COUNT, TPLT_COMMA TPLT_FUNCTION_ARGUMENTS_CAST(WINDOW_MESSAGE_PARAMETER_COUNT, Param, std::forward)));
						},
						*context,
						WINDOW_MESSAGE_TAG(),
						WindowClassTag()
					);
				}
				return *result;
			}

			Target target;
			const Context<WindowClassTag>* context;
			BOOL* handled;
			LRESULT* result;
		};

 		template<typename WindowClassTag, typename Target>
		WINDOW_MESSAGE_CHOICE<WindowClassTag, Target> WINDOW_MESSAGE_OPTIONAL(
			Target target, 
			const Context<WindowClassTag>* context, 
			BOOL* handled, 
			LRESULT* result, 
			decltype(
				cmn::instance_of<Target>::value->WINDOW_MESSAGE_TARGET_METHOD(
					cmn::instance_of<Context<WindowClassTag>>::value 
					TPLT_NON_ZERO(WINDOW_MESSAGE_PARAMETER_COUNT, TPLT_COMMA WINDOW_MESSAGE_PARAMETER_INSTANCES)
				)
			) 
		)
		{
			return WINDOW_MESSAGE_CHOICE<WindowClassTag, Target>(target, context, handled, result);
		}
#if 1
		inline nohandler WINDOW_MESSAGE_OPTIONAL(...)
		{
			return nohandler();
		}
#endif
		template<typename WindowClassTag, typename Target>
		void WINDOW_MESSAGE_DISPATCH(Target target, const Context<WindowClassTag>& context, BOOL* handled, LRESULT* result)
		{
			WINDOW_MESSAGE_HANDLER(context.window, context.wParam, context.lParam, detail::WINDOW_MESSAGE_OPTIONAL(target, &context, handled, result, 0));
		}
	}

	template<typename WindowClassTag, typename Target>
	std::pair<bool, LRESULT> WINDOW_MESSAGE_DISPATCH(Target target, const Context<WindowClassTag>& context)
	{
		BOOL handled = FALSE;
		LRESULT result = 0;
		detail::WINDOW_MESSAGE_DISPATCH(target, context, &handled, &result);
		return std::make_pair(!!handled, result);
	} 

#	undef WINDOW_MESSAGE_PARAMETER_INSTANCES

#	undef WINDOW_MESSAGE_HANDLER 
#	undef WINDOW_MESSAGE_DISPATCH 
#	undef WINDOW_MESSAGE_OPTIONAL 
#	undef WINDOW_MESSAGE_TARGET_METHOD 
#	undef WINDOW_MESSAGE_MACRO 
#	undef WINDOW_MESSAGE_CHOICE 
#	undef WINDOW_MESSAGE_TAG 

#elif defined(WINDOW_MESSAGE_DEFINE_DISPATCH)

#	define WINDOW_MESSAGE_DISPATCH TPLT_CALL(MAKE_IDENTIFIER_EXPLICIT, (dispatch, WINDOW_MESSAGE_CASED_NAME))

		msg::detail::WINDOW_MESSAGE_DISPATCH(target, context, &handled, &result); 

#	undef WINDOW_MESSAGE_DISPATCH 

#endif

#undef WINDOW_MESSAGE_PARAMETERS
#undef WINDOW_MESSAGE_PARAMETER_COUNT
#undef WINDOW_MESSAGE_CASED_NAME
#undef WINDOW_MESSAGE_CAPITAL_NAME
#undef WINDOW_MESSAGE_DEFINITION
