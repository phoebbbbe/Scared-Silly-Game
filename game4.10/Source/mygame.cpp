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
	page_aboutus.LoadBitmap(IDB_ABOUT_PAGE);
	page_explain.LoadBitmap(IDB_EXPLAIN_PAGE);
	button_begin.AddBitmap(IDB_BUTTON_BEGIN1, WHITE);
	button_begin.AddBitmap(IDB_BUTTON_BEGIN2, WHITE);
	button_aboutus.LoadBitmap(IDB_BUTTON_ABOUTUS, WHITE);
	button_explain.LoadBitmap(IDB_BUTTON_EXPLAIN, WHITE);
	button_back.LoadBitmap(IDB_BUTTON_BACK);
	
	/* Level Page */
	page_level.LoadBitmap(IDB_LEVEL_PAGE, WHITE);
	levels[0].LoadBitmap(IDB_LEVEL1, WHITE);
	levels[1].LoadBitmap(IDB_LEVEL2, WHITE);
	levels[2].LoadBitmap(IDB_LEVEL3, WHITE);

	isBeginButtonDown = false;
	beginButtonHasDown = false;
	isAboutusButtonDown = false;
	isExplainButtonDown = false;
	isBackButtonDown = false;
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
	int x4, y4, x5, y5; // about
	int x6, y6, x7, y7; // explain
	// add music button
	if (curPage == 1) {									// 處於BeginPage
		x2 = button_begin.Left();							// button左上角x
		y2 = button_begin.Top();							// button左上角y
		x3 = x2 + button_begin.Width();						// button右下角x
		y3 = x2 + button_begin.Height();					// button右下角y
		x4 = button_aboutus.Left();
		y4 = button_aboutus.Top();
		x5 = x4 + button_aboutus.Width();
		y5 = y4 + button_aboutus.Height();
		x6 = button_explain.Left();
		y6 = button_explain.Top();
		x7 = x6 + button_explain.Width();
		y7 = y6 + button_explain.Height();
		if (x1 >= x2 && x1 <= x3 && y1 >= y2 && y1 <= y3) {
			isBeginButtonDown = true;
			beginButtonHasDown = true;
		}
		else if (x1 >= x4 && x1 <= x5 && y1 >= y4 && y1 <= y5) {
			isAboutusButtonDown = true;
		}
		else if (x1 >= x6 && x1 <= x7 && y1 >= y6 && y1 <= y7) {
			isExplainButtonDown = true;
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
	else if (curPage == 3 || curPage == 4) {							// AboutPage
		x2 = button_back.Left();
		y2 = button_back.Top();
		x3 = x2 + button_back.Width();
		y3 = y2 + button_back.Height();
		if (x1 >= x2 && x1 <= x3 && y1 >= y2 && y1 <= y3) {
			isBackButtonDown = true;
		}
	}

}

void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point) {
	if (curPage == 1) {
		if (isBeginButtonDown) {
			CAudio::Instance()->Play(AUDIO_BUTTON);
			Sleep(500);
			curPage = 2;
			isBeginButtonDown = false;
			beginButtonHasDown = false;
		}
		if (isAboutusButtonDown) {
			CAudio::Instance()->Play(AUDIO_BUTTON);
			curPage = 3;
			isAboutusButtonDown = false;
		}
		if (isExplainButtonDown) {
			CAudio::Instance()->Play(AUDIO_BUTTON);
			curPage = 4;
			isExplainButtonDown = false;
		}
	}
	else if (curPage == 2) {
		CAudio::Instance()->Play(AUDIO_BUTTON);
		Sleep(500);
		CGame::Instance()->SetLevel(curLevel);
		GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
	}
	else if (curPage == 3) {
		if (isBackButtonDown) {
			CAudio::Instance()->Play(AUDIO_BUTTON);
			curPage = 1;
			isBackButtonDown = false;
		}
	}
	else if (curPage == 4) {
		if (isBackButtonDown) {
			CAudio::Instance()->Play(AUDIO_BUTTON);
			curPage = 1;
			isBackButtonDown = false;
		}
	}
}

void CGameStateInit::OnShow()
{
	if (curPage == 1) {
		//page_begin.SetTopLeft((SIZE_X - page_begin.Width())/2, SIZE_Y/8);
		page_begin.SetTopLeft(0,0);
		page_begin.OnShow();
		button_aboutus.SetTopLeft(590, 30);
		button_aboutus.ShowBitmap();
		button_explain.SetTopLeft(590, 150);
		button_explain.ShowBitmap();
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
	else if (curPage == 3) {
		page_aboutus.SetTopLeft(0, 80);
		page_aboutus.ShowBitmap();
		button_back.SetTopLeft(20, 400);
		button_back.ShowBitmap();
	}
	else if (curPage == 4) {
		page_explain.SetTopLeft(20, 30);
		page_explain.ShowBitmap();
		button_back.SetTopLeft(20, 420);
		button_back.ShowBitmap();
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
		button_begin.OnMove();
		beginButtonHasDown = true;
		isBeginButtonDown = false;
	}
	
}

/* 這個class為遊戲的結束狀態(Game Over)*/

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
	curLevel = CGame::Instance()->GetLevel();
	curState = CGame::Instance()->GetFinish(curLevel);
}

void CGameStateOver::OnBeginState()
{
	counter = 45; // 1.5 seconds
	curLevel = CGame::Instance()->GetLevel();
	curState = CGame::Instance()->GetFinish(curLevel);
	apu_curMode = 2;

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

	apu_relive.AddBitmap(IDB_APU_RELIVE1, WHITE);
	apu_relive.AddBitmap(IDB_APU_RELIVE2, WHITE);
	apu_relive.AddBitmap(IDB_APU_RELIVE3, WHITE);
	apu_relive.AddBitmap(IDB_APU_RELIVE4, WHITE);
	apu_relive.AddBitmap(IDB_APU_RELIVE5, WHITE);
	apu_relive.AddBitmap(IDB_APU_RELIVE5, WHITE);
}

void CGameStateOver::OnMove()
{
	if (curState) {
		;
	}
	else {
		if (apu_relive.GetCurrentBitmapNumber() == apu_relive.GetLastBitmapNumber()) {
			apu_curMode = 1;
		}
		if (apu_curMode == 2) {
			apu_relive.OnMove();
			apu_relive.OnMove();
		}
	}

	counter--;
	if (counter < 0) {
		apu_curMode = 2;
		apu_relive.Reset();
		GotoGameState(GAME_STATE_INIT);
	}
}

void CGameStateOver::OnShow()
{
	if (curState)
	{
		CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo 數字對字串的轉換
		sprintf(str, "Apu Succeed!");
		pDC->TextOut(240, 210, str);
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
	else {
		POINT pos = CGame::Instance()->GetApuXY();
		apu_relive.SetTopLeft(pos.x, pos.y);
		apu_relive.OnShow();
	}


}

/* 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡 */

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g) {
	curLevel = CGame::Instance()->GetLevel();
}

CGameStateRun::~CGameStateRun() {
	delete gamemap;
	delete apu;
	ghost.clear();
}

void CGameStateRun::OnBeginState() {
	GHOSTNUM = 1;
	overCounter = 30 * 1;									// 5 seconds
	curLevel = CGame::Instance()->GetLevel();

	ghost.clear();
	switch (curLevel) {
	case 1:
		apu = new CApu(130, 260);
		gamemap = new CGameMap_1();
		for (int i = 0; i < GHOSTNUM; i++) {
			AddGhost(1, 715, 260);
		}
		break;
	case 2:
		apu = new CApu(150, 200);
		gamemap = new CGameMap_2();
		for (int i = 0; i < GHOSTNUM; i++) {
			AddGhost(1, 120 * (i + 1), 100);
			AddGhost(2, 220 * (i + 1), 100);
		}
		break;
	case 3:
		apu = new CApu(150, 200);
		gamemap = new CGameMap_3();
		for (int i = 0; i < GHOSTNUM; i++) {
			AddGhost(1, 120 * (i + 1), 100);
			AddGhost(2, 220 * (i + 1), 100);
			AddGhost(3, 320 * (i + 1), 100);
		}
		break;
	default:
		break;
	}
	gamemap->LoadBitmap();
	for (int i = 0; i < GHOSTNUM; i++)
		ghost[i]->LoadBitmap();
	apu->LoadBitmap();

	//CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
	/*
	background.SetTopLeft(BACKGROUND_X,0);				// 設定背景的起始座標
	help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
	hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// 指定剩下撞擊數的座標
	CAudio::Instance()->Play(AUDIO_LAKE, true);			// 撥放 WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// 撥放 MIDI
	*/
}

void CGameStateRun::OnInit() { 								// 遊戲的初值及圖形設定
	// 當圖很多時，OnInit載入所有的圖要花很多時間。
	//為避免玩遊戲的人等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%

	// 完成部分Loading動作，提高進度
	ShowInitProgress(50);
	Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep

	// 載入其他資料
	//CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
	/*
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// 載入說明的圖形
	corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
	corner.ShowBitmap(background);							// 將corner貼到background
	hits_left.LoadBitmap();	
	*/
	//CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
	//CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// 載入編號2的聲音ntut.mid
	
	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
	CAudio::Instance()->Load(AUDIO_BGM, "sounds\\bgm.mp3");
	CAudio::Instance()->Load(AUDIO_WIN, "sounds\\win.mp3");
	CAudio::Instance()->Load(AUDIO_LOSE, "sounds\\lose.mp3");
	CAudio::Instance()->Load(AUDIO_FIGHT, "sounds\\fight.mp3");
	CAudio::Instance()->Load(AUDIO_BUTTON, "sounds\\button.mp3");
	CAudio::Instance()->Play(AUDIO_BGM, true);
	gamemap = nullptr;
	apu = nullptr;	
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	const char KEY_LEFT = 0x25;
	const char KEY_UP = 0x26;
	const char KEY_RIGHT = 0x27;
	const char KEY_DOWN = 0x28;
	const char KEY_Q = 0x51;
	int apuX1 = apu->GetX1();
	int apuY1 = apu->GetY1();
	int apuX2 = apu->GetX2();
	int apuY2 = apu->GetY2();
	int exist = -1;
	int RANGE = 65;

	if (apu->GetMode() == 1) {
		apu->SetMode(2);
	}
	else { return; }

	if (nChar == KEY_Q) {
		curKeyState = 11;
		apu->SetSpace(true);
	}
	if (nChar == KEY_UP) {
		curKeyState = 1;
		exist = TheGhostNearbyApu(apuX1, apuY1-RANGE, apuX2, apuY2-RANGE);
	}
	if (nChar == KEY_DOWN) {
		curKeyState = 2;
		exist = TheGhostNearbyApu(apuX1, apuY1+RANGE, apuX2, apuY2+RANGE);
	}
	if (nChar == KEY_LEFT) {
		curKeyState = 3;
		exist = TheGhostNearbyApu(apuX1-RANGE, apuY1, apuX2-RANGE, apuY2);
	}
	if (nChar == KEY_RIGHT) {
		curKeyState = 4;
		exist = TheGhostNearbyApu(apuX1+RANGE, apuY1, apuX2+RANGE, apuY2);
	}

	if (exist != -1) {
		apu->SetMoving(curKeyState + 4);
		ghost[exist]->SetFighted(true);
	}
	else {
		apu->SetMoving(curKeyState);


	}
}
void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
}
void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) {  // 處理滑鼠的動作
}
void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) {	// 處理滑鼠的動作
}
void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) {	// 處理滑鼠的動作
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}
void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point) {  // 處理滑鼠的動作
}
void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) {	// 處理滑鼠的動作
}

int CGameStateRun::TheGhostNearbyApu(int x1, int y1, int x2, int y2) {
	for (int i = 0; i < GHOSTNUM; i++) {
		if (ghost[i]->GetX1() == x1 && ghost[i]->GetY1() == y1) {
		//if (x2 >= ghost[i]->GetX1() && x1 <= (ghost[i]->GetX1()+64) && y2 >= ghost[i]->GetY1()  && y1 <= (ghost[i]->GetY1()+64)) {
			if (ghost[i]->IsAlive()) return i;
			else break;
		}
	}
	return -1;
}
void CGameStateRun::AddGhost(int type, int x, int y) {
	switch (type) {
	case 1:
		ghost.push_back(new CBallon(x, y));
		break;
	case 2:
		ghost.push_back(new CBat(x, y));
		break;
	case 3:
		ghost.push_back(new CPumpkin(x, y));
		break;
	default:
		break;
	}
}

void CGameStateRun::OnMove() {
	// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));

	/* 阿噗動作 */
	apu->OnMove(gamemap);
	
	/* 鬼怪動作 */
	for (int i = 0; i < GHOSTNUM; i++)
		ghost[i]->OnMove(gamemap, apu);

	/* 音效 */
	//CAudio::Instance()->Play(AUDIO_DING);
	//if (hits_left.GetInteger() <= 0) {
	//	CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
	//	CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
	//}


	/* 判斷成功與失敗 */
	if (apu->IsSucceed()) {
		CGame::Instance()->SetFinish(curLevel);
		CGame::Instance()->SetApuXY(gamemap->ScreenXY(apu->GetXY()));
		apu->OnMove(gamemap);
		overCounter--;
		if (overCounter < 0)
			GotoGameState(GAME_STATE_OVER);
	}
	else if (apu->IsFail()) {
		CGame::Instance()->SetDead(curLevel);
		CGame::Instance()->SetApuXY(gamemap->ScreenXY(apu->GetXY()));
		apu->OnMove(gamemap);
		overCounter--;
		if (overCounter < 0)
			GotoGameState(GAME_STATE_OVER);
	}
}
void CGameStateRun::OnShow() {	
	gamemap->OnShow();					//貼上練習的地圖
	apu->OnShow(gamemap);
	for (int i = 0; i < GHOSTNUM; i++)
		ghost[i]->OnShow(gamemap);
}

}


