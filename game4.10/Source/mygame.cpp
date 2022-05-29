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
	if (curPage == 1) {									// �B��BeginPage
		x2 = button_begin.Left();							// button���W��x
		y2 = button_begin.Top();							// button���W��y
		x3 = x2 + button_begin.Width();						// button�k�U��x
		y3 = x2 + button_begin.Height();					// button�k�U��y
		if (x1 >= x2 && x1 <= x3 && y1 >= y2 && y1 <= y3) {
			//GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
			isBeginButtonDown = true;
			beginButtonHasDown = true;
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
		GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
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
		beginButtonHasDown = true;
		isBeginButtonDown = false;
	}
	
}

/* �o��class���C�����������A(Game Over)*/

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
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%

	// �}�l���J���
	//Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep

	// �̲׶i�׬�100%
	ShowInitProgress(100);
	//apu.LoadBitmap();
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// ���� font f; 160���16 point���r
	fp=pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	
	/* Apu relive animation */
	/*apu.SetMode(1);
	apu.SetState(11);
	apu.OnShow();*/


}

/* �o��class���C�����C�����檫��A�D�n���C���{�����b�o�� */

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g) {
	curLevel = CGame::Instance()->GetLevel();
}

CGameStateRun::~CGameStateRun() {
	delete gamemap;
	ghost.clear();
}

void CGameStateRun::OnBeginState() {
	GHOSTNUM = 5;
	counter = 30 * 1;									// 5 seconds
	curLevel = CGame::Instance()->GetLevel();

	switch (curLevel) {
	case 1:
		apu.Initialize(150, 200);
		gamemap = new CGameMap_1();
		for (int i = 0; i < GHOSTNUM; i++) {
			AddGhost(1, 120 * (i + 1), 100);
		}
		break;
	case 2:
		apu.Initialize(150, 200);
		gamemap = new CGameMap_2();
		for (int i = 0; i < GHOSTNUM; i++) {
			AddGhost(1, 120 * (i + 1), 100);
			AddGhost(2, 220 * (i + 1), 100);
		}
		break;
	case 3:
		apu.Initialize(150, 200);
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
	apu.LoadBitmap();
	for (int i = 0; i < GHOSTNUM; i++)
		ghost[i]->LoadBitmap();
	//for (int i = 0; i < NUMBALLONS; i++) {				// �]�wballon���_�l�y��
	//	int x_pos = 700; // 715,725
	//	int y_pos = 200;
	//	ballon[i].SetXY(x_pos,y_pos);
	//	ballon[i].SetIsAlive(true);
	//}
	/*
	background.SetTopLeft(BACKGROUND_X,0);				// �]�w�I�����_�l�y��
	help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
	hits_left.SetInteger(HITS_LEFT);					// ���w�ѤU��������
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
	CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
	CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
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
	/*
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// ���J�������ϧ�
	corner.LoadBitmap(IDB_CORNER);							// ���J�����ϧ�
	corner.ShowBitmap(background);							// �Ncorner�K��background
	hits_left.LoadBitmap();									
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// ���J�s��2���n��ntut.mid
	*/
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	gamemap = nullptr;
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	const char KEY_LEFT = 0x25; // keyboard���b�Y
	const char KEY_UP = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN = 0x28; // keyboard�U�b�Y
	int apuX1 = apu.GetX1();
	int apuY1 = apu.GetY1();
	int apuX2 = apu.GetX2();
	int apuY2 = apu.GetY2();
	int exist = -1;
	int RANGE = 25;

	if (apu.GetMode() == 1) apu.SetMode(2);
	else return;

	if (nChar == KEY_UP) {
		curKeyState = 1;
		//exist = TheGhostNearbyApu(apuX1, apuY1-RANGE, apuX2, apuY2-RANGE);
		if (exist != -1) {
			apu.SetFightUp(true);
			//ballon[exist].SetIsFighted(true);
		}
		else {
			apu.SetMovingUp(true);
		}
	}
	if (nChar == KEY_DOWN) {
		curKeyState = 2;
		//exist = TheGhostNearbyApu(apuX1, apuY1+RANGE, apuX2, apuY2+RANGE);
		if (exist != -1) {
			apu.SetFightDown(true);
			//ballon[exist].SetIsFighted(true);
		}
		else {
			apu.SetMovingDown(true);
		}
	}
	if (nChar == KEY_LEFT) {
		curKeyState = 3;
		//exist = TheGhostNearbyApu(apuX1-RANGE, apuY1, apuX2-RANGE, apuY2);
		if (exist != -1) {
			apu.SetFightLeft(true);
			//ballon[exist].SetIsFighted(true);
		}
		else {
			apu.SetMovingLeft(true);
		}
	}
	if (nChar == KEY_RIGHT) {
		curKeyState = 4;
		//exist = TheGhostNearbyApu(apuX1+RANGE, apuY1, apuX2+RANGE, apuY2);
		if (exist != -1) {
			apu.SetFightRight(true);
			//ballon[exist].SetIsFighted(true);
		}
		else {
			apu.SetMovingRight(true);
		}
	}
}
void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
}
void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) {  // �B�z�ƹ����ʧ@
	apu.SetMovingLeft(true);
}
void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) {	// �B�z�ƹ����ʧ@
	apu.SetMovingLeft(false);
}
void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) {	// �B�z�ƹ����ʧ@
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}
void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point) {  // �B�z�ƹ����ʧ@
	apu.SetMovingRight(true);
}
void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) {	// �B�z�ƹ����ʧ@
	apu.SetMovingRight(false);
}

int CGameStateRun::TheGhostNearbyApu(int x1, int y1, int x2, int y2) {
	for (int i = 0; i < GHOSTNUM; i++) {
		if (x2 >= ghost[i]->GetX1() && x1 <= ghost[i]->GetX2() && y2 >= ghost[i]->GetY1() && y1 <= ghost[i]->GetY2())
			if (ghost[i]->IsAlive()) return i;
			else break;
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
void CGameStateRun::OnMove()							// ���ʹC������
{
	// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));

	/* ���ʮ�y�� */
	//for (int i = 0; i < NUMBALLONS; i++)
	//{
	//	ballon[i].OnMove(&apu);
	//	ballon[i].OnMove(&apu);
	//	ballon[i].OnMove(&apu);
	//	// ��Ӫ��P
	//}

	/* ���ʪ��P */
	for (int i = 0; i < 4; i++)
		apu.OnMove(gamemap);
	if (apu.GetCurAnimationNum() == apu.GetCurAnimationLastNum()) {
		apu.ResetCurAnimation();
		apu.SetMode(1);
		apu.SetAllAction(false);
		/*for (int i = 0; i < NUMBALLONS; i++) {
			ballon[i].SwitchMode();
			ballon[i].SetState(0);
		}*/
	}
	if (apu.IsSucceed()) {
		apu.OnMove();
		counter--;
		if (counter < 0)
			GotoGameState(GAME_STATE_OVER);
	}

	/* �P�_Apu�O�_fight Ghost */
	for (int i = 0; i < GHOSTNUM; i++) {
		if (ghost[i]->IsAlive() && ghost[i]->IsFighted()) {			// �P�_��Apu������Ghost�A�hGhost����
			ghost[i]->SetIsAlive(false);
			//CAudio::Instance()->Play(AUDIO_DING); // �������n��

			//if (hits_left.GetInteger() <= 0) {
			//	CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
			//	CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
			//}
		}
		if (ghost[i]->IsAlive() && ghost[i]->HitApu(&apu)) {		// �P�_��Ghost�I��Apu�A�h����Game Over���A
			apu.SetMode(1);
			apu.SetState(9);
			apu.OnMove();
			counter--;
			if (counter < 0)
				GotoGameState(GAME_STATE_OVER);
		}
	}
}
void CGameStateRun::OnShow() {	
	gamemap->OnShow();					//�K�W�m�ߪ��a��
	apu.OnShow(gamemap);
	for (int i = 0; i < GHOSTNUM; i++)
		ghost[i]->OnShow(gamemap);
}

}


