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
		CMovingBitmap brick3;	// �T�ئa�j
		CMovingBitmap turf;						// ���
		int map[24][12];						// �a��
		int sx, sy;								// �ù����W���y��
		const int X, Y;							// �b�a�ϤW���y��
		const int MW, MH;						// �C�j���e�j�p
		//CBouncingBall* bballs;
		int random_num;
	};
}

#endif