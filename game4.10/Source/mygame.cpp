#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include <iostream>
using namespace std;

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	// 等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	ShowInitProgress(0);	// 一開始的loading進度為0%

	// 開始載入資料
	page_begin.AddBitmap(IDB_BEGIN_PAGE1);
	page_begin.AddBitmap(IDB_BEGIN_PAGE2);
	button_begin.AddBitmap(IDB_BUTTON_BEGIN1);
	button_begin.AddBitmap(IDB_BUTTON_BEGIN2);
	
	page_level.LoadBitmap(IDB_LEVEL_PAGE, RGB(255, 255, 255));
	level1.LoadBitmap(IDB_LEVEL1, RGB(255, 255, 255));
	level2.LoadBitmap(IDB_LEVEL2, RGB(255, 255, 255));
	level3.LoadBitmap(IDB_LEVEL3, RGB(255, 255, 255));
	/*PAGE1*/
	isBeginButtonDown = false;
	beginButtonHasDown = false;
	curState = 1;
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep

	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
}

void CGameStateInit::OnBeginState()
{

}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// 關閉遊戲
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point) {
	int x1 = point.x, y1 = point.y;
	int x2, y2, x3, y3, x4, y4;
	if (curState == 1) {									// 處於BeginPage
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
	else if (curState == 2) {								// 處於LevelPage
		x2 = level1.Left();
		y2 = level1.Top();
		x3 = level2.Left();
		y3 = level2.Top();
		x4 = level3.Left();
		y4 = level3.Top();
		if (x1 >= x2 && x1 <= (x2 + level1.Width()) && y1 >= y2 && y1 <= (y2 + level1.Height())) {
			//isBeginButtonDown = true;
			//beginButtonHasDown = true;
		} else if (x1 >= x3 && x1 <= (x3 + level2.Width()) && y1 >= y3 && y1 <= (y3 + level2.Height())) {

		} else if (x1 >= x4 && x1 <= (x4 + level3.Width()) && y1 >= y4 && y1 <= (y4 + level3.Height())) {

		}

	}
}

void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point) {
	if (isBeginButtonDown)
		GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	// 貼上logo
	page_begin.SetTopLeft((SIZE_X - page_begin.Width())/2, SIZE_Y/8);
	page_begin.OnShow();
	button_begin.SetTopLeft(510, 300);
	button_begin.OnShow();

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
	}
	
}
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
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
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep

	// 最終進度為100%
	ShowInitProgress(100);
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
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g), NUMBALLONS(2){
	ballon = new CGhost[NUMBALLONS];
}

CGameStateRun::~CGameStateRun() {
	delete[] ballon;
}

void CGameStateRun::OnBeginState() {
	const int BALL_GAP = 90;
	const int BALL_XY_OFFSET = 45;
	const int BALL_PER_ROW = 7;
	const int HITS_LEFT = 10;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	const int BACKGROUND_X = 60;
	const int ANIMATION_SPEED = 15;
	/*for (int i = 0; i < NUMBALLS; i++) {				// 設定球的起始座標
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		ball[i].SetXY(x_pos, y_pos);
		ball[i].SetDelay(x_pos);
		ball[i].SetIsAlive(true);
	}*/

	for (int i = 0; i < NUMBALLONS; i++) {				// 設定ballon的起始座標
		int x_pos = 480 - 320 * i;
		int y_pos = 200;
		ballon[i].SetXY(x_pos, y_pos);
		ballon[i].SetIsAlive(true);
	}
	apu.Initialize();
	background.SetTopLeft(BACKGROUND_X,0);				// 設定背景的起始座標
	help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
	hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// 指定剩下撞擊數的座標
	//CAudio::Instance()->Play(AUDIO_LAKE, true);			// 撥放 WAVE
	//CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
	//CAudio::Instance()->Play(AUDIO_NTUT, true);			// 撥放 MIDI
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));

	// 移動背景圖的座標
	if (background.Top() > SIZE_Y)
		background.SetTopLeft(60, -background.Height());
	background.SetTopLeft(background.Left(), background.Top() + 1);

	// 移動氣球鬼
	for (int i = 0; i < NUMBALLONS; i++)
	{
		ballon[i].OnMove(&apu);
		ballon[i].OnMove(&apu);
		ballon[i].OnMove(&apu);
		// 比照阿噗
	}
	// 移動阿噗
	apu.OnMove();
	apu.OnMove();
	apu.OnMove();
	apu.OnMove();
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

	// 判斷Apu是否fight Ghost
	for (int i = 0; i < NUMBALLONS; i++) {
		if (ballon[i].IsAlive() && ballon[i].IsFighted()) {
			ballon[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);

			// 若剩餘碰撞次數為0，則跳到Game Over狀態
			if (hits_left.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
		// 判斷當Ghost碰到Apu，則跳到Game Over狀態
		if (ballon[i].IsAlive() && ballon[i].HitApu(&apu))
		{
			apu.SetState(9);
			GotoGameState(GAME_STATE_OVER);
		}
	}
	// 移動彈跳的球
	bball.OnMove();
	gamemap.OnMove();
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
	bball.LoadBitmap();										// 載入圖形
	hits_left.LoadBitmap();									
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// 載入編號2的聲音ntut.mid

	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%

	gamemap.LoadBitmap();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int exist = 0, RANGE = 25;
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	if (apu.GetMode() == 1)
		apu.SetMode(2);
	else
		return;

	if (nChar == KEY_UP) {
		curKeyState = 1;
		exist = HasGhost(apu.GetX1(), apu.GetY1() - RANGE, apu.GetX2(), apu.GetY2() - RANGE);
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
		exist = HasGhost(apu.GetX1(), apu.GetY1() + RANGE, apu.GetX2(), apu.GetY2() + RANGE);
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
		exist = HasGhost(apu.GetX1() - RANGE, apu.GetY1(), apu.GetX2() - RANGE, apu.GetY2());
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
		exist = HasGhost(apu.GetX1() + RANGE, apu.GetY1(), apu.GetX2() + RANGE, apu.GetY2());
		if (exist != -1) {
			apu.SetFightRight(true);
			ballon[exist].SetIsFighted(true);
		}
		else {
			apu.SetMovingRight(true);
		}
	}
	gamemap.OnKeyDown(nChar);
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭

	//if (nChar == KEY_LEFT)
	//{
	//	//sleep_for(nanoseconds(10));
	//	//sleep_until(system_clock::now() + seconds(1));
	//	//eraser.SetMovingLeft(false);
	//	apu.SetMovingLeft(false);
	//	apu.SetFightLeft(false);
	//}
	//if (nChar == KEY_RIGHT)
	//{
	//	//eraser.SetMovingRight(false);
	//	apu.SetMovingRight(false);
	//	apu.SetFightRight(false);
	//}
	//if (nChar == KEY_UP)
	//{
	//	//eraser.SetMovingUp(false);
	//	apu.SetMovingUp(false);
	//	apu.SetFightUp(false);
	//}
	//if (nChar == KEY_DOWN)
	//{
	//	//eraser.SetMovingDown(false);
	//	apu.SetMovingDown(false);
	//	apu.SetFightDown(false);
	//}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	//eraser.SetMovingLeft(true);
	apu.SetMovingLeft(true);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	//eraser.SetMovingLeft(false);
	apu.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	//eraser.SetMovingRight(true);
	apu.SetMovingRight(true);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	//eraser.SetMovingRight(false);
	apu.SetMovingRight(false);
}

void CGameStateRun::OnShow()
{
	//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
	//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
	//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。

	//  貼上背景圖、撞擊數、球、擦子、彈跳的球
	background.ShowBitmap();			// 貼上背景圖
	gamemap.OnShow();					//貼上練習的地圖
	//help.ShowBitmap();					// 貼上說明圖
	hits_left.ShowBitmap();
	for (int i = 0; i < NUMBALLONS; i++)
		ballon[i].OnShow();				// 貼上第i號球
	//bball.OnShow();						// 貼上彈跳的球
	apu.OnShow();

	//  貼上左上及右下角落的圖
	corner.SetTopLeft(0,0);
	corner.ShowBitmap();
	corner.SetTopLeft(SIZE_X-corner.Width(), SIZE_Y-corner.Height());
	corner.ShowBitmap();

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

int CGameStateRun::HasGhost(int x1, int y1, int x2, int y2) {
	for (int i = 0; i < NUMBALLONS; i++) {
		if (x2 >= ballon[i].GetX1() && x1 <= ballon[i].GetX2() && y2 >= ballon[i].GetY1()+5 && y1 <= ballon[i].GetY2())
			if (ballon[i].IsAlive())
				return i;
			else
				break;
	}
	return -1;
}
}


