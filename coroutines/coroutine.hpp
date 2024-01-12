#pragma once

#include "coroutines/status.hpp"
#include <ctx/context.hpp>
#include <ctx/trampoline.hpp>
#include <ctx/stack/stack.hpp>
#include <functional>

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
	std::function<void()> routine_;
};
