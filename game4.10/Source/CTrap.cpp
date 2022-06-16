#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CApu.h"
#include "CTrap.h"
#include "mygame.h"
#define WHITE RGB(255, 255, 255)

namespace game_framework {
	
	CTrap::CTrap(int x, int y) {
		Initialize(x, y);
	}
	CTrap::~CTrap() {}
	void CTrap::Initialize(int x, int y) {
		pos.x = x;
		pos.y = y;
		switchState = true;
		curMode = 1;
		curState = 1;
		counter = 30;
	}
	int  CTrap::GetX1() { return pos.x; }
	int  CTrap::GetY1() { return pos.y; }

	int  CTrap::GetCurAnimationNum() {
		switch (curState) {
		case 1: return trap_up.GetCurrentBitmapNumber();
		case 2: return trap_down.GetCurrentBitmapNumber();
		default: return 0;
		}
	}
	int CTrap::GetCurAnimationLastNum() {
		switch (curState) {
		case 1: return trap_up.GetLastBitmapNumber();
		case 2: return trap_down.GetLastBitmapNumber();
		default: return 0;
		}
	}
	void CTrap::ResetCurAnimation() {
		if (curState == 1) trap_up.Reset();
		else if (curState == 2) trap_down.Reset();
	}

	void CTrap::SetXY(int nx, int ny) {
		pos.x = nx; pos.y = ny;
	}
	void CTrap::SetMode(int mode) { curMode = mode; }
	void CTrap::SetState(int state) { curState = state; }

	void CTrap::SwitchState() {};

	CClaw::CClaw(int x, int y) : CTrap::CTrap(x, y) {
		pos_show.x = pos.x;
		pos_show.y = pos.y - 50;
	}
	CClaw::~CClaw() {}

	void CClaw::LoadBitmap() {
		trap_up.AddBitmap(IDB_CLAW1, WHITE);
		trap_up.AddBitmap(IDB_CLAW2, WHITE);
		trap_up.AddBitmap(IDB_CLAW3, WHITE);
		trap_up.AddBitmap(IDB_CLAW4, WHITE);
		trap_up.AddBitmap(IDB_CLAW5, WHITE);
		trap_up.AddBitmap(IDB_CLAW6, WHITE);
		trap_up.AddBitmap(IDB_CLAW7, WHITE);

		trap_down.AddBitmap(IDB_CLAW7, WHITE);
		trap_down.AddBitmap(IDB_CLAW6, WHITE);
		trap_down.AddBitmap(IDB_CLAW5, WHITE);
		trap_down.AddBitmap(IDB_CLAW4, WHITE);
		trap_down.AddBitmap(IDB_CLAW3, WHITE);
		trap_down.AddBitmap(IDB_CLAW2, WHITE);
		trap_down.AddBitmap(IDB_CLAW1, WHITE);
	}

	/*void CClaw::OnMove(CGameMap *map, CApu *apu) {};
	void CClaw::OnShow(CGameMap *map) {};*/

	CSpike::CSpike(int x, int y) : CTrap::CTrap(x, y) {
		pos_show.x = pos.x;
		pos_show.y = pos.y - 50;
	}
	CSpike::~CSpike() {}

	void CSpike::LoadBitmap() {
		trap_up.AddBitmap(IDB_SPIKE1, WHITE);
		trap_up.AddBitmap(IDB_SPIKE2, WHITE);
		trap_up.AddBitmap(IDB_SPIKE3, WHITE);
		trap_up.AddBitmap(IDB_SPIKE4, WHITE);
		trap_up.AddBitmap(IDB_SPIKE5, WHITE);
		trap_up.AddBitmap(IDB_SPIKE6, WHITE);

		trap_down.AddBitmap(IDB_SPIKE6, WHITE);
		trap_down.AddBitmap(IDB_SPIKE5, WHITE);
		trap_down.AddBitmap(IDB_SPIKE4, WHITE);
		trap_down.AddBitmap(IDB_SPIKE3, WHITE);
		trap_down.AddBitmap(IDB_SPIKE2, WHITE);
		trap_down.AddBitmap(IDB_SPIKE1, WHITE);
	}

	/*void CSpike::OnMove(CGameMap *map, CApu *apu) {};
	void CSpike::OnShow(CGameMap *map) {};*/

	CBouncingBrick::CBouncingBrick(int x, int y) : CTrap::CTrap(x, y) {
		pos_show.x = pos.x;
		pos_show.y = pos.y - 50;
	}
	CBouncingBrick::~CBouncingBrick() {}

	void CBouncingBrick::LoadBitmap() {
		/*trap_up.AddBitmap(IDB_SPIKE1, WHITE);
		trap_up.AddBitmap(IDB_SPIKE2, WHITE);
		trap_up.AddBitmap(IDB_SPIKE3, WHITE);
		trap_up.AddBitmap(IDB_SPIKE4, WHITE);
		trap_up.AddBitmap(IDB_SPIKE5, WHITE);
		trap_up.AddBitmap(IDB_SPIKE6, WHITE);

		trap_down.AddBitmap(IDB_SPIKE6, WHITE);
		trap_down.AddBitmap(IDB_SPIKE5, WHITE);
		trap_down.AddBitmap(IDB_SPIKE4, WHITE);
		trap_down.AddBitmap(IDB_SPIKE3, WHITE);
		trap_down.AddBitmap(IDB_SPIKE2, WHITE);
		trap_down.AddBitmap(IDB_SPIKE1, WHITE);*/
	}

	/*void CBouncingBrick::OnMove(CGameMap *map, CApu *apu) {};
	void CBouncingBrick::OnShow(CGameMap *map) {};*/
}
