#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CApu.h"
#include "CGameMap.h"

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
		return x + initApu.Width();
	}

	int CApu::GetY2() {
		return y + initApu.Height();
	}

	int CApu::GetMode() {
		return curMode;
	}
	int CApu::GetState() {
		return curState;
	}
	bool CApu::GetMoved() {
		return isMoved;
	}
	void CApu::Initialize() {
		const int X_POS = 0;
		const int Y_POS = 180;
		x = X_POS;
		y = Y_POS;
		curState = 0;  // initApu
		curMode = 1; // still
		isMoved = false;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isFightLeft = isFightRight = isFightUp = isFightDown = false;

	}

	void CApu::LoadBitmap() {

		moveUp.AddBitmap(IDB_APU_UP1, RGB(255, 255, 255));
		moveUp.AddBitmap(IDB_APU_UP2, RGB(255, 255, 255));
		moveUp.AddBitmap(IDB_APU_UP3, RGB(255, 255, 255));
		moveUp.AddBitmap(IDB_APU_UP4, RGB(255, 255, 255));
		moveUp.AddBitmap(IDB_APU_UP5, RGB(255, 255, 255));
		moveUp.AddBitmap(IDB_APU_UP5, RGB(255, 255, 255));

		moveDown.AddBitmap(IDB_APU_DOWN1, RGB(255, 255, 255));
		moveDown.AddBitmap(IDB_APU_DOWN2, RGB(255, 255, 255));
		moveDown.AddBitmap(IDB_APU_DOWN3, RGB(255, 255, 255));
		moveDown.AddBitmap(IDB_APU_DOWN4, RGB(255, 255, 255));
		moveDown.AddBitmap(IDB_APU_DOWN5, RGB(255, 255, 255));
		moveDown.AddBitmap(IDB_APU_DOWN5, RGB(255, 255, 255));

		moveLeft.AddBitmap(IDB_APU_LEFT1, RGB(255, 255, 255));
		moveLeft.AddBitmap(IDB_APU_LEFT2, RGB(255, 255, 255));
		moveLeft.AddBitmap(IDB_APU_LEFT3, RGB(255, 255, 255));
		moveLeft.AddBitmap(IDB_APU_LEFT4, RGB(255, 255, 255));
		moveLeft.AddBitmap(IDB_APU_LEFT5, RGB(255, 255, 255));
		moveLeft.AddBitmap(IDB_APU_LEFT5, RGB(255, 255, 255));

		moveRight.AddBitmap(IDB_APU_RIGHT1, RGB(255, 255, 255));
		moveRight.AddBitmap(IDB_APU_RIGHT2, RGB(255, 255, 255));
		moveRight.AddBitmap(IDB_APU_RIGHT3, RGB(255, 255, 255));
		moveRight.AddBitmap(IDB_APU_RIGHT4, RGB(255, 255, 255));
		moveRight.AddBitmap(IDB_APU_RIGHT5, RGB(255, 255, 255));
		moveRight.AddBitmap(IDB_APU_RIGHT5, RGB(255, 255, 255));

		fightUp.AddBitmap(IDB_FIGHT_UP1, RGB(255, 255, 255));
		fightUp.AddBitmap(IDB_FIGHT_UP2, RGB(255, 255, 255));
		fightUp.AddBitmap(IDB_FIGHT_UP3, RGB(255, 255, 255));

		fightDown.AddBitmap(IDB_FIGHT_DOWN1, RGB(255, 255, 255));
		fightDown.AddBitmap(IDB_FIGHT_DOWN2, RGB(255, 255, 255));
		fightDown.AddBitmap(IDB_FIGHT_DOWN3, RGB(255, 255, 255));

		fightLeft.AddBitmap(IDB_FIGHT_BACK1, RGB(255, 255, 255));
		fightLeft.AddBitmap(IDB_FIGHT_BACK2, RGB(255, 255, 255));
		fightLeft.AddBitmap(IDB_FIGHT_BACK3, RGB(255, 255, 255));

		fightRight.AddBitmap(IDB_FIGHT_FRONT1, RGB(255, 255, 255));
		fightRight.AddBitmap(IDB_FIGHT_FRONT2, RGB(255, 255, 255));
		fightRight.AddBitmap(IDB_FIGHT_FRONT3, RGB(255, 255, 255));

		fail.AddBitmap(IDB_APU_LOSE, RGB(255, 255, 255));
		initApu.LoadBitmap(IDB_APU_RIGHT1, RGB(255, 255, 2555));
	}

	void CApu::OnMove() {
		const int STEP_SIZE = 1;
		if (curMode == 2) {
			SetXY(STEP_SIZE);
			if (curState == 1)
				moveUp.OnMove();
			else if (curState == 2)
				moveDown.OnMove();
			else if (curState == 3)
				moveLeft.OnMove();
			else if (curState == 4)
				moveRight.OnMove();
			else if (curState == 5)
				fightUp.OnMove();
			else if (curState == 6)
				fightDown.OnMove();
			else if (curState == 7)
				fightLeft.OnMove();
			else if (curState == 8)
				fightRight.OnMove();
			else if (curState == 9)
				fail.OnMove();
		}
	}
	void CApu::SetMovingUp(bool flag) {
		isMovingUp = flag;
		if (flag)
			curState = 1;
	}

	void CApu::SetMovingDown(bool flag) {
		isMovingDown = flag;
		if (flag)
			curState = 2;
	}

	void CApu::SetMovingLeft(bool flag) {
		isMovingLeft = flag;
		if (flag)
			curState = 3;
	}

	void CApu::SetMovingRight(bool flag) {
		isMovingRight = flag;
		if (flag)
			curState = 4;
	}

	void CApu::SetFightUp(bool flag) {
		isFightUp = flag;
		if (flag)
			curState = 5;
	}
	void CApu::SetFightDown(bool flag) {
		isFightDown = flag;
		if (flag)
			curState = 6;
	}
	void CApu::SetFightLeft(bool flag) {
		isFightLeft = flag;
		if (flag)
			curState = 7;
	}
	void CApu::SetFightRight(bool flag) {
		isFightRight = flag;
		if (flag)
			curState = 8;
	}
	void CApu::SetAllAction(bool flag) {
		isMovingUp = flag;
		isMovingDown = flag;
		isMovingLeft = flag;
		isMovingRight = flag;
		isFightUp = flag;
		isFightDown = flag;
		isFightLeft = flag;
		isFightRight = flag;
	}
	void CApu::SetXY(int nx, int ny) {
		x = nx; y = ny;
	}
	void CApu::SetXY(int stepSize) {
		if (isMovingLeft) {
			x -= stepSize;
		}
		if (isMovingRight) {
			x += stepSize;
		}
		if (isMovingUp) {
			y -= stepSize;
		}
		if (isMovingDown) {
			y += stepSize;
		}
	}

	void CApu::OnShow() {
		switch (curState) {
		case 0:
			initApu.SetTopLeft(x, y);
			initApu.ShowBitmap();
			break;
		case 1:
			moveUp.SetTopLeft(x, y);
			moveUp.OnShow();
			break;
		case 2:
			moveDown.SetTopLeft(x, y);
			moveDown.OnShow();
			break;
		case 3:
			moveLeft.SetTopLeft(x, y);
			moveLeft.OnShow();
			break;
		case 4:
			moveRight.SetTopLeft(x, y);
			moveRight.OnShow();
			break;
		case 5:
			fightUp.SetTopLeft(x, y);
			fightUp.OnShow();
			break;
		case 6:
			fightDown.SetTopLeft(x, y);
			fightDown.OnShow();
			break;
		case 7:
			fightLeft.SetTopLeft(x, y);
			fightLeft.OnShow();
			break;
		case 8:
			fightRight.SetTopLeft(x, y);
			fightRight.OnShow();
			break;
		case 9:
			fail.SetTopLeft(x, y);
			fail.OnShow();
			break;
		default:
			break;
		}
	}
	int CApu::GetCurAnimationNum() {
		if (curState == 1)
			return moveUp.GetCurrentBitmapNumber();
		else if (curState == 2)
			return moveDown.GetCurrentBitmapNumber();
		else if (curState == 3)
			return moveLeft.GetCurrentBitmapNumber();
		else if (curState == 4)
			return moveRight.GetCurrentBitmapNumber();
		else if (curState == 5)
			return fightUp.GetCurrentBitmapNumber();
		else if (curState == 6)
			return fightDown.GetCurrentBitmapNumber();
		else if (curState == 7)
			return fightLeft.GetCurrentBitmapNumber();
		else if (curState == 8)
			return fightRight.GetCurrentBitmapNumber();
		else if (curState == 9)
			return fail.GetCurrentBitmapNumber();
		else
			return 1;
	}
	int CApu::GetCurAnimationLastNum() {
		if (curState == 1)
			return moveUp.GetLastBitmapNumber();
		else if (curState == 2)
			return moveDown.GetLastBitmapNumber();
		else if (curState == 3)
			return moveLeft.GetLastBitmapNumber();
		else if (curState == 4)
			return moveRight.GetLastBitmapNumber();
		else if (curState == 5)
			return fightUp.GetLastBitmapNumber();
		else if (curState == 6)
			return fightDown.GetLastBitmapNumber();
		else if (curState == 7)
			return fightLeft.GetLastBitmapNumber();
		else if (curState == 8)
			return fightRight.GetLastBitmapNumber();
		else if (curState == 9)
			return fail.GetLastBitmapNumber();
		else
			return 0;
	}
	void CApu::ResetCurAnimation() {
		if (curState == 1)
			moveUp.Reset();
		else if (curState == 2)
			moveDown.Reset();
		else if (curState == 3)
			moveLeft.Reset();
		else if (curState == 4)
			moveRight.Reset();
		else if (curState == 5)
			fightUp.Reset();
		else if (curState == 6)
			fightDown.Reset();
		else if (curState == 7)
			fightLeft.Reset();
		else if (curState == 8)
			fightRight.Reset();
		else if (curState == 9)
			fail.Reset();
	}
	void CApu::SetMode(int flag) {
		curMode = flag;
	}
	void CApu::SetState(int flag) {
		curState = flag;
	}
	void CApu::SetMoved(bool flag) {
		isMoved = flag;
	}
}