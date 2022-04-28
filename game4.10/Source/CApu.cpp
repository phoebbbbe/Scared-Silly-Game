#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CApu.h"

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
	int CApu::GetDir() {
		return curDir;
	}
	bool CApu::GetMoved() {
		return isMoved;
	}
	void CApu::Initialize() {
		const int X_POS = 0;
		const int Y_POS = 180;
		x = X_POS;
		y = Y_POS;
		curDir = 0;  // initApu
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

		moveDown.AddBitmap(IDB_APU_DOWN1, RGB(255, 255, 255));
		moveDown.AddBitmap(IDB_APU_DOWN2, RGB(255, 255, 255));
		moveDown.AddBitmap(IDB_APU_DOWN3, RGB(255, 255, 255));
		moveDown.AddBitmap(IDB_APU_DOWN4, RGB(255, 255, 255));

		moveLeft.AddBitmap(IDB_APU_BACK1, RGB(255, 255, 255));
		moveLeft.AddBitmap(IDB_APU_BACK2, RGB(255, 255, 255));
		moveLeft.AddBitmap(IDB_APU_BACK3, RGB(255, 255, 255));
		moveLeft.AddBitmap(IDB_APU_BACK4, RGB(255, 255, 255));

		moveRight.AddBitmap(IDB_APU_FRONT1, RGB(255, 255, 255));
		moveRight.AddBitmap(IDB_APU_FRONT2, RGB(255, 255, 255));
		moveRight.AddBitmap(IDB_APU_FRONT3, RGB(255, 255, 255));
		moveRight.AddBitmap(IDB_APU_FRONT4, RGB(255, 255, 255));

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

		initApu.LoadBitmap(IDB_APU_FRONT1, RGB(255, 255, 2555));
	}

	void CApu::OnMove() {
		if (curMode == 2) {
			if (curDir == 1)
				moveUp.OnMove();
			else if (curDir == 2)
				moveDown.OnMove();
			else if (curDir == 3)
				moveLeft.OnMove();
			else if (curDir == 4)
				moveRight.OnMove();
			else if (curDir == 5)
				fightUp.OnMove();
			else if (curDir == 6)
				fightDown.OnMove();
			else if (curDir == 7)
				fightLeft.OnMove();
			else if (curDir == 8)
				fightRight.OnMove();
		}
	}

	void CApu::SetMovingUp(bool flag) {
		isMovingUp = flag;
		if (flag)
			curDir = 1;
	}

	void CApu::SetMovingDown(bool flag) {
		isMovingDown = flag;
		if (flag)
			curDir = 2;
	}

	void CApu::SetMovingLeft(bool flag) {
		isMovingLeft = flag;
		if (flag)
			curDir = 3;
	}

	void CApu::SetMovingRight(bool flag) {
		isMovingRight = flag;
		if (flag)
			curDir = 4;
	}

	void CApu::SetFightUp(bool flag) {
		isFightUp = flag;
		if (flag)
			curDir = 5;
	}
	void CApu::SetFightDown(bool flag) {
		isFightDown = flag;
		if (flag)
			curDir = 6;
	}
	void CApu::SetFightLeft(bool flag) {
		isFightLeft = flag;
		if (flag)
			curDir = 7;
	}
	void CApu::SetFightRight(bool flag) {
		isFightRight = flag;
		if (flag)
			curDir = 8;
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
		switch (curDir) {
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
		default:
			break;
		}
	}
	int CApu::GetCurAnimationNum() {
		if (curDir == 1)
			return moveUp.GetCurrentBitmapNumber();
		else if (curDir == 2)
			return moveDown.GetCurrentBitmapNumber();
		else if (curDir == 3)
			return moveLeft.GetCurrentBitmapNumber();
		else if (curDir == 4)
			return moveRight.GetCurrentBitmapNumber();
		else if (curDir == 5)
			return fightUp.GetCurrentBitmapNumber();
		else if (curDir == 6)
			return fightDown.GetCurrentBitmapNumber();
		else if (curDir == 7)
			return fightLeft.GetCurrentBitmapNumber();
		else if (curDir == 8)
			return fightRight.GetCurrentBitmapNumber();
		else
			return 1;
	}
	int CApu::GetCurAnimationLastNum() {
		if (curDir == 1)
			return moveUp.GetLastBitmapNumber();
		else if (curDir == 2)
			return moveDown.GetLastBitmapNumber();
		else if (curDir == 3)
			return moveLeft.GetLastBitmapNumber();
		else if (curDir == 4)
			return moveRight.GetLastBitmapNumber();
		else if (curDir == 5)
			return fightUp.GetLastBitmapNumber();
		else if (curDir == 6)
			return fightDown.GetLastBitmapNumber();
		else if (curDir == 7)
			return fightLeft.GetLastBitmapNumber();
		else if (curDir == 8)
			return fightRight.GetLastBitmapNumber();
		else
			return 0;
	}
	void CApu::ResetCurAnimation() {
		if (curDir == 1)
			moveUp.Reset();
		else if (curDir == 2)
			moveDown.Reset();
		else if (curDir == 3)
			moveLeft.Reset();
		else if (curDir == 4)
			moveRight.Reset();
		else if (curDir == 5)
			fightUp.Reset();
		else if (curDir == 6)
			fightDown.Reset();
		else if (curDir == 7)
			fightLeft.Reset();
		else if (curDir == 8)
			fightRight.Reset();
	}
	void CApu::SetMode(int flag) {
		curMode = flag;
	}
	void CApu::SetDir(int flag) {
		curDir = flag;
	}
	void CApu::SetMoved(bool flag) {
		isMoved = flag;
	}
}