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

	}

	void CGhost::Initialize(int x, int y) {
		pos.x = x;
		pos.y = y;
		isAlive = true;
		isFighted = false;
		curMode = 1;
		curState = 0;
	}

	int  CGhost::GetX1() { return pos.x; }
	int  CGhost::GetY1() { return pos.y; }
	int  CGhost::GetX2() { return pos.x + ghost.Width(); }
	int  CGhost::GetY2() { return pos.y + ghost.Height(); }
	
	void CGhost::SetXY(int nx, int ny) {
		pos.x = nx; pos.y = ny;
	}
	void CGhost::SetIsAlive(bool alive) { isAlive = alive; }
	void CGhost::SetIsFighted(bool fighted) { isFighted = fighted; }
	void CGhost::SetMode(int mode) { curMode = mode; }
	void CGhost::SetState(int state) { curState = state; }
	void CGhost::SetFork() {

	}
	
	bool CGhost::IsAlive() { return isAlive; }
	bool CGhost::IsFighted() { return isFighted; }

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
	void CGhost::SwitchMode() {
		if (curMode == 1) {
			SetMode(2);
		}
		else if (curMode == 2) {
			SetMode(1);
		}
	}
	void CGhost::FollowApu(CApu *apu, int stepsize) {
		int xUp = pos.x, yUp = pos.y - stepsize;
		int xDown = pos.x, yDown = pos.y + stepsize;
		int xLeft = pos.x - stepsize, yLeft = pos.y;
		int xRight = pos.x + stepsize, yRight = pos.y;
		float disUp = (float)sqrt((double)((xUp - apu->GetX1())*(xUp - apu->GetX1()) + (yUp - apu->GetY1())*(yUp - apu->GetY1())));
		float disDown = (float)sqrt((double)((xDown - apu->GetX1())*(xDown - apu->GetX1()) + (yDown - apu->GetY1())*(yDown - apu->GetY1())));
		float disLeft = (float)sqrt((double)((xLeft - apu->GetX1())*(xLeft - apu->GetX1()) + (yLeft - apu->GetY1())*(yLeft - apu->GetY1())));
		float disRight = (float)sqrt((double)((xRight - apu->GetX1())*(xRight - apu->GetX1()) + (xRight - apu->GetY1())*(xRight - apu->GetY1())));
		if (curState == 0) {
			switch (WhereIsApu(apu)) {
			case 1:
				if (disUp <= disRight) curState = 1;
				else curState = 4;
				break;
			case 2:
				if (disUp <= disLeft) curState = 1;
				else curState = 3;
				break;
			case 3:
				if (disDown <= disLeft) curState = 2;
				else curState = 3;
				break;
			case 4:
				if (disDown <= disRight) curState = 2;
				else curState = 4;
				break;
			}
		}
		if (curState == 1)
			SetXY(xUp, yUp);
		else if (curState == 2)
			SetXY(xDown, yDown);
		else if (curState == 3)
			SetXY(xLeft, yLeft);
		else if (curState == 4)
			SetXY(xRight, yRight);
	}
	bool CGhost::HitApu(CApu *apu) {
		return HitRectangle(apu->GetX1(), apu->GetY1(), apu->GetX2(), apu->GetY2());
	}
	bool CGhost::HitRectangle(int tx1, int ty1, int tx2, int ty2) {
		int x1 = tx1;
		int y1 = ty1;
		int x2 = tx2;
		int y2 = ty2;
		int x3 = pos.x;				// 鬼怪的左上角pos.x座標
		int y3 = pos.y + 5;				// 鬼怪的左上角pos.y座標
		int x4 = pos.x + ghost.Width();	// 鬼怪的右下角pos.x座標
		int y4 = pos.y + ghost.Height();	// 鬼怪的右下角pos.y座標
		return (x2 >= x3 && x1 <= x4 && y2 >= y3 && y1 <= y4);
	}

	void CGhost::OnMove(CGameMap *map, CApu *apu) {
		const int STEP = 1;
		if (isAlive)
		{
			if (isFighted) {
				curState = 2;
				ghost_die.OnMove();
			}
			else if (HitApu(apu)) {
				apu->SetFail(true);
			}
			if (apu->GetMode() == 2) {
				TRACE("ghost is %d and the mode is %d\n", isAlive, curMode);
				if (curMode == 1)
				{
					ghost.OnMove();
				}
				else if (curMode == 2)
				{
					//FollowApu(apu, STEP_SIZE);
					// undisplay fork
				}
			}
			
			TRACE("ghost is %d and the mode is %d\n", isAlive, curMode);
		}
	}
	void CGhost::OnShow() {
		if (isAlive) {
			ghost.SetTopLeft(pos.x, pos.y);
			ghost.OnShow();
			if (curMode == 1)
			{
				//SetFork();
				/*fork1.SetTopLeft(pos.x - 30, pos.y);
				fork2.SetTopLeft(pos.x + 30, pos.y);
				fork3.SetTopLeft(pos.x, pos.y - 30);
				fork4.SetTopLeft(pos.x, pos.y + 30);
				fork1.ShowBitmap();
				fork2.ShowBitmap();
				fork3.ShowBitmap();
				fork4.ShowBitmap();*/
			}

		}
		else if (isFighted) {
			ghost_die.SetTopLeft(pos.x, pos.y);
			ghost_die.OnShow(); // 改進ghost_die的動畫
		}
	}
	void CGhost::OnShow(CGameMap *m) {
		if (isAlive) {
			switch (curState) {
				// 比照阿噗
			}
			if (curMode == 1)
			{
				ghost.SetTopLeft(m->ScreenX(pos.x), m->ScreenY(pos.y));
				ghost.OnShow();
				/*fork1.SetTopLeft(pos.x - 30, pos.y);
				fork2.SetTopLeft(pos.x + 30, pos.y);
				fork3.SetTopLeft(pos.x, pos.y - 30);
				fork4.SetTopLeft(pos.x, pos.y + 30);
				fork1.ShowBitmap();
				fork2.ShowBitmap();
				fork3.ShowBitmap();
				fork4.ShowBitmap();*/
			}
			else {
				ghost.SetTopLeft(m->ScreenX(pos.x), m->ScreenY(pos.y));
				ghost.OnShow();
			}
			if (isFighted) {
				ghost_die.SetTopLeft(m->ScreenX(pos.x), m->ScreenY(pos.y));
				ghost_die.OnShow(); // 改進ghost_die的動畫
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