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
		Initialize(0, 0);
	}
	CApu::CApu(int x, int y) {
		Initialize(x, y);
	}
	CApu::~CApu() {}
	void CApu::Initialize(int x, int y) {
		pos.x = x;
		pos.y = y;
		curState = 0;			// initApu
		curMode = 1;			// still
		isMoved = false;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isFightLeft = isFightRight = isFightUp = isFightDown = false;
	}

	int CApu::GetX1() { return pos.x; }
	int CApu::GetY1() { return pos.y; }
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
	int CApu::GetMode() { return curMode; }
	int CApu::GetState() { return curState; }
	bool CApu::GetMoved() { return isMoved; }
	
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
		case 10: return success.GetCurrentBitmapNumber();
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
		case 10: return success.GetLastBitmapNumber();
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
		else if (curState == 10)
			success.Reset();
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
	void CApu::SetMode(int flag) { curMode = flag; }
	void CApu::SetState(int flag) { curState = flag; }
	void CApu::SetMoved(bool flag) { isMoved = flag; }
	void CApu::SetFail(bool flag) { curState = 9; }
	void CApu::SetSucceed(bool flag) { curState = 10; }
	void CApu::SetRelive(bool flag) { curState = 11; }

	bool CApu::IsFail() {
		if (curState == 9) return true;
		else return false;
	}
	bool CApu::IsSucceed() { 
		if (curState == 10) return true;
		else return false;
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

		success.AddBitmap(IDB_APU_SUCCESS1, WHITE);
		success.AddBitmap(IDB_APU_SUCCESS2, WHITE);
		success.AddBitmap(IDB_APU_SUCCESS3, WHITE);
		success.AddBitmap(IDB_APU_SUCCESS4, WHITE);
		success.AddBitmap(IDB_APU_SUCCESS5, WHITE);

		initApu.LoadBitmap(IDB_APU_RIGHT1, WHITE);
		initUp.LoadBitmap(IDB_APU_UP1, WHITE);
		initDown.LoadBitmap(IDB_APU_DOWN1, WHITE);
		initLeft.LoadBitmap(IDB_APU_LEFT1, WHITE);
		initRight.LoadBitmap(IDB_APU_RIGHT1, WHITE);
	}
	void CApu::OnMove(CGameMap *map) {
		const int STEP = 1;
		if (curMode == 2) {
			if (GetCurAnimationNum() == GetCurAnimationLastNum()) {
				ResetCurAnimation();
				curMode = 1;
				SetAllAction(false);
			}
			switch (curState) {
			case 1:
				if (map->IsEmpty(pos.x, pos.y - 1)) {
					pos.y -= STEP;
					map->SetSY(pos.y - 200);
					moveUp.OnMove();
					if (map->HasPiece(GetX1(), GetY1(), GetX2(), GetY2())) {
						curState = 10;
					}
				}
				else {
					//map->SetSY(pos.y - 200);
					moveUp.OnMove();
				}
				break;
			case 2:
				if (map->IsEmpty(pos.x, pos.y + 40)) {
					pos.y += STEP;
					map->SetSY(pos.y - 200);
					moveDown.OnMove();
					if (map->HasPiece(GetX1(), GetY1(), GetX2(), GetY2())) {
						curState = 10;
					}
				}
				else {
					//map->SetSY(pos.y - 200);
					moveDown.OnMove();
				}
				break;
			case 3:
				if (map->IsEmpty(pos.x - 30, pos.y)) {
					pos.x -= STEP;
					map->SetSX(pos.x - 150);
					moveLeft.OnMove();
					if (map->HasPiece(GetX1(), GetY1(), GetX2(), GetY2())) {
						curState = 10;
					}
				}
				else {
					//map->SetSX(pos.x - 150);
					moveLeft.OnMove();
				}
				break;
			case 4:
				if (map->IsEmpty(pos.x + 30, pos.y)) {
					pos.x += STEP;
					map->SetSX(pos.x - 150);
					moveRight.OnMove();
					if (map->HasPiece(GetX1(), GetY1(), GetX2(), GetY2())) {
						curState = 10;
					}
				}
				else {
					//map->SetSX(pos.x - 150);
					moveRight.OnMove();
				}
				break;
			case 5:
				fightUp.OnMove();
				break;
			case 6:
				fightDown.OnMove();
				break;
			case 7:
				fightLeft.OnMove();
				break;
			case 8:
				fightRight.OnMove();
				break;
			case 9:
				fail.OnMove();
				break;
			case 10:
				success.OnMove();
				break;
			case 11:
				relive.OnMove();
				break;
			default:
				break;
			}
		}
	}
	void CApu::OnShow(CGameMap *map) {
		switch (curState) {
		case 0:
			initApu.SetTopLeft(map->ScreenX(pos.x), map->ScreenY(pos.y));
			initApu.ShowBitmap();
			break;
		case 1:
			moveUp.SetTopLeft(map->ScreenX(pos.x), map->ScreenY(pos.y));
			moveUp.OnShow();
			break;
		case 2:
			moveDown.SetTopLeft(map->ScreenX(pos.x), map->ScreenY(pos.y));
			moveDown.OnShow();
			break;
		case 3:
			moveLeft.SetTopLeft(map->ScreenX(pos.x), map->ScreenY(pos.y));
			moveLeft.OnShow();
			break;
		case 4:
			moveRight.SetTopLeft(map->ScreenX(pos.x), map->ScreenY(pos.y));
			moveRight.OnShow();
			break;
		case 5:
			fightUp.SetTopLeft(map->ScreenX(pos.x), map->ScreenY(pos.y));
			fightUp.OnShow();
			break;
		case 6:
			fightDown.SetTopLeft(map->ScreenX(pos.x), map->ScreenY(pos.y));
			fightDown.OnShow();
			break;
		case 7:
			fightLeft.SetTopLeft(map->ScreenX(pos.x), map->ScreenY(pos.y));
			fightLeft.OnShow();
			break;
		case 8:
			fightRight.SetTopLeft(map->ScreenX(pos.x), map->ScreenY(pos.y));
			fightRight.OnShow();
			break;
		case 9:
			fail.SetTopLeft(map->ScreenX(pos.x), map->ScreenY(pos.y));
			fail.OnShow();
			break;
		case 10:
			success.SetTopLeft(map->ScreenX(pos.x), map->ScreenY(pos.y));
			success.OnShow();
		default:
			break;
		}
	}
}