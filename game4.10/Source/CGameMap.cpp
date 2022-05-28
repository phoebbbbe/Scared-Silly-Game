#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameMap.h"
#include "CData.h"

#define CELL 52
#define N 24
#define M 12
#define Twenty 20
#define Ten 10
#define WHITE RGB(255, 255, 255)
using namespace std;

namespace game_framework {

	/* CGameMap */
	CGameMap::CGameMap() :X(0), Y(0), MW(50), MH(60) {				// 給予地圖左上角座標以及每張小圖寬高度
		sx = 0;
		sy = 0;
	}
	
	CGameMap::~CGameMap() {}

	void CGameMap::LoadBitmap() {
		brick1.LoadBitmap(IDB_BRICK1);							// 載入地板
		brick2.LoadBitmap(IDB_BRICK3);
		piece.LoadBitmap(IDB_MAP_FINAL, WHITE);
	}

	bool CGameMap::IsEmpty(int x, int y) {
		int gx = x / 47;
		int gy = y / 50;
		return (map[gx][gy] == 1) || (map[gx][gy] == 2);
	}

	POINT CGameMap::GetPieceXY() {
		POINT p = POINT();
		p.x = 50 * 18;
		p.y = 60 * 4;
		return p;
	}

	POINT CGameMap::GetSXY() {
		POINT p = POINT();
		p.x = sx;
		p.y = sy;
		return p;
	}
	
	int *CGameMap::GetMap() {
		return map[0];
	}
	
	void CGameMap::SetSX(int x) {
		sx = x;
	}

	void CGameMap::SetSY(int y) {
		sy = y;
	}

	int CGameMap::ScreenX(int x) {
		return x - sx;
	}

	int CGameMap::ScreenY(int y) {
		return y - sy;
	}

	bool CGameMap::HasPiece(int x1, int y1, int x2, int y2) {
		int x3 = GetPieceXY().x;				// 鬼怪的左上角pos.x座標
		int y3 = GetPieceXY().y;				// 鬼怪的左上角pos.y座標
		int x4 = GetPieceXY().x + piece.Width();	// 鬼怪的右下角pos.x座標
		int y4 = GetPieceXY().y +piece.Height();	// 鬼怪的右下角pos.y座標
		TRACE("piece x = %d, y = %d\n", x3, y3);
		return (x2 >= x3 && x1 <= x4 && y2 >= y3 && y1 <= y4);
	}
	
	/* CGameMap_1 */
	CGameMap_1::CGameMap_1() : CGameMap::CGameMap()
	{
		for (int i = 0; i < 30; i++)
			for (int j = 0; j < 30; j++)
				map[i][j] = LEVEL1_MAP[i][j];
	}

	CGameMap_1::~CGameMap_1() {}

	void CGameMap_1::LoadLevelBitmap() {
		int i;
		LoadBitmap();
		turf.LoadBitmap(IDB_TURF);								// 載入草叢
		brick3.LoadBitmap(IDB_BRICK2);
		brick4.LoadBitmap(IDB_BRICK4);
		explination.LoadBitmap(IDB_EXPLINATION, WHITE);
		for (i = 0; i < Twenty; i++)
			tree[i].LoadBitmap(IDB_TREE1, WHITE);
		for (i = 0; i < Ten; i++)
			grass[i].LoadBitmap(IDB_GRASS4, WHITE);
	}

	//int CGameMap_1::GhostNearbyApu(int x1, int y1, int x2, int y2) {
	//	for (int i = 0; i < ballonNum; i++) {
	//		if (x2 >= ballon[i].GetX1() && x1 <= ballon[i].GetX2() && y2 >= ballon[i].GetY1() + 5 && y1 <= ballon[i].GetY2())
	//			if (ballon[i].IsAlive())
	//				return i;
	//			else
	//				break;
	//	}
	//	return -1;
	//}

	//void CGameMap_1::SetGhostFighted(int i, bool fighted) {
	//	ballon[i].SetIsFighted(true);
	//}
	//void CGameMap_1::OnMove(POINT apuXY1, POINT apuXY2, int apu_mode) {
	//	int i;
	//	for (i = 0; i < ballonNum; i++) {
	//		if (ballon[i].IsAlive() && ballon[i].IsFighted()) {
	//			ballon[i].SetIsAlive(false);
	//			//CAudio::Instance()->Play() // 出現打擊的聲音
	//		}
	//		if (ballon[i].IsAlive() && ballon[i].HitApu(apuXY1, apuXY2)) {
	//			APUWIN = false;
	//			GAMEOVER = true;
	//		}
	//	}
	//	for (int i = 0; i < ballonNum; i++)
	//		ballon[i].OnMove(apuXY1, apuXY2, apu_mode);
	//}

	void CGameMap_1::OnMove(){}

	void CGameMap_1::OnShow() {
		for (int i = 0; i < 30; i++) {							// 往右顯示N張圖
			for (int j = 0; j < 30; j++) {						// 往下顯示M張圖
				int x = i * 50 - sx;
				int y = j * 60 - sy;

				switch (map[i][j]) {
				case 0:
					turf.SetTopLeft(x, y);
					turf.ShowBitmap();
					break;
				case 1:
					brick1.SetTopLeft(x, y);
					brick1.ShowBitmap();
					break;
				case 2:
					brick2.SetTopLeft(x, y);
					brick2.ShowBitmap();
					break;
				case 3:
					brick3.SetTopLeft(x, y);
					brick3.ShowBitmap();
					break;
				case 4:
					brick4.SetTopLeft(x, y);
					brick4.ShowBitmap();
					break;
				default:
					ASSERT(0);
				}
			}
		}
		for (int i = 0; i < Twenty; i++) {
			tree[i].SetTopLeft(LEVEL1_TREE[i][0] - sx, LEVEL1_TREE[i][1] - sy);
			tree[i].ShowBitmap();
		}
		for (int i = 0; i < Ten; i++) {
			grass[i].SetTopLeft(LEVEL1_GRASS[i][0] - sx, LEVEL1_GRASS[i][1] - sy);
			//grass[i].ShowBitmap();
		}
		piece.SetTopLeft(50 * 18 - sx, 60 * 4 - sy);
		piece.ShowBitmap();
		explination.SetTopLeft(90 - sx, 120 - sy);
		explination.ShowBitmap();
	}


	/* CGameMap_2 */
	CGameMap_2::CGameMap_2() : CGameMap::CGameMap()
	{
		for (int i = 0; i < 30; i++)
			for (int j = 0; j < 30; j++)
				map[i][j] = LEVEL2_MAP[i][j];
	}

	CGameMap_2::~CGameMap_2() {
	}

	void CGameMap_2::LoadLevelBitmap() {
		LoadBitmap();
		brick3.LoadBitmap(IDB_BRICK2);
		brick4.LoadBitmap(IDB_BRICK4);
		turf.LoadBitmap(IDB_TURF);								// 載入草叢
		wall.LoadBitmap(IDB_WALL1);
		for (int i = 0; i < Twenty;) {
			tree[i++].LoadBitmap(IDB_TREE1, WHITE);
			tree[i++].LoadBitmap(IDB_TREE2, WHITE);
		}
		for (int i = 0; i < Twenty; i++)
			grass[i].LoadBitmap(IDB_GRASS4, WHITE);
	}

	void CGameMap_2::OnShow() {
		for (int i = 0; i < 30; i++) {							// 往右顯示N張圖
			for (int j = 0; j < 30; j++) {						// 往下顯示M張圖
				int x = i * 50 - sx;
				int y = j * 60 - sy;

				switch (map[i][j]) {
				case 0:
					turf.SetTopLeft(x, y);
					turf.ShowBitmap();
					break;
				case 1:
					brick1.SetTopLeft(x, y);
					brick1.ShowBitmap();
					break;
				case 2:
					brick2.SetTopLeft(x, y);
					brick2.ShowBitmap();
					break;
				case 3:
					brick3.SetTopLeft(x, y);
					brick3.ShowBitmap();
					break;
				case 4:
					brick4.SetTopLeft(x, y);
					brick4.ShowBitmap();
					break;
				case 5:
					wall.SetTopLeft(x, y);
					wall.ShowBitmap();
					break;
				default:
					ASSERT(0);
				}
			}
		}
		for (int i = 0; i < Twenty; i++) {
			tree[i].SetTopLeft(LEVEL2_TREE[i][0] - sx, LEVEL2_TREE[i][1] - sy);
			tree[i].ShowBitmap();
		}
		piece.SetTopLeft(50 * 18 - sx, 60 * 4 - sy);
		piece.ShowBitmap();
	}

	void CGameMap_2::OnMove() {

	}

	/* CGameMap_3 */
	CGameMap_3::CGameMap_3() : CGameMap::CGameMap()
	{
		for (int i = 0; i < 30; i++)
			for (int j = 0; j < 30; j++)
				map[i][j] = LEVEL3_MAP[i][j];
	}

	CGameMap_3::~CGameMap_3() {}

	void CGameMap_3::LoadLevelBitmap() {
		LoadBitmap();
		brick3.LoadBitmap(IDB_BRICK5);
		brick4.LoadBitmap(IDB_BRICK6);
		floor.LoadBitmap(IDB_FLOOR);								// 載入草叢
		for (int i = 0; i < Twenty;) {
			tree[i++].LoadBitmap(IDB_TREE4, WHITE);
			tree[i++].LoadBitmap(IDB_TREE3, WHITE);
			tree[i++].LoadBitmap(IDB_TREE5, WHITE);
			tree[i++].LoadBitmap(IDB_TREE3, WHITE);
		}
		//for (int i = 0; i < 10; i++)
		//	tombs[i].LoadBitmap(IDB_GRASS4, WHITE);
	}

	void CGameMap_3::OnShow() {
		for (int i = 0; i < 30; i++) {							// 往右顯示N張圖
			for (int j = 0; j < 30; j++) {						// 往下顯示M張圖
				int x = i * 50 - sx;
				int y = j * 60 - sy;

				switch (map[i][j]) {
				case 0:
					floor.SetTopLeft(x, y);
					floor.ShowBitmap();
					break;
				case 1:
					brick1.SetTopLeft(x, y);
					brick1.ShowBitmap();
					break;
				case 2:
					brick2.SetTopLeft(x, y);
					brick2.ShowBitmap();
					break;
				case 3:
					brick3.SetTopLeft(x, y);
					brick3.ShowBitmap();
					break;
				case 4:
					brick4.SetTopLeft(x, y);
					brick4.ShowBitmap();
					break;
				default:
					ASSERT(0);
				}
			}
		}
		for (int i = 0; i < Twenty; i++) {
			tree[i].SetTopLeft(LEVEL3_TREE[i][0] - sx, LEVEL3_TREE[i][1] - sy);
			tree[i].ShowBitmap();
		}
		piece.SetTopLeft(50 * 18 - sx, 60 * 4 - sy);
		piece.ShowBitmap();
	}

	void CGameMap_3::OnMove() {}
}