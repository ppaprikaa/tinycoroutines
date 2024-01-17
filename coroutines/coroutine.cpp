#include <coroutines/coroutine.hpp>
#include <coroutines/status.hpp>
#include <ctx/stack/stack.hpp>
#include <mmap-allocator/pagesize.hpp>

Coroutine::Coroutine(Routine routine)
    : routine_(std::move(routine)), stack_(Stack::AllocateBytes(2097152)) {
    current_.Setup(stack_.MutableView(), this);
    status_ = CoroutineStatus::NotCalled;
}

void Coroutine::Suspend() {
    if (status_ != CoroutineStatus::Running)
        return;

    status_ = CoroutineStatus::Suspended;
    current_.SwitchTo(to_resume_);
}

void Coroutine::operator()() { Call(); }

void Coroutine::Call() {
    if (status_ != CoroutineStatus::NotCalled)
        return;

    status_ = CoroutineStatus::Running;
    to_resume_.SwitchTo(current_);
}

void Coroutine::Resume() {
    if (status_ != CoroutineStatus::Suspended)
        return;

    status_ = CoroutineStatus::Running;
    to_resume_.SwitchTo(current_);
}

void Coroutine::Run() noexcept {
    routine_();
    Exit();
}

void Coroutine::Exit() {
    if (status_ != CoroutineStatus::Running)
        return;

    status_ = CoroutineStatus::Exited;
    current_.SwitchTo(to_resume_);
}
