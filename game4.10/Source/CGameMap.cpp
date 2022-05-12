#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameMap.h"
#include "CData.h"
#include "CApu.h"
#include "CGhost.h"
#define CELL 52
#define N 24
#define M 12
using namespace std;

namespace game_framework {

	CGameMap::CGameMap()
		:X(0), Y(0), MW(CELL), MH(CELL)							// 給予地圖左上角座標以及每張小圖寬高度
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				map[i][j] = LEVEL1_MAP[i][j];					// 依序填入map內
		random_num = 0;
		//bballs = NULL;
	}

	void CGameMap::LoadBitmap() {
		brick1.LoadBitmap(IDB_FLOOR1);							// 載入地板
		turf.LoadBitmap(IDB_TREE);								// 載入草叢
	}

	void CGameMap::OnShow() {
		for (int i = 0; i < N; i++)								// 往右顯示五張圖
			for (int j = 0; j < M; j++)							// 往下顯示四張圖
			{
				switch (map[i][j]) {
				case 0:
					turf.SetTopLeft(X + (MW*i), Y + (MH*j));
					turf.ShowBitmap();
					break;
				case 1:
					brick1.SetTopLeft(X + (MW*i), Y + (MH*j));	//設定每張圖的座標
					brick1.ShowBitmap();						//顯示設定完座標的圖
					break;
				case 2:
					//green.SetTopLeft(X + (MW*i), Y + (MH*j));
					//green.ShowBitmap();
					break;
				default:
					ASSERT(0); //map陣列不該出現0,1,2之外的值
				}
			}
		/*for (int i = 0; i < random_num; i++) {
			bballs[i].OnShow();
		}*/
	}

	void CGameMap::InitializeBouncingBall(int ini_index, int row, int col) {
		const int VELOCITY = 10;
		const int BALL_PIC_HEIGHT = 15;
		int brick1 = Y + (row + 1)*MH - BALL_PIC_HEIGHT;

		/*bballs[ini_index].LoadBitmap();
		bballs[ini_index].SetFloor(brick1);
		bballs[ini_index].SetVelocity(VELOCITY + col);
		bballs[ini_index].SetXY(X + col * MW + MW / 2, brick1);*/
	}
	int *CGameMap::GetMap() {
		return map[0];
	}
	void CGameMap::RandomBouncingBall() {
		const int MAX_RAND_NUM = 10;
		random_num = (rand() % MAX_RAND_NUM) + 1;

		//delete[] bballs;
		//bballs = new CBouncingBall[random_num];
		int ini_index = 0;
		for (int row = 0; row < 4; row++)
			for (int col = 0; col < 5; col++)
			{
				if (map[row][col] != 0 && ini_index < random_num)
				{
					InitializeBouncingBall(ini_index, row, col);
					ini_index++;
				}
			}
	}

	void CGameMap::OnKeyDown(UINT nChar) {
		const int KEY_SPACE = 0x20;
		if (nChar == KEY_SPACE)
			RandomBouncingBall();
	}

	void CGameMap::OnMove() {
		/*for (int i = 0; i < random_num; i++) {
			bballs[i].OnMove();
		}*/
	}

	CGameMap::~CGameMap()
	{
		//delete[] bballs;
	}
}