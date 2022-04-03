#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CEraser::CEraser()
	{
		Initialize();
	}

	int CEraser::GetX1()
	{
		return x;
	}

	int CEraser::GetY1()
	{
		return y;
	}

	int CEraser::GetX2()
	{
		//return x + animation.Width();
		return x + bmpInitApu.Width();
	}

	int CEraser::GetY2()
	{
		//return y + animation.Height();
		return y + bmpInitApu.Height();
	}

	void CEraser::Initialize()
	{
		const int X_POS = 280;
		const int Y_POS = 280;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isFightBack = isFightFront= isFightUp = isFightDown = false;
		
	}

	void CEraser::LoadBitmap()
	{
		animation.AddBitmap(IDB_ERASER1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_ERASER3, RGB(255, 255, 255));
		animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));

		animationRunUp.AddBitmap(IDB_APU_UP1, RGB(255, 255, 255));
		animationRunUp.AddBitmap(IDB_APU_UP2, RGB(255, 255, 255));
		animationRunUp.AddBitmap(IDB_APU_UP3, RGB(255, 255, 255));
		animationRunUp.AddBitmap(IDB_APU_UP4, RGB(255, 255, 255));

		animationRunDown.AddBitmap(IDB_APU_DOWN1, RGB(255, 255, 255));
		animationRunDown.AddBitmap(IDB_APU_DOWN2, RGB(255, 255, 255));
		animationRunDown.AddBitmap(IDB_APU_DOWN3, RGB(255, 255, 255));
		animationRunDown.AddBitmap(IDB_APU_DOWN4, RGB(255, 255, 255));

		animationRunBack.AddBitmap(IDB_APU_BACK1, RGB(255, 255, 255));
		animationRunBack.AddBitmap(IDB_APU_BACK2, RGB(255, 255, 255));
		animationRunBack.AddBitmap(IDB_APU_BACK3, RGB(255, 255, 255));
		animationRunBack.AddBitmap(IDB_APU_BACK4, RGB(255, 255, 255));

		animationRunFront.AddBitmap(IDB_APU_FRONT1, RGB(255, 255, 255));
		animationRunFront.AddBitmap(IDB_APU_FRONT2, RGB(255, 255, 255));
		animationRunFront.AddBitmap(IDB_APU_FRONT3, RGB(255, 255, 255));
		animationRunFront.AddBitmap(IDB_APU_FRONT4, RGB(255, 255, 255));

		animationFightUp.AddBitmap(IDB_FIGHT_UP1, RGB(255, 255, 255));
		animationFightUp.AddBitmap(IDB_FIGHT_UP2, RGB(255, 255, 255));
		animationFightUp.AddBitmap(IDB_FIGHT_UP3, RGB(255, 255, 255));

		animationFightDown.AddBitmap(IDB_FIGHT_DOWN1, RGB(255, 255, 255));
		animationFightDown.AddBitmap(IDB_FIGHT_DOWN2, RGB(255, 255, 255));
		animationFightDown.AddBitmap(IDB_FIGHT_DOWN3, RGB(255, 255, 255));

		animationFightBack.AddBitmap(IDB_FIGHT_BACK1, RGB(255, 255, 255));
		animationFightBack.AddBitmap(IDB_FIGHT_BACK2, RGB(255, 255, 255));
		animationFightBack.AddBitmap(IDB_FIGHT_BACK3, RGB(255, 255, 255));

		animationFightFront.AddBitmap(IDB_FIGHT_FRONT1, RGB(255, 255, 255));
		animationFightFront.AddBitmap(IDB_FIGHT_FRONT2, RGB(255, 255, 255));
		animationFightFront.AddBitmap(IDB_FIGHT_FRONT3, RGB(255, 255, 255));

		bmpInitApu.LoadBitmap(IDB_APU_FRONT1, RGB(255, 255,2555));
	}

	void CEraser::OnMove()
	{
		const int STEP_SIZE = 20;
		int flag = 0;
		animation.OnMove();

		if (isMovingLeft) {
			animationRunBack.OnMove();
			curState = 3;
			x -= STEP_SIZE; 
		}
			
		if (isMovingRight) {
			animationRunFront.OnMove();
			curState = 4;
			x += STEP_SIZE;
		}
			
		if (isMovingUp) {
			animationRunUp.OnMove();
			curState = 1;
			y -= STEP_SIZE;
		}
			
		if (isMovingDown) {
			animationRunDown.OnMove();
			curState = 2;
			y += STEP_SIZE;
		}
		if (isFightUp) {
			animationFightUp.OnMove();
			curState = 5;
		}

		if (isFightDown) {
			animationFightDown.OnMove();
			curState = 6;
		}

		if (isFightBack) {
			animationFightBack.OnMove();
			curState = 7;
		}
		if (isFightFront) {
			animationFightFront.OnMove();
			curState = 8;
		}
			
	}

	void CEraser::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CEraser::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CEraser::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CEraser::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void CEraser::SetFightUp(bool flag) {
		isFightUp = flag;
	}
	void CEraser::SetFightDown(bool flag) {
		isFightDown = flag;
	}
	void CEraser::SetFightBack(bool flag) {
		isFightBack = flag;
	}
	void CEraser::SetFightFront(bool flag) {
		isFightFront = flag;
	}

	void CEraser::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CEraser::OnShow()
	{
		//animation.SetTopLeft(x, y);
		//animation.OnShow();
		switch (curState) {
		case 0:
			bmpInitApu.SetTopLeft(x, y);
			bmpInitApu.ShowBitmap();
			break;
		case 1:
			animationRunUp.SetTopLeft(x, y);
			animationRunUp.OnShow();
			break;
		case 2:
			animationRunDown.SetTopLeft(x, y);
			animationRunDown.OnShow();
			break;
		case 3:
			animationRunBack.SetTopLeft(x, y);
			animationRunBack.OnShow();
			break;
		case 4:
			animationRunFront.SetTopLeft(x, y);
			animationRunFront.OnShow();
			break;
		case 5:
			animationFightUp.SetTopLeft(x, y);
			animationFightUp.OnShow();
			break;
		case 6:
			animationFightDown.SetTopLeft(x, y);
			animationFightDown.OnShow();
			break;
		case 7:
			animationFightBack.SetTopLeft(x, y);
			animationFightBack.OnShow();
			break;
		case 8:
			animationFightFront.SetTopLeft(x, y);
			animationFightFront.OnShow();
			break;
		default:
			break;
		}

	}

}