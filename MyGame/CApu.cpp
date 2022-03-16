#include "CApu.h"
#include "../GameLibrary/gamelib.h"

namespace game_framework {
    CApu::CApu() {
        Initialize();
    }

    int CApu::GetX1() {
        return x;
    }

    int CApu::GetY1() {
        return y;
    }

    int CApu::GetX2() {
        return x + animation.Width();
    }
}
