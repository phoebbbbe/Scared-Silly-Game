#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CApu.h"
#include "CGhost.h"
#include "mygame.h"
#define WHITE RGB(255, 255, 255)

namespace game_framework {

	CGhost::CGhost(int x, int y) {
		Initialize(x, y);
	}
	CGhost::~CGhost() {
		Initialize(0, 0);
	}

	void CGhost::Initialize(int x, int y) {
		pos.x = x;
		pos.y = y;
		pos_show.x = pos.x - 5;
		pos_show.y = pos.y - 60;
		isAlive = true;
		isFighted = false;
		isMoving = true;
		switchState = true;
		followApu = true;
		curMode = 1;
		curState = 1;
		curDirect = 1;
		moveCounter = 30;
		dieCounter = 18;
	}

	int  CGhost::GetX1() { return pos.x; }
	int  CGhost::GetY1() { return pos.y; }
	int  CGhost::GetX2() { return pos.x + ghost_up.Width(); }
	int  CGhost::GetY2() { return pos.y + ghost_up.Height(); }
	int  CGhost::GetCurAnimationNum() {
		switch (curState) {
		case 1: return ghost_up.GetCurrentBitmapNumber();
		case 2: return ghost_down.GetCurrentBitmapNumber();
		case 3: return ghost_die.GetCurrentBitmapNumber();
		default: return 0;
		}
	}
	int CGhost::GetCurAnimationLastNum() {
		switch (curState) {
		case 1: return ghost_up.GetLastBitmapNumber();
		case 2: return ghost_down.GetLastBitmapNumber();
		case 3: return ghost_die.GetLastBitmapNumber();
		default: return 0;
		}
	}
	void CGhost::ResetCurAnimation() {
		if (curState == 1)
			ghost_up.Reset();
		else if (curState == 2)
			ghost_down.Reset();
		else if (curState == 3)
			ghost_die.Reset();
	}
	void CGhost::SetXY(int nx, int ny) {
		pos.x = nx; pos.y = ny;
	}
	void CGhost::SetAlive(bool alive) { isAlive = alive; }
	void CGhost::SetFighted(bool fighted) { isFighted = fighted; }
	void CGhost::SetMode(int mode) { curMode = mode; }
	void CGhost::SetState(int state) { curState = state; }
	void CGhost::SetFork() {

	}
	
	bool CGhost::IsAlive() { return isAlive; }
	bool CGhost::IsFighted() { return isFighted; }

	//bool CGhost::HitRectangle(int tx1, int ty1, int tx2, int ty2) {
	//	int x1 = tx1;
	//	int y1 = ty1;
	//	int x2 = tx2;
	//	int y2 = ty2;
	//	int x3 = pos.x;
	//	int y3 = pos.y + 5;
	//	int x4 = pos.x + ghost.Width();
	//	int y4 = pos.y + ghost.Height();
	//	return (x2 >= x3 && x1 <= x4 && y2 >= y3 && y1 <= y4);
	//}
	bool CGhost::HitApu(CApu *apu) {
		int x1 = apu->GetX1();
		int y1 = apu->GetY1();
		int x2 = apu->GetX2();
		int y2 = apu->GetY2();
		int x3 = pos.x;
		int y3 = pos.y + 5;
		int x4 = pos.x + ghost_up.Width();
		int y4 = pos.y + ghost_up.Height();
		return (x2 >= x3 && x1 <= x4 && y2 >= y3 && y1 <= y4);
	}
	void CGhost::FollowApu(CGameMap *map, CApu *apu) {
		const int STEP = 3;
		const int RANGE1 = 10;
		const int RANGE2 = 60;
		int xUp = pos.x, yUp = pos.y - STEP;
		int xDown = pos.x, yDown = pos.y + STEP;
		int xLeft = pos.x - STEP, yLeft = pos.y;
		int xRight = pos.x + STEP, yRight = pos.y;
		float disUp = (float)sqrt((double)((xUp - apu->GetX1())*(xUp - apu->GetX1()) + (yUp - apu->GetY1())*(yUp - apu->GetY1())));
		float disDown = (float)sqrt((double)((xDown - apu->GetX1())*(xDown - apu->GetX1()) + (yDown - apu->GetY1())*(yDown - apu->GetY1())));
		float disLeft = (float)sqrt((double)((xLeft - apu->GetX1())*(xLeft - apu->GetX1()) + (yLeft - apu->GetY1())*(yLeft - apu->GetY1())));
		float disRight = (float)sqrt((double)((xRight - apu->GetX1())*(xRight - apu->GetX1()) + (xRight - apu->GetY1())*(xRight - apu->GetY1())));
		if (isMoving) {
			switch (WhereIsApu(apu)) {
			case 1:
				if (disUp <= disRight && map->IsEmpty(pos.x, pos.y - RANGE1)) curDirect = 1;
				else if (map->IsEmpty(pos.x + RANGE2, pos.y)) curDirect = 4;
				else if (map->IsEmpty(pos.x, pos.y + RANGE2)) curDirect = 2;
				else if (map->IsEmpty(pos.x - RANGE1, pos.y)) curDirect = 3;
				else curDirect = 0;
				break;
			case 2:
				if (disUp <= disLeft && map->IsEmpty(pos.x, pos.y - RANGE1)) curDirect = 1;
				else if (map->IsEmpty(pos.x - RANGE1, pos.y)) curDirect = 3;
				else if (map->IsEmpty(pos.x, pos.y + RANGE2)) curDirect = 2;
				else if (map->IsEmpty(pos.x + RANGE2, pos.y)) curDirect = 4;
				else curDirect = 0;
				break;
			case 3:
				if (disDown <= disLeft && map->IsEmpty(pos.x, pos.y + RANGE2)) curDirect = 2;
				else if (map->IsEmpty(pos.x - RANGE1, pos.y)) curDirect = 3;
				else if (map->IsEmpty(pos.x, pos.y - RANGE1)) curDirect = 1;
				else if (map->IsEmpty(pos.x + RANGE2, pos.y)) curDirect = 4;
				else curDirect = 0;
				break;
			case 4:
				if (disDown <= disRight && map->IsEmpty(pos.x, pos.y + RANGE2)) curDirect = 2;
				else if (map->IsEmpty(pos.x + RANGE2, pos.y)) curDirect = 4;
				else if (map->IsEmpty(pos.x, pos.y - RANGE1)) curDirect = 1;
				else if (map->IsEmpty(pos.x - RANGE1, pos.y)) curDirect = 3;
				else curDirect = 0;
				break;
			}
		}
		if (followApu) {
			if (curDirect == 1)
				SetXY(xUp, yUp);
			else if (curDirect == 2)
				SetXY(xDown, yDown);
			else if (curDirect == 3)
				SetXY(xLeft, yLeft);
			else if (curDirect == 4)
				SetXY(xRight, yRight);
		}
		if (moveCounter < 0) {
			followApu = false;
			isMoving = true;
		}
		isMoving = false;
	}
	int CGhost::WhereIsApu(CApu *apu) {
		int X1 = pos.x, Y1 = pos.y;
		int X2 = apu->GetX1(), Y2 = apu->GetY1();
		float dis = (float)sqrt((double)((X2 - X1)*(X2 - X1) + (Y2 - Y1)*(Y2 - Y1)));
		if (dis < 0.001)
			return 0;
		X2 -= X1;
		Y2 -= Y1;
		if (X2 >= 0 && Y2 <= 0) return 1;
		else if (X2 <= 0 && Y2 <= 0) return 2;
		else if (X2 <= 0 && Y2 >= 0) return 3;
		else if (X2 >= 0 && Y2 >= 0) return 4;
		else return 0;
	}
	
	void CGhost::SwitchState() {
		if (switchState) {
			curMode = 2;
			ResetCurAnimation();
			if (curState == 1) {
				curState = 2;
				moveCounter = 30;
				followApu = true;
			}
			else if (curState == 2)  curState = 1;
			else if (curState == 3) dieCounter = 18;
		}
		switchState = false;
	}

	void CGhost::OnMove(CGameMap *map, CApu *apu) {
		if (isAlive)
		{
			if (isFighted) {
				curState = 3;
				CAudio::Instance()->Play(AUDIO_FIGHT);
			}
			else {
				if (apu->GetMode() == 2) SwitchState();
				else switchState = true;

				if (HitApu(apu)) {
					curMode = 1;
					apu->SetFail(true);
				}
			}	

			if (curMode == 2) {
				if (GetCurAnimationNum() == GetCurAnimationLastNum()) {
					curMode = 1;
					//isMoving = true;
				}
				if (curState == 1) {
					ghost_up.OnMove();
					ghost_up.OnMove();
				}
				else if (curState == 2) {
					ghost_down.OnMove();
					ghost_down.OnMove();
					FollowApu(map, apu);
				}
			}

			if (curState == 3) {
				ghost_die.OnMove();
				ghost_die.OnMove();
			}
		}
	}

	void CGhost::OnShow(CGameMap *map) {
		pos_show.x = pos.x;
		pos_show.y = pos.y - 50;
		if (isAlive) {
			switch (curState) {
			case 1:
				ghost_up.SetTopLeft(map->ScreenX(pos_show.x), map->ScreenY(pos_show.y));
				ghost_up.OnShow();
				break;
			case 2:
				moveCounter--;
				ghost_down.SetTopLeft(map->ScreenX(pos_show.x), map->ScreenY(pos_show.y));
				ghost_down.OnShow();
				fork1.SetTopLeft(map->ScreenX(pos_show.x - 50), map->ScreenY(pos_show.y));
				fork2.SetTopLeft(map->ScreenX(pos_show.x + 50), map->ScreenY(pos_show.y));
				fork3.SetTopLeft(map->ScreenX(pos_show.x), map->ScreenY(pos_show.y - 80));
				fork4.SetTopLeft(map->ScreenX(pos_show.x), map->ScreenY(pos_show.y + 80));
				//fork1.ShowBitmap();
				//fork2.ShowBitmap();
				//fork3.ShowBitmap();
				//fork4.ShowBitmap();
				break;
			case 3:
				dieCounter--;
				if (dieCounter < 0) {
					isAlive = false;
				}
				ghost_die.SetTopLeft(map->ScreenX(pos_show.x), map->ScreenY(pos_show.y));
				ghost_die.OnShow();
				break;
			default:
				break;
			}
		}
	}

	CBallon::CBallon(int x, int y) : CGhost::CGhost(x, y) {}
	CBallon::~CBallon() {}
	void CBallon::LoadBitmap() {

		ghost_up.AddBitmap(IDB_BALLOON5, WHITE);
		ghost_up.AddBitmap(IDB_BALLOON5, WHITE);
		ghost_up.AddBitmap(IDB_BALLOON4, WHITE);
		ghost_up.AddBitmap(IDB_BALLOON3, WHITE);
		ghost_up.AddBitmap(IDB_BALLOON1, WHITE);
		
		ghost_down.AddBitmap(IDB_BALLOON1, WHITE);
		ghost_down.AddBitmap(IDB_BALLOON1, WHITE);
		ghost_down.AddBitmap(IDB_BALLOON3, WHITE);
		ghost_down.AddBitmap(IDB_BALLOON4, WHITE);
		ghost_down.AddBitmap(IDB_BALLOON5, WHITE);

		ghost_die.AddBitmap(IDB_BALLOON_DIE1, WHITE);
		ghost_die.AddBitmap(IDB_BALLOON_DIE2, WHITE);
		ghost_die.AddBitmap(IDB_BALLOON_DIE3, WHITE);
		ghost_die.AddBitmap(IDB_BALLOON_DIE3, WHITE);

		fork1.LoadBitmap(IDB_FORK, WHITE);
		fork2.LoadBitmap(IDB_FORK, WHITE);
		fork3.LoadBitmap(IDB_FORK, WHITE);
		fork4.LoadBitmap(IDB_FORK, WHITE);
	}

	CBat::CBat(int x, int y) : CGhost::CGhost(x, y) {}
	CBat::~CBat() {}
	void CBat::LoadBitmap() {
		ghost_up.AddBitmap(IDB_BALLOON1, WHITE);
		ghost_up.AddBitmap(IDB_BALLOON2, WHITE);
		ghost_up.AddBitmap(IDB_BALLOON3, WHITE);

		ghost_down.AddBitmap(IDB_BALLOON1, WHITE);
		ghost_down.AddBitmap(IDB_BALLOON4, WHITE);
		ghost_down.AddBitmap(IDB_BALLOON5, WHITE);

		ghost_die.AddBitmap(IDB_BALLOON_DIE1, WHITE);
		ghost_die.AddBitmap(IDB_BALLOON_DIE2, WHITE);
		ghost_die.AddBitmap(IDB_BALLOON_DIE3, WHITE);

		fork1.LoadBitmap(IDB_FORK, WHITE);
		fork2.LoadBitmap(IDB_FORK, WHITE);
		fork3.LoadBitmap(IDB_FORK, WHITE);
		fork4.LoadBitmap(IDB_FORK, WHITE);
	}

	CPumpkin::CPumpkin(int x, int y) : CGhost::CGhost(x, y) {}
	CPumpkin::~CPumpkin() {}
	void CPumpkin::LoadBitmap() {
		ghost_up.AddBitmap(IDB_BALLOON1, WHITE);
		ghost_up.AddBitmap(IDB_BALLOON2, WHITE);
		ghost_up.AddBitmap(IDB_BALLOON3, WHITE);

		ghost_down.AddBitmap(IDB_BALLOON1, WHITE);
		ghost_down.AddBitmap(IDB_BALLOON4, WHITE);
		ghost_down.AddBitmap(IDB_BALLOON5, WHITE);

		ghost_die.AddBitmap(IDB_BALLOON_DIE1, WHITE);
		ghost_die.AddBitmap(IDB_BALLOON_DIE2, WHITE);
		ghost_die.AddBitmap(IDB_BALLOON_DIE3, WHITE);
		ghost_die.AddBitmap(IDB_BALLOON_DIE3, WHITE);

		fork1.LoadBitmap(IDB_FORK, WHITE);
		fork2.LoadBitmap(IDB_FORK, WHITE);
		fork3.LoadBitmap(IDB_FORK, WHITE);
		fork4.LoadBitmap(IDB_FORK, WHITE);
	}
}