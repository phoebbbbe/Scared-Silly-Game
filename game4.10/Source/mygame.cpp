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

/* �o��class���C�����C���}�Y�e������*/

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g){}

void CGameStateInit::OnInit() {
	/* ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C
	���קK���C�����H�������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	 �@�}�l��loading�i�׬�0% */
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
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep

	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
}

void CGameStateInit::OnBeginState() {}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE) {
		CGame::Instance()->SetLevel(curLevel);
		GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
	}
	else if (nChar == KEY_ESC)								// Demo �����C������k
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// �����C��
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point) {
	int x1 = point.x, y1 = point.y;
	int x2, y2, x3, y3;
	int x4, y4, x5, y5; // about
	int x6, y6, x7, y7; // explain
	// add music button
	if (curPage == 1) {									// �B��BeginPage
		x2 = button_begin.Left();							// button���W��x
		y2 = button_begin.Top();							// button���W��y
		x3 = x2 + button_begin.Width();						// button�k�U��x
		y3 = x2 + button_begin.Height();					// button�k�U��y
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
	else if (curPage == 2) {								// �B��LevelPage
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
		GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
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

	// Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
	//CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	//CFont f,*fp;
	//f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	//fp=pDC->SelectObject(&f);					// ��� font f
	//pDC->SetBkColor(RGB(0,0,0));
	//pDC->SetTextColor(RGB(255,255,0));
	//pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	//pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	//if (ENABLE_GAME_PAUSE)
	//	pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	//pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	//pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	//CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
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

/* �o��class���C�����������A(Game Over)*/

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
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%

	// �}�l���J���
	//Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep

	// �̲׶i�׬�100%
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
		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));
		char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
		sprintf(str, "Apu Succeed!");
		pDC->TextOut(240, 210, str);
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}
	else {
		POINT pos = CGame::Instance()->GetApuXY();
		apu_relive.SetTopLeft(pos.x, pos.y);
		apu_relive.OnShow();
	}


}

/* �o��class���C�����C�����檫��A�D�n���C���{�����b�o�� */

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

	//CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
	/*
	background.SetTopLeft(BACKGROUND_X,0);				// �]�w�I�����_�l�y��
	help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
	hits_left.SetInteger(HITS_LEFT);					// ���w�ѤU��������
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
	CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// ���� MIDI
	*/
}

void CGameStateRun::OnInit() { 								// �C������Ȥιϧγ]�w
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C
	//���קK���C�����H�������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%

	// ��������Loading�ʧ@�A�����i��
	ShowInitProgress(50);
	Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep

	// ���J��L���
	//CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
	/*
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// ���J�������ϧ�
	corner.LoadBitmap(IDB_CORNER);							// ���J�����ϧ�
	corner.ShowBitmap(background);							// �Ncorner�K��background
	hits_left.LoadBitmap();	
	*/
	//CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
	//CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// ���J�s��2���n��ntut.mid
	
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
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
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
}
void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) {  // �B�z�ƹ����ʧ@
}
void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) {	// �B�z�ƹ����ʧ@
}
void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) {	// �B�z�ƹ����ʧ@
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}
void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point) {  // �B�z�ƹ����ʧ@
}
void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) {	// �B�z�ƹ����ʧ@
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
	// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));

	/* ���P�ʧ@ */
	apu->OnMove(gamemap);
	
	/* ���ǰʧ@ */
	for (int i = 0; i < GHOSTNUM; i++)
		ghost[i]->OnMove(gamemap, apu);

	/* ���� */
	//CAudio::Instance()->Play(AUDIO_DING);
	//if (hits_left.GetInteger() <= 0) {
	//	CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
	//	CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
	//}


	/* �P�_���\�P���� */
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
	gamemap->OnShow();					//�K�W�m�ߪ��a��
	apu->OnShow(gamemap);
	for (int i = 0; i < GHOSTNUM; i++)
		ghost[i]->OnShow(gamemap);
}

}


