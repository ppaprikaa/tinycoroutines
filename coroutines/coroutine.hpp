#pragma once

#include <coroutines/routine.hpp>
#include <coroutines/status.hpp>
#include <ctx/context.hpp>
#include <ctx/stack/stack.hpp>
#include <ctx/trampoline.hpp>

class Coroutine : public ITrampoline {
  public:
    Coroutine() = delete;
    Coroutine(Routine routine);

    Coroutine(Coroutine &coroutine) = delete;
    Coroutine &operator=(Coroutine &coroutine) = delete;

    void operator()();

    CoroutineStatus Status() { return status_; }

    void Call();

    void Resume();

    void Suspend();

  private:
    void SetupCoroutineContext();

    void Run() noexcept override;

    void Exit();

  private:
    CoroutineStatus status_;
    Stack stack_;
    Context to_resume_;
    Context current_;
    Routine routine_;
};
