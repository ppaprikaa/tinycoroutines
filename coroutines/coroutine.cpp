#include <ctx/stack/stack.hpp>
#include <mmap-allocator/pagesize.hpp>
#include <coroutines/coroutine.hpp>
#include <functional>
Coroutine::Coroutine(std::function<void()> routine) : routine_(routine), stack_(Stack::AllocateBytes(4096)) {
	current_.Setup(stack_.MutableView(), this);
}

void Coroutine::Suspend() {
	current_.SwitchTo(to_resume_);
}

void Coroutine::Call() {
	Resume();
}

void Coroutine::Resume() {
	to_resume_.SwitchTo(current_);
}

void Coroutine::Run() noexcept {
	routine_();
	Suspend();
}
