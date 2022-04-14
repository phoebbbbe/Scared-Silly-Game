#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"
#include "CApu.h"
#include "CGhost.h"
#ifndef CGAMEMAP_H
#define CGAMEMAP_H

namespace game_framework {

	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供地圖的構成
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	class CGameMap {
	public:
		CGameMap();
		void LoadBitmap();
		void OnShow();
		void OnMove();
		void OnKeyDown(UINT);
		void RandomBouncingBall();
		void InitializeBouncingBall(int, int, int);
		~CGameMap();
	protected:
		CMovingBitmap floor, grass;
		int map[14][10];
		const int X, Y;
		const int MW, MH;
		CBouncingBall* bballs;
		int random_num;
	};
}

#endif