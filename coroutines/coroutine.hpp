#pragma once

#include <ctx/context.hpp>
#include <ctx/trampoline.hpp>
#include <ctx/stack/stack.hpp>
#include <functional>

class Coroutine : public ITrampoline {
public:
	Coroutine() = delete;
	Coroutine(std::function<void()> routine);

	void Suspend();
	
	void Call();
	void Resume();
private:
	void SetupCoroutineContext();
	void Run() noexcept override;
private:
	Stack stack_;
	Context to_resume_;
	Context current_;
	std::function<void()> routine_;
};
