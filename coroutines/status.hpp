#pragma once

enum class CoroutineStatus {
    NotCalled,
    ReadyToCall,
    Running,
    Suspended,
    ReadyToExit
};
