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

    void CApu::Initialize() {
        const int X_POS = 280;
        const int Y_POS = 400;
        x = X_POS;
        y = Y_POS;
        isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
    }

    void CApu::LoadBitmap() {
        animation.AddBitmap(IDB_APU1, RPG(255,255,255));
        animation.AddBitmap(IDB_APU2, RGB(255,255,255));
        animation.AddBitmap(IDB_APU3, RGB(255,255,255));
        animation.AddBitmap(IDB_APU4, RGB(255,255,255));
    }

    void CApu::OnMove() {
        const int STEP_SIZE = 2;
        animation.OnMove();
        if (isMovingLeft)
            x -= STEP_SIZE;
        if (isMovingRight)
            x += STEP_SIZE;
        if (isMovingUp)
            y -= STEP_SIZE;
        if (isMovingDown)
            y += STEP_SIZE;
    }

    void CApu::SetMovingDown(bool flag) {
        isMovingDown = flag;
    }

    void CApu::SetMovingLeft(bool flag) {
        isMovingLeft = flag;
    }

    void CApu::SetMovingRight(bool flag) {
        isMovingRight = flag;
    }
    
    void CApu::SetMovingUp(bool flag) {
        isMovingUp = flag;
    }

    void CApu::SetXY(int nx, int ny) {
        x = nx;
        y = ny;
    }

    void CApu::OnShow() {
        animation.SetTopLeft(x, y);
        animation.OnShow();
    }
}
