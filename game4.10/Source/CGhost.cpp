#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CApu.h"
#include "CGhost.h"

namespace game_framework {

	CGhost::CGhost()
	{
		is_alive = true;
		is_fighted = false;
		is_apu_move = false;
		x = y = dx = dy = index = delay_counter = 0;
	}

	bool CGhost::HitApu(CApu *apu)
	{
		// 檢測阿噗所構成的矩形是否碰到鬼怪
		return HitRectangle(apu->GetX1(), apu->GetY1(), apu->GetX2(), apu->GetY2());
	}

	bool CGhost::HitRectangle(int tx1, int ty1, int tx2, int ty2)
	{
		int x1 = x + dx;				// 鬼怪的左上角x座標
		int y1 = y + dy;				// 鬼怪的左上角y座標
		int x2 = x1 + ghost.Width();	// 鬼怪的右下角x座標
		int y2 = y1 + ghost.Height();	// 鬼怪的右下角y座標

		// 檢測鬼怪的矩形與參數矩形是否有交集
		return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	}

	bool CGhost::IsAlive()
	{
		return is_alive;
	}

	bool CGhost::IsFighted() {
		return is_fighted;
	}

	bool CGhost::IsApuMove() {
		return is_apu_move;
	}
	void CGhost::LoadBitmap()
	{
		ghost.AddBitmap(IDB_GHOST1, RGB(255, 255, 255));
		ghost.AddBitmap(IDB_GHOST1_2, RGB(255, 255, 255));

	}

	void CGhost::OnMove()
	{
		ghost.OnMove();
		if (!is_alive)
			return;
		
		delay_counter--;
		if (delay_counter < 0) {
			delay_counter = delay;

			// 計算球向對於圓心的位移量dx, dy
			const int STEPS = 18;
			static const int DIFFX[] = { 35, 32, 26, 17, 6, -6, -17, -26, -32, -34, -32, -26, -17, -6, 6, 17, 26, 32, };
			static const int DIFFY[] = { 0, 11, 22, 30, 34, 34, 30, 22, 11, 0, -11, -22, -30, -34, -34, -30, -22, -11, };
			index++;
			if (index >= STEPS)
				index = 0;
			//dx = DIFFX[index];
			//dy = DIFFY[index];
		}
	}
	void CGhost::OnMove(CApu *apu) {
		ghost.OnMove();
		if (!is_alive)
			return;
		if (is_apu_move) {
			if (mode == 1) {
				SetMode(2);
			}
			else {

				SetMode(1);
			}
		}
	}

	int CGhost::WhereIsApu(CApu *apu) {
		int X1 = GetX(), Y2 = GetY();
		int X2 = apu->GetX1(), Y1 = apu->GetY1();
		float dis = (float)sqrt((double)((X2 - X1)*(X2 - X1) + (Y2 - Y1)*(Y2 - Y1)));
		if (dis < 0.001)
		{
			return 0;
		}

		X2 -= X1;
		Y2 -= Y1;
		if (X2 > 0 && Y2 < 0)
			return 1;
		else if (X2 < 0 && Y2 < 0)
			return 2;
		else if (X2 < 0 && Y2 >0)
			return 3;
		else if (X2 > 0 && Y2 > 0)
			return 4;
		else
			return 0;
	}

	void CGhost::SetDelay(int d)
	{
		delay = d;
	}

	void CGhost::SetIsAlive(bool alive)
	{
		is_alive = alive;
	}

	void CGhost::SetIsFighted(bool fighted) {
		is_fighted = fighted;
	}

	void CGhost::SetIsApuMove(bool apu_move) {
		is_apu_move = apu_move;
	}
	void CGhost::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CGhost::SetMode(int m) {
		mode = m;
	}
	int CGhost::GetX() {
		return x;
	}

	int CGhost::GetY() {
		return y;
	}

	void CGhost::OnShow()
	{
		if (is_alive) {
			ghost.SetTopLeft(x + dx, y + dy);
			ghost.OnShow();
		}
	}
}