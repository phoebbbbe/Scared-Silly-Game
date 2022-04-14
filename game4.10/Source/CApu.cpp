#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CApu.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CApu: Apu class
	/////////////////////////////////////////////////////////////////////////////

	CApu::CApu()
	{
		Initialize();
	}

	int CApu::GetX1()
	{
		return x;
	}

	int CApu::GetY1()
	{
		return y;
	}

	int CApu::GetX2()
	{
		return x + initApu.Width();
	}

	int CApu::GetY2()
	{
		return y + initApu.Height();
	}

	void CApu::Initialize()
	{
		const int X_POS = 0;
		const int Y_POS = 180;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isFightLeft = isFightRight = isFightUp = isFightDown = false;

	}

	void CApu::LoadBitmap()
	{

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

		//fightUp.AddBitmap(IDB_FIGHT_UP1, RGB(255, 255, 255));
		fightUp.AddBitmap(IDB_FIGHT_UP2, RGB(255, 255, 255));
		//fightUp.AddBitmap(IDB_FIGHT_UP3, RGB(255, 255, 255));

		//fightDown.AddBitmap(IDB_FIGHT_DOWN1, RGB(255, 255, 255));
		fightDown.AddBitmap(IDB_FIGHT_DOWN2, RGB(255, 255, 255));
		//fightDown.AddBitmap(IDB_FIGHT_DOWN3, RGB(255, 255, 255));

		//fightLeft.AddBitmap(IDB_FIGHT_BACK1, RGB(255, 255, 255));
		fightLeft.AddBitmap(IDB_FIGHT_BACK2, RGB(255, 255, 255));
		//fightLeft.AddBitmap(IDB_FIGHT_BACK3, RGB(255, 255, 255));

		//fightRight.AddBitmap(IDB_FIGHT_FRONT1, RGB(255, 255, 255));
		fightRight.AddBitmap(IDB_FIGHT_FRONT2, RGB(255, 255, 255));
		//fightRight.AddBitmap(IDB_FIGHT_FRONT3, RGB(255, 255, 255));

		initApu.LoadBitmap(IDB_APU_FRONT1, RGB(255, 255, 2555));
	}

	void CApu::OnMove()
	{
		const int STEP_SIZE = 20;
		int flag = 0;

		if (isMovingLeft) {
			moveLeft.OnMove();
			curState = 3;
			x -= STEP_SIZE;
		}

		if (isMovingRight) {
			moveRight.OnMove();
			curState = 4;
			x += STEP_SIZE;
		}

		if (isMovingUp) {
			moveUp.OnMove();
			curState = 1;
			y -= STEP_SIZE;
		}

		if (isMovingDown) {
			moveDown.OnMove();
			curState = 2;
			y += STEP_SIZE;
		}
		if (isFightUp) {
			fightUp.OnMove();
			curState = 5;
		}

		if (isFightDown) {
			fightDown.OnMove();
			curState = 6;
		}

		if (isFightLeft) {
			fightLeft.OnMove();
			curState = 7;
		}
		if (isFightRight) {
			fightRight.OnMove();
			curState = 8;
		}

	}

	void CApu::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CApu::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CApu::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CApu::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void CApu::SetFightUp(bool flag) {
		isFightUp = flag;
	}
	void CApu::SetFightDown(bool flag) {
		isFightDown = flag;
	}
	void CApu::SetFightLeft(bool flag) {
		isFightLeft = flag;
	}
	void CApu::SetFightRight(bool flag) {
		isFightRight = flag;
	}

	void CApu::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CApu::OnShow()
	{
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
		default:
			break;
		}

	}

}