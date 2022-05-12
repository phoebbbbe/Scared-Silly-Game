#ifndef CGAMEMAP_H
#define CGAMEMAP_H
#include "CBouncingBall.h"

namespace game_framework {

	/* Map : 1248*624  (24*12)
	Screen : 676*364 (13*7)
	cell : 52*52 */

	class CGameMap {
	public:
		/* Constructor */
		CGameMap();
		~CGameMap();

		/* Getter */
		int *GetMap();

		/* Member Function */
		void OnKeyDown(UINT);
		void RandomBouncingBall();
		void InitializeBouncingBall(int, int, int);

		//
		void LoadBitmap();
		void OnShow();
		void OnMove();

	protected:
		CMovingBitmap brick1;
		CMovingBitmap brick2;
		CMovingBitmap brick3;	// 三種地磚
		CMovingBitmap turf;						// 草皮
		int map[24][12];						// 地圖
		int sx, sy;								// 螢幕左上角座標
		const int X, Y;							// 在地圖上的座標
		const int MW, MH;						// 每隔長寬大小
		//CBouncingBall* bballs;
		int random_num;
	};
}

#endif