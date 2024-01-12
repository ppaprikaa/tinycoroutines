include(FetchContent)

FetchContent_Declare(
	ctx
	GIT_REPOSITORY https://github.com/ppaprikaa/execution-context
	GIT_TAG master
	)

FetchContent_MakeAvailable(ctx)

FetchContent_Declare(
	function2
	GIT_REPOSITORY https://github.com/Naios/function2
	GIT_TAG master
	)

FetchContent_MakeAvailable(function2)
