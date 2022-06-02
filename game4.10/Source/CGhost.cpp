#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CApu.h"
#include "CGhost.h"

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
		isAlive = true;
		isFighted = false;
		switchState = true;
		followApu = true;
		curMode = 1;
		curState = 1;
		curDirect = 1;
		counter = 30;
	}

	int  CGhost::GetX1() { return pos.x; }
	int  CGhost::GetY1() { return pos.y; }
	int  CGhost::GetX2() { return pos.x + ghost.Width(); }
	int  CGhost::GetY2() { return pos.y + ghost.Height(); }
	int  CGhost::GetCurAnimationNum() {
		switch (curState) {
		case 1: return ghost.GetCurrentBitmapNumber();
		case 2: return ghost.GetCurrentBitmapNumber();
		case 3: return ghost_die.GetCurrentBitmapNumber();
		default: return 0;
		}
	}
	int CGhost::GetCurAnimationLastNum() {
		switch (curState) {
		case 1: return ghost.GetLastBitmapNumber();
		case 2: return ghost.GetLastBitmapNumber();
		case 3: return ghost_die.GetLastBitmapNumber();
		default: return 0;
		}
	}
	void CGhost::ResetCurAnimation() {
		if (curState == 1)
			ghost.Reset();
		else if (curState == 2)
			ghost.Reset();
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
		int x4 = pos.x + ghost.Width();
		int y4 = pos.y + ghost.Height();
		return (x2 >= x3 && x1 <= x4 && y2 >= y3 && y1 <= y4);
	}
	void CGhost::FollowApu(CApu *apu) {
		const int STEP = 1;
		int xUp = pos.x, yUp = pos.y - STEP;
		int xDown = pos.x, yDown = pos.y + STEP;
		int xLeft = pos.x - STEP, yLeft = pos.y;
		int xRight = pos.x + STEP, yRight = pos.y;
		float disUp = (float)sqrt((double)((xUp - apu->GetX1())*(xUp - apu->GetX1()) + (yUp - apu->GetY1())*(yUp - apu->GetY1())));
		float disDown = (float)sqrt((double)((xDown - apu->GetX1())*(xDown - apu->GetX1()) + (yDown - apu->GetY1())*(yDown - apu->GetY1())));
		float disLeft = (float)sqrt((double)((xLeft - apu->GetX1())*(xLeft - apu->GetX1()) + (yLeft - apu->GetY1())*(yLeft - apu->GetY1())));
		float disRight = (float)sqrt((double)((xRight - apu->GetX1())*(xRight - apu->GetX1()) + (xRight - apu->GetY1())*(xRight - apu->GetY1())));
		switch (WhereIsApu(apu)) {
		case 1:
			if (disUp <= disRight) curDirect = 1;
			else curDirect = 4;
			break;
		case 2:
			if (disUp <= disLeft) curDirect = 1;
			else curDirect = 3;
			break;
		case 3:
			if (disDown <= disLeft) curDirect = 2;
			else curDirect = 3;
			break;
		case 4:
			if (disDown <= disRight) curDirect = 2;
			else curDirect = 4;
			break;
		}
		TRACE("ghost follow : %d\n", followApu);
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
		if (counter < 0)
			followApu = false;

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
			if (curState == 1) {
				curState = 2;
				followApu = true;
				counter = 30;
			}
			else if (curState == 2)  curState = 1;
		}
		switchState = false;
	}

	void CGhost::OnMove(CGameMap *map, CApu *apu) {
		const int STEP = 1;
		if (isAlive)
		{
			if (isFighted)  curState = 3;
			else {
				if (apu->GetMode() == 2) SwitchState();
				else switchState = true;

				if (HitApu(apu))  apu->SetFail(true);
			}	

			if (curMode == 2) {
				switch (curState) {
				case 1:
					ResetCurAnimation();
					curMode = 1;
					break;
				case 2:
					if (GetCurAnimationNum() == GetCurAnimationLastNum()) {
						curMode = 1;
					}
					ghost.OnMove();
					FollowApu(apu);
					break;
				case 3:
					ghost_die.OnMove();
					break;
				default:
					break;
				}
			}
			

			
		}
	}

	void CGhost::OnShow(CGameMap *map) {
		if (isAlive) {
			switch (curState) {
			case 1:
				ghost.SetTopLeft(map->ScreenX(pos.x), map->ScreenY(pos.y));
				ghost.OnShow();
				break;
			case 2:
				counter--;
				ghost.SetTopLeft(map->ScreenX(pos.x), map->ScreenY(pos.y));
				ghost.OnShow();
				fork1.SetTopLeft(map->ScreenX(pos.x - 50), map->ScreenY(pos.y));
				fork2.SetTopLeft(map->ScreenX(pos.x + 50), map->ScreenY(pos.y));
				fork3.SetTopLeft(map->ScreenX(pos.x), map->ScreenY(pos.y - 80));
				fork4.SetTopLeft(map->ScreenX(pos.x), map->ScreenY(pos.y + 80));
				fork1.ShowBitmap();
				fork2.ShowBitmap();
				fork3.ShowBitmap();
				fork4.ShowBitmap();
				break;
			case 3:
				ghost_die.SetTopLeft(map->ScreenX(pos.x), map->ScreenY(pos.y));
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
		ghost.AddBitmap(IDB_BALLOON1, RGB(255, 255, 255));
		ghost.AddBitmap(IDB_BALLOON3, RGB(255, 255, 255));
		ghost.AddBitmap(IDB_BALLOON2, RGB(255, 255, 255));
		ghost.AddBitmap(IDB_BALLOON4, RGB(255, 255, 255));
		ghost.AddBitmap(IDB_BALLOON4, RGB(255, 255, 255));
		ghost.AddBitmap(IDB_BALLOON5, RGB(255, 255, 255));

		ghost_die.AddBitmap(IDB_BALLOON_DIE1, RGB(255, 255, 255));
		ghost_die.AddBitmap(IDB_BALLOON_DIE2, RGB(255, 255, 255));
		ghost_die.AddBitmap(IDB_BALLOON_DIE3, RGB(255, 255, 255));
		ghost_die.AddBitmap(IDB_BALLOON_DIE3, RGB(255, 255, 255));

		fork1.LoadBitmap(IDB_FORK, RGB(255, 255, 255));
		fork2.LoadBitmap(IDB_FORK, RGB(255, 255, 255));
		fork3.LoadBitmap(IDB_FORK, RGB(255, 255, 255));
		fork4.LoadBitmap(IDB_FORK, RGB(255, 255, 255));
	}

	CBat::CBat(int x, int y) : CGhost::CGhost(x, y) {}
	CBat::~CBat() {}
	void CBat::LoadBitmap() {
		ghost.AddBitmap(IDB_BALLOON1, RGB(255, 255, 255));
		ghost.AddBitmap(IDB_BALLOON3, RGB(255, 255, 255));
		ghost.AddBitmap(IDB_BALLOON2, RGB(255, 255, 255));
		ghost.AddBitmap(IDB_BALLOON4, RGB(255, 255, 255));
		ghost.AddBitmap(IDB_BALLOON4, RGB(255, 255, 255));
		ghost.AddBitmap(IDB_BALLOON5, RGB(255, 255, 255));

		ghost_die.AddBitmap(IDB_BALLOON_DIE1, RGB(255, 255, 255));
		ghost_die.AddBitmap(IDB_BALLOON_DIE2, RGB(255, 255, 255));
		ghost_die.AddBitmap(IDB_BALLOON_DIE3, RGB(255, 255, 255));
		ghost_die.AddBitmap(IDB_BALLOON_DIE3, RGB(255, 255, 255));

		fork1.LoadBitmap(IDB_FORK, RGB(255, 255, 255));
		fork2.LoadBitmap(IDB_FORK, RGB(255, 255, 255));
		fork3.LoadBitmap(IDB_FORK, RGB(255, 255, 255));
		fork4.LoadBitmap(IDB_FORK, RGB(255, 255, 255));
	}

	CPumpkin::CPumpkin(int x, int y) : CGhost::CGhost(x, y) {}
	CPumpkin::~CPumpkin() {}
	void CPumpkin::LoadBitmap() {
		ghost.AddBitmap(IDB_BALLOON1, RGB(255, 255, 255));
		ghost.AddBitmap(IDB_BALLOON3, RGB(255, 255, 255));
		ghost.AddBitmap(IDB_BALLOON2, RGB(255, 255, 255));
		ghost.AddBitmap(IDB_BALLOON4, RGB(255, 255, 255));
		ghost.AddBitmap(IDB_BALLOON4, RGB(255, 255, 255));
		ghost.AddBitmap(IDB_BALLOON5, RGB(255, 255, 255));

		ghost_die.AddBitmap(IDB_BALLOON_DIE1, RGB(255, 255, 255));
		ghost_die.AddBitmap(IDB_BALLOON_DIE2, RGB(255, 255, 255));
		ghost_die.AddBitmap(IDB_BALLOON_DIE3, RGB(255, 255, 255));
		ghost_die.AddBitmap(IDB_BALLOON_DIE3, RGB(255, 255, 255));

		fork1.LoadBitmap(IDB_FORK, RGB(255, 255, 255));
		fork2.LoadBitmap(IDB_FORK, RGB(255, 255, 255));
		fork3.LoadBitmap(IDB_FORK, RGB(255, 255, 255));
		fork4.LoadBitmap(IDB_FORK, RGB(255, 255, 255));
	}
}