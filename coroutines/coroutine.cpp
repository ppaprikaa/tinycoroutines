#include <coroutines/coroutine.hpp>
#include <coroutines/status.hpp>
#include <ctx/stack/stack.hpp>
#include <functional>
#include <mmap-allocator/pagesize.hpp>

Coroutine::Coroutine(std::function<void()> routine)
    : routine_(routine), stack_(Stack::AllocateBytes(2097152)) {
    current_.Setup(stack_.MutableView(), this);
    status_ = CoroutineStatus::NotCalled;
}

void Coroutine::Suspend() {
    switch (status_) {
    case CoroutineStatus::Running:
        break;
    default:
        return;
    }

    status_ = CoroutineStatus::Suspended;
    current_.SwitchTo(to_resume_);
}

void Coroutine::Call() {
    switch (status_) {
    case CoroutineStatus::NotCalled:
        break;
    default:
        return;
    }

    status_ = CoroutineStatus::ReadyToCall;
    Resume();
}

void Coroutine::Resume() {
    switch (status_) {
    case CoroutineStatus::Suspended:
        break;
    case CoroutineStatus::ReadyToCall:
        break;
    default:
        return;
    }

    status_ = CoroutineStatus::Running;
    to_resume_.SwitchTo(current_);
}

void Coroutine::Run() noexcept {
    routine_();
	Exit();
}

void Coroutine::Exit() {
    switch (status_) {
    case CoroutineStatus::Running:
        break;
    default:
        return;
    }

    status_ = CoroutineStatus::Exited;
    current_.SwitchTo(to_resume_);
}
