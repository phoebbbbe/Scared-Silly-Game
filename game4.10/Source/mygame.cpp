#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include <iostream>

#define WHITE RGB(255, 255, 255)
using namespace std;

namespace game_framework {

/* 這個class為遊戲的遊戲開頭畫面物件*/

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g){}

void CGameStateInit::OnInit() {
	/* 當圖很多時，OnInit載入所有的圖要花很多時間。
	為避免玩遊戲的人等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	 一開始的loading進度為0% */
	ShowInitProgress(0);	

	/* Begin Page */
	page_begin.AddBitmap(IDB_BEGIN_PAGE1);
	page_begin.AddBitmap(IDB_BEGIN_PAGE2);
	button_begin.AddBitmap(IDB_BUTTON_BEGIN1, WHITE);
	button_begin.AddBitmap(IDB_BUTTON_BEGIN2, WHITE);
	
	/* Level Page */
	page_level.LoadBitmap(IDB_LEVEL_PAGE, WHITE);
	levels[0].LoadBitmap(IDB_LEVEL1, WHITE);
	levels[1].LoadBitmap(IDB_LEVEL2, WHITE);
	levels[2].LoadBitmap(IDB_LEVEL3, WHITE);

	isBeginButtonDown = false;
	beginButtonHasDown = false;
	curPage = 1;
	curLevel = 0;
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep

	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
}

void CGameStateInit::OnBeginState() {}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE) {
		CGame::Instance()->SetLevel(curLevel);
		GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
	}
	else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// 關閉遊戲
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point) {
	int x1 = point.x, y1 = point.y;
	int x2, y2, x3, y3;
	if (curPage == 1) {									// 處於BeginPage
		x2 = button_begin.Left();							// button左上角x
		y2 = button_begin.Top();							// button左上角y
		x3 = x2 + button_begin.Width();						// button右下角x
		y3 = x2 + button_begin.Height();					// button右下角y
		if (x1 >= x2 && x1 <= x3 && y1 >= y2 && y1 <= y3) {
			//GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
			isBeginButtonDown = true;
			beginButtonHasDown = true;
		}
	}
	else if (curPage == 2) {								// 處於LevelPage
		for (int i = 0; i < 3; i++) {
			x2 = levels[i].Left();
			y2 = levels[i].Top();
			x3 = x2 + levels[i].Width();
			y3 = y2 + levels[i].Height();
			if (x1 >= x2 && x1 <= x3 && y1 >= y2 && y1 <= y3) 
				curLevel = i+1;
		}
	}
}

void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point) {
	if (curPage == 1) {
		if (isBeginButtonDown) {
			curPage = 2;
			isBeginButtonDown = false;
			beginButtonHasDown = false;
		}
	}
	else if (curPage == 2) {
		CGame::Instance()->SetLevel(curLevel);
		GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
	}
}

void CGameStateInit::OnShow()
{
	if (curPage == 1) {
		//page_begin.SetTopLeft((SIZE_X - page_begin.Width())/2, SIZE_Y/8);
		page_begin.SetTopLeft(0,0);
		page_begin.OnShow();
		button_begin.SetTopLeft(590, 260);
		button_begin.OnShow();
	}
	else if (curPage == 2) {
		page_level.SetTopLeft(0, 0);
		page_level.ShowBitmap();
		levels[0].SetTopLeft(73, 98);
		levels[1].SetTopLeft(73, 218);
		levels[2].SetTopLeft(159, 218);
		levels[0].ShowBitmap();
		levels[1].ShowBitmap();
		levels[2].ShowBitmap();

	}

	// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
	//CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	//CFont f,*fp;
	//f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	//fp=pDC->SelectObject(&f);					// 選用 font f
	//pDC->SetBkColor(RGB(0,0,0));
	//pDC->SetTextColor(RGB(255,255,0));
	//pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	//pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	//if (ENABLE_GAME_PAUSE)
	//	pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	//pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	//pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	//CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}								

void CGameStateInit::OnMove() {
	page_begin.OnMove();
	if (isBeginButtonDown && !(beginButtonHasDown)) {
		button_begin.OnMove();
		beginButtonHasDown = true;
		isBeginButtonDown = false;
	}
	
}

/* 這個class為遊戲的結束狀態(Game Over)*/

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	//apu.OnMove();
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit()
{
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%

	// 開始載入資料
	//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep

	// 最終進度為100%
	ShowInitProgress(100);
	//apu.LoadBitmap();
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo 數字對字串的轉換
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	
	/* Apu relive animation */
	/*apu.SetMode(1);
	apu.SetState(11);
	apu.OnShow();*/


}

/* 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡 */

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g), NUMBALLONS(0){
	ballon = new CGhost[NUMBALLONS];
	curLevel = CGame::Instance()->GetLevel();
}

CGameStateRun::~CGameStateRun() {
	delete[] ballon;
}

void CGameStateRun::OnBeginState() {
	//const int BALL_GAP = 90;
	//const int BALL_XY_OFFSET = 45;
	//const int BALL_PER_ROW = 7;
	//const int HITS_LEFT = 10;
	//const int HITS_LEFT_X = 590;
	//const int HITS_LEFT_Y = 0;
	//const int BACKGROUND_X = 60;
	//const int ANIMATION_SPEED = 15;
	counter = 30 * 1;									// 5 seconds
	curLevel = CGame::Instance()->GetLevel();
	switch (curLevel) {
	case 1:
		gamemap = new CGameMap_1();
		break;
	case 2:
		gamemap = new CGameMap_2();
		break;
	case 3:
		gamemap = new CGameMap_3();
		break;
	default:
		gamemap = new CGameMap_1();
		break;
	}
	gamemap->LoadLevelBitmap();

	/*for (int i = 0; i < NUMBALLS; i++) {				// 設定球的起始座標
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		ball[i].SetXY(x_pos, y_pos);
		ball[i].SetDelay(x_pos);
		ball[i].SetIsAlive(true);
	}*/

	for (int i = 0; i < NUMBALLONS; i++) {				// 設定ballon的起始座標
		int x_pos = 700; // 715,725
		int y_pos = 200;
		ballon[i].SetXY(x_pos,y_pos);
		ballon[i].SetIsAlive(true);
	}

	apu.Initialize();

	/*
	background.SetTopLeft(BACKGROUND_X,0);				// 設定背景的起始座標
	help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
	hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// 指定剩下撞擊數的座標
	CAudio::Instance()->Play(AUDIO_LAKE, true);			// 撥放 WAVE
	CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// 撥放 MIDI
	*/
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%

	// 開始載入資料
	int i;
	for (i = 0; i < NUMBALLONS; i++)
		ballon[i].LoadBitmap();								// 載入第i個ballon的圖形
	apu.LoadBitmap();
	background.LoadBitmap(IDB_BACKGROUND);					// 載入背景的圖形

	// 完成部分Loading動作，提高進度
	ShowInitProgress(50);
	Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep

	// 繼續載入其他資料
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// 載入說明的圖形
	corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
	corner.ShowBitmap(background);							// 將corner貼到background
	hits_left.LoadBitmap();									
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// 載入編號2的聲音ntut.mid

	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
	gamemap = nullptr;

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int apuX1 = apu.GetX1();
	int apuY1 = apu.GetY1();
	int apuX2 = apu.GetX2();
	int apuY2 = apu.GetY2();
	int exist = 0;
	int RANGE = 25;

	const char KEY_LEFT = 0x25; // keyboard左箭頭
	const char KEY_UP = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN = 0x28; // keyboard下箭頭
	if (apu.GetMode() == 1) apu.SetMode(2);
	else return;

	if (nChar == KEY_UP) {
		curKeyState = 1;
		exist = TheGhostNearbyApu(apuX1, apuY1-RANGE, apuX2, apuY2-RANGE);
		if (exist != -1) {
			apu.SetFightUp(true);
			ballon[exist].SetIsFighted(true);
		}
		else {
			apu.SetMovingUp(true);
		}
	}
	if (nChar == KEY_DOWN) {
		curKeyState = 2;
		exist = TheGhostNearbyApu(apuX1, apuY1+RANGE, apuX2, apuY2+RANGE);
		if (exist != -1) {
			apu.SetFightDown(true);
			ballon[exist].SetIsFighted(true);
		}
		else {
			apu.SetMovingDown(true);
		}
	}
	if (nChar == KEY_LEFT) {
		curKeyState = 3;
		exist = TheGhostNearbyApu(apuX1-RANGE, apuY1, apuX2-RANGE, apuY2);
		if (exist != -1) {
			apu.SetFightLeft(true);
			ballon[exist].SetIsFighted(true);
		}
		else {
			apu.SetMovingLeft(true);
		}
	}
	if (nChar == KEY_RIGHT) {
		curKeyState = 4;
		exist = TheGhostNearbyApu(apuX1+RANGE, apuY1, apuX2+RANGE, apuY2);
		if (exist != -1) {
			apu.SetFightRight(true);
			ballon[exist].SetIsFighted(true);
		}
		else {
			apu.SetMovingRight(true);
		}
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	apu.SetMovingLeft(true);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	apu.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	apu.SetMovingRight(true);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	apu.SetMovingRight(false);
}

int CGameStateRun::TheGhostNearbyApu(int x1, int y1, int x2, int y2) {
	for (int i = 0; i < NUMBALLONS; i++) {
		if (x2 >= ballon[i].GetX1() && x1 <= ballon[i].GetX2() && y2 >= ballon[i].GetY1() && y1 <= ballon[i].GetY2())
			if (ballon[i].IsAlive()) return i;
			else break;
	}
	return -1;
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));

	/* 移動背景圖的座標 */
	if (background.Top() > SIZE_Y)
		background.SetTopLeft(60, -background.Height());
	background.SetTopLeft(background.Left(), background.Top() + 1);

	/* 移動氣球鬼 */
	//for (int i = 0; i < NUMBALLONS; i++)
	//{
	//	ballon[i].OnMove(&apu);
	//	ballon[i].OnMove(&apu);
	//	ballon[i].OnMove(&apu);
	//	// 比照阿噗
	//}

	/* 移動阿噗 */
	for (int i = 0; i < 4; i++)
		apu.OnMove(gamemap);
	if (apu.GetCurAnimationNum() == apu.GetCurAnimationLastNum()) {
		apu.ResetCurAnimation();
		apu.SetMode(1);
		apu.SetAllAction(false);
		for (int i = 0; i < NUMBALLONS; i++)
		{
			ballon[i].SwitchMode();
			ballon[i].SetState(0);
		}
	}
	if (apu.IsSucceed()) {
		apu.OnMove();
		counter--;
		if (counter < 0)
			GotoGameState(GAME_STATE_OVER);
	}
	//apu.Moving(gamemap.GetMap());
	// 判斷擦子是否碰到球
	//for (i = 0; i < NUMBALLS; i++) {
	//	//if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
	//	if (ball[i].IsAlive() && ball[i].IsFighted()) {
	//		ball[i].SetIsAlive(false);
	//		CAudio::Instance()->Play(AUDIO_DING);
	//		hits_left.Add(-1); // 生命值
	//		// 若剩餘碰撞次數為0，則跳到Game Over狀態
	//		if (hits_left.GetInteger() <= 0) {
	//			CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
	//			CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
	//			GotoGameState(GAME_STATE_OVER);
	//		}
	//	}
	//}

	//判斷Apu是否fight Ghost
	for (int i = 0; i < NUMBALLONS; i++) {
		if (ballon[i].IsAlive() && ballon[i].IsFighted()) {
			ballon[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);

			// 若剩餘碰撞次數為0，則跳到Game Over狀態
			//if (hits_left.GetInteger() <= 0) {
			//	CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
			//	CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
			//}
		}
		// 判斷當Ghost碰到Apu，則跳到Game Over狀態
		if (ballon[i].IsAlive() && ballon[i].HitApu(&apu))
		{
			apu.SetMode(1);
			apu.SetState(9);
			apu.OnMove();
			counter--;
			if (counter < 0)
				GotoGameState(GAME_STATE_OVER);
		}
	}



}

void CGameStateRun::OnShow()
{	
	gamemap->OnShow();					//貼上練習的地圖
	apu.OnShow(gamemap);

	hits_left.ShowBitmap();
	/*for (int i = 0; i < NUMBALLONS; i++)
		ballon[i].OnShow(&gamemap1);*/

	CDC *pDC = CDDraw::GetBackCDC();
	CFont f, *fp;
	fp = pDC->SelectObject(&f);
	pDC->SetBkColor(RGB(0, 0, 0));
	pDC->SetTextColor(RGB(255, 255, 0));
	if (apu.GetCurAnimationNum() == 0)
		pDC->TextOut(5, 355, "0");
	else if (apu.GetCurAnimationNum() == 1)
		pDC->TextOut(5, 355, "1");
	else if (apu.GetCurAnimationNum() == 2)
		pDC->TextOut(5, 355, "2");
	else if (apu.GetCurAnimationNum() == 3)
		pDC->TextOut(5, 355, "3");
	else if (apu.GetCurAnimationNum() == 4)
		pDC->TextOut(5, 355, "4");
	else
		pDC->TextOutA(5, 355, "Null");

	if (apu.GetCurAnimationLastNum() == 0)
		pDC->TextOut(5, 395, "last is : 0");
	else if (apu.GetCurAnimationLastNum() == 1)
		pDC->TextOut(5, 395, "last is : 1");
	else if (apu.GetCurAnimationLastNum() == 2)
		pDC->TextOut(5, 395, "last is : 2");
	else if (apu.GetCurAnimationLastNum() == 3)
		pDC->TextOut(5, 395, "last is : 3");
	else if (apu.GetCurAnimationLastNum() == 4)
		pDC->TextOut(5, 395, "last is : 4");
	else
		pDC->TextOut(5, 395, "last is : Null");
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

}


