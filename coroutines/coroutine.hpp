#pragma once

#include <coroutines/routine.hpp>
#include <coroutines/status.hpp>
#include <ctx/context.hpp>
#include <ctx/trampoline.hpp>
#include <ctx/stack/stack.hpp>

class Coroutine : public ITrampoline {
public:
	Coroutine() = delete;
	Coroutine(std::function<void()> routine);

	CoroutineStatus Status() {
		return status_;
	}

	void Suspend();
	void Call();
	void Resume();

private:
	void SetupCoroutineContext();
	void Run() noexcept override;
private:
	CoroutineStatus status_;
	Stack stack_;
	Context to_resume_;
	Context current_;
	Routine routine_;
};
