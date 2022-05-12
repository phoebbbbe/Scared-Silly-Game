#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CApu.h"
#include "CGameMap.h"
#define WHITE RGB(255, 255, 255)

namespace game_framework {

	CApu::CApu() {
		Initialize();
	}
	void CApu::Initialize() {
		pos.x = 0;
		pos.y = SIZE_Y/3;
		curState = 0;			// initApu
		curMode = 1;			// still
		isMoved = false;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isFightLeft = isFightRight = isFightUp = isFightDown = false;

	}

	CApu::~CApu() {

	}
	int CApu::GetX1() {
		return pos.x;
	}

	int CApu::GetY1() {
		return pos.y;
	}

	int CApu::GetX2() {
		switch (curState) {
		case 1: return pos.x + initUp.Width();
		case 2: return pos.x + initDown.Width();
		case 3: return pos.x + initLeft.Width();
		case 4: return pos.x + initRight.Width();
		default:
			return pos.x + initRight.Width();
		}
	}

	int CApu::GetY2() {
		switch (curState) {
		case 1: return pos.y + initUp.Height();
		case 2: return pos.y + initDown.Height();
		case 3: return pos.y + initLeft.Height();
		case 4: return pos.y + initRight.Height();
		default:
			return pos.y + initRight.Height();
		}
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

	void CApu::LoadBitmap() {

		moveUp.AddBitmap(IDB_APU_UP1, WHITE);
		moveUp.AddBitmap(IDB_APU_UP2, WHITE);
		moveUp.AddBitmap(IDB_APU_UP3, WHITE);
		moveUp.AddBitmap(IDB_APU_UP4, WHITE);
		moveUp.AddBitmap(IDB_APU_UP5, WHITE);
		moveUp.AddBitmap(IDB_APU_UP5, WHITE);

		moveDown.AddBitmap(IDB_APU_DOWN1, WHITE);
		moveDown.AddBitmap(IDB_APU_DOWN2, WHITE);
		moveDown.AddBitmap(IDB_APU_DOWN3, WHITE);
		moveDown.AddBitmap(IDB_APU_DOWN4, WHITE);
		moveDown.AddBitmap(IDB_APU_DOWN5, WHITE);
		moveDown.AddBitmap(IDB_APU_DOWN5, WHITE);

		moveLeft.AddBitmap(IDB_APU_LEFT1, WHITE);
		moveLeft.AddBitmap(IDB_APU_LEFT2, WHITE);
		moveLeft.AddBitmap(IDB_APU_LEFT3, WHITE);
		moveLeft.AddBitmap(IDB_APU_LEFT4, WHITE);
		moveLeft.AddBitmap(IDB_APU_LEFT5, WHITE);
		moveLeft.AddBitmap(IDB_APU_LEFT5, WHITE);

		moveRight.AddBitmap(IDB_APU_RIGHT1, WHITE);
		moveRight.AddBitmap(IDB_APU_RIGHT2, WHITE);
		moveRight.AddBitmap(IDB_APU_RIGHT3, WHITE);
		moveRight.AddBitmap(IDB_APU_RIGHT4, WHITE);
		moveRight.AddBitmap(IDB_APU_RIGHT5, WHITE);
		moveRight.AddBitmap(IDB_APU_RIGHT5, WHITE);

		fightUp.AddBitmap(IDB_FIGHT_UP1, WHITE);
		fightUp.AddBitmap(IDB_FIGHT_UP2, WHITE);
		fightUp.AddBitmap(IDB_FIGHT_UP3, WHITE);
		fightUp.AddBitmap(IDB_FIGHT_UP4, WHITE);
		fightUp.AddBitmap(IDB_FIGHT_UP4, WHITE);

		fightDown.AddBitmap(IDB_FIGHT_DOWN1, WHITE);
		fightDown.AddBitmap(IDB_FIGHT_DOWN2, WHITE);
		fightDown.AddBitmap(IDB_FIGHT_DOWN3, WHITE);
		fightDown.AddBitmap(IDB_FIGHT_DOWN4, WHITE);
		fightDown.AddBitmap(IDB_FIGHT_DOWN4, WHITE);

		fightLeft.AddBitmap(IDB_FIGHT_LEFT1, WHITE);
		fightLeft.AddBitmap(IDB_FIGHT_LEFT2, WHITE);
		fightLeft.AddBitmap(IDB_FIGHT_LEFT3, WHITE);
		fightLeft.AddBitmap(IDB_FIGHT_LEFT4, WHITE);
		fightLeft.AddBitmap(IDB_FIGHT_LEFT4, WHITE);

		fightRight.AddBitmap(IDB_FIGHT_RIGHT1, WHITE);
		fightRight.AddBitmap(IDB_FIGHT_RIGHT2, WHITE);
		fightRight.AddBitmap(IDB_FIGHT_RIGHT3, WHITE);
		fightRight.AddBitmap(IDB_FIGHT_RIGHT4, WHITE);
		fightRight.AddBitmap(IDB_FIGHT_RIGHT4, WHITE);

		fail.AddBitmap(IDB_APU_LOSE1, WHITE);
		fail.AddBitmap(IDB_APU_LOSE2, WHITE);
		fail.AddBitmap(IDB_APU_LOSE3, WHITE);
		fail.AddBitmap(IDB_APU_LOSE4, WHITE);
		fail.AddBitmap(IDB_APU_LOSE5, WHITE);
		fail.AddBitmap(IDB_APU_LOSE6, WHITE);
		fail.AddBitmap(IDB_APU_LOSE6, WHITE);

		relive.AddBitmap(IDB_APU_RELIVE1, WHITE);
		relive.AddBitmap(IDB_APU_RELIVE2, WHITE);
		relive.AddBitmap(IDB_APU_RELIVE3, WHITE);
		relive.AddBitmap(IDB_APU_RELIVE4, WHITE);
		relive.AddBitmap(IDB_APU_RELIVE5, WHITE);
		relive.AddBitmap(IDB_APU_RELIVE5, WHITE);

		initApu.LoadBitmap(IDB_APU_RIGHT1, WHITE);
		initUp.LoadBitmap(IDB_APU_UP1, WHITE);
		initDown.LoadBitmap(IDB_APU_DOWN1, WHITE);
		initLeft.LoadBitmap(IDB_APU_LEFT1, WHITE);
		initRight.LoadBitmap(IDB_APU_RIGHT1, WHITE);
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
		pos.x = nx; pos.y = ny;
	}
	void CApu::SetXY(int stepSize) {
		if (isMovingLeft) {
			pos.x -= stepSize;
		}
		if (isMovingRight) {
			pos.x += stepSize;
		}
		if (isMovingUp) {
			pos.y -= stepSize;
		}
		if (isMovingDown) {
			pos.y += stepSize;
		}
	}

	int CApu::GetCurAnimationNum() {
		switch (curState) {
		case 1: return moveUp.GetCurrentBitmapNumber();
		case 2: return moveDown.GetCurrentBitmapNumber();
		case 3: return moveLeft.GetCurrentBitmapNumber();
		case 4: return moveRight.GetCurrentBitmapNumber();
		case 5: return fightUp.GetCurrentBitmapNumber();
		case 6: return fightDown.GetCurrentBitmapNumber();
		case 7: return fightLeft.GetCurrentBitmapNumber();
		case 8: return fightRight.GetCurrentBitmapNumber();
		case 9: return fail.GetCurrentBitmapNumber();
		default:
			return 0;
		}
	}
	int CApu::GetCurAnimationLastNum() {
		switch (curState) {
		case 1: return moveUp.GetLastBitmapNumber();
		case 2: return moveDown.GetLastBitmapNumber();
		case 3: return moveLeft.GetLastBitmapNumber();
		case 4: return moveRight.GetLastBitmapNumber();
		case 5: return fightUp.GetLastBitmapNumber();
		case 6: return fightDown.GetLastBitmapNumber();
		case 7: return fightLeft.GetLastBitmapNumber();
		case 8: return fightRight.GetLastBitmapNumber();
		case 9: return fail.GetLastBitmapNumber();
		default:
			return 0;
		}
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
	void CApu::OnShow() {
		switch (curState) {
		case 0:
			initApu.SetTopLeft(pos.x, pos.y);
			initApu.ShowBitmap();
			break;
		case 1:
			moveUp.SetTopLeft(pos.x, pos.y);
			moveUp.OnShow();
			break;
		case 2:
			moveDown.SetTopLeft(pos.x, pos.y);
			moveDown.OnShow();
			break;
		case 3:
			moveLeft.SetTopLeft(pos.x, pos.y);
			moveLeft.OnShow();
			break;
		case 4:
			moveRight.SetTopLeft(pos.x, pos.y);
			moveRight.OnShow();
			break;
		case 5:
			fightUp.SetTopLeft(pos.x, pos.y);
			fightUp.OnShow();
			break;
		case 6:
			fightDown.SetTopLeft(pos.x, pos.y);
			fightDown.OnShow();
			break;
		case 7:
			fightLeft.SetTopLeft(pos.x, pos.y);
			fightLeft.OnShow();
			break;
		case 8:
			fightRight.SetTopLeft(pos.x, pos.y);
			fightRight.OnShow();
			break;
		case 9:
			fail.SetTopLeft(pos.x, pos.y);
			fail.OnShow();
			break;
		default:
			break;
		}
	}
}