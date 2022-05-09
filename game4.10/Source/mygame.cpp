/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

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
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	// �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%

	// �}�l���J���
	page_begin.AddBitmap(IDB_PAGE_BEGIN1);
	page_begin.AddBitmap(IDB_PAGE_BEGIN2);
	button_begin.AddBitmap(IDB_BUTTON_BEGIN1);
	button_begin.AddBitmap(IDB_BUTTON_BEGIN2);
	/*PAGE1*/
	isBeginButtonDown = false;
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep

	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo �����C������k
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// �����C��
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point) {
	int x1 = point.x;
	int y1 = point.y;
	int x2 = button_begin.Left();					// button���W��x
	int y2 = button_begin.Top();					// button���W��y
	int x3 = x2 + button_begin.Width();					// button�k�U��x
	int y3 = x2 + button_begin.Height();					// button�k�U��y
	if (x1 >= x2 && x1 <= x3 && y1 >= y2 && y1 <= y3) {
		//GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
		isBeginButtonDown = true;
		beginButtonHasDown = true;
	}
}

void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point) {
	if (isBeginButtonDown)
		GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	// �K�Wlogo
	page_begin.SetTopLeft((SIZE_X - page_begin.Width())/2, SIZE_Y/8);
	page_begin.OnShow();
	button_begin.SetTopLeft(510, 300);
	button_begin.OnShow();

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
	}
	
}
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
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
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%

	// �}�l���J���
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep

	// �̲׶i�׬�100%
	ShowInitProgress(100);
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
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
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
	/*for (int i = 0; i < NUMBALLS; i++) {				// �]�w�y���_�l�y��
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		ball[i].SetXY(x_pos, y_pos);
		ball[i].SetDelay(x_pos);
		ball[i].SetIsAlive(true);
	}*/

	for (int i = 0; i < NUMBALLONS; i++) {				// �]�wballon���_�l�y��
		int x_pos = 480 - 320 * i;
		int y_pos = 200;
		ballon[i].SetXY(x_pos, y_pos);
		ballon[i].SetDelay(x_pos);
		ballon[i].SetIsAlive(true);
	}
	apu.Initialize();
	background.SetTopLeft(BACKGROUND_X,0);				// �]�w�I�����_�l�y��
	help.SetTopLeft(0, SIZE_Y - help.Height());			// �]�w�����Ϫ��_�l�y��
	hits_left.SetInteger(HITS_LEFT);					// ���w�ѤU��������
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// ���w�ѤU�����ƪ��y��
	//CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
	//CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
	//CAudio::Instance()->Play(AUDIO_NTUT, true);			// ���� MIDI
}

void CGameStateRun::OnMove()							// ���ʹC������
{
	// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));

	// ���ʭI���Ϫ��y��
	if (background.Top() > SIZE_Y)
		background.SetTopLeft(60, -background.Height());
	background.SetTopLeft(background.Left(), background.Top() + 1);

	// ���ʮ�y��
	for (int i = 0; i < NUMBALLONS; i++)
	{
		ballon[i].OnMove(&apu);
		ballon[i].OnMove(&apu);
		ballon[i].OnMove(&apu);
		// ��Ӫ��P
	}
	// ���ʪ��P
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
	// �P�_���l�O�_�I��y
	//for (i = 0; i < NUMBALLS; i++) {
	//	//if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
	//	if (ball[i].IsAlive() && ball[i].IsFighted()) {
	//		ball[i].SetIsAlive(false);
	//		CAudio::Instance()->Play(AUDIO_DING);
	//		hits_left.Add(-1); // �ͩR��
	//		// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
	//		if (hits_left.GetInteger() <= 0) {
	//			CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
	//			CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
	//			GotoGameState(GAME_STATE_OVER);
	//		}
	//	}
	//}

	// �P�_Apu�O�_fight Ghost
	for (int i = 0; i < NUMBALLONS; i++) {
		if (ballon[i].IsAlive() && ballon[i].IsFighted()) {
			ballon[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);

			// �Y�Ѿl�I�����Ƭ�0�A�h����Game Over���A
			if (hits_left.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// ���� WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// ���� MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
		// �P�_��Ghost�I��Apu�A�h����Game Over���A
		if (ballon[i].IsAlive() && ballon[i].HitApu(&apu))
		{
			apu.SetState(9);
			GotoGameState(GAME_STATE_OVER);
		}
	}
	// ���ʼu�����y
	bball.OnMove();
	gamemap.OnMove();
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%

	// �}�l���J���
	int i;
	for (i = 0; i < NUMBALLONS; i++)
		ballon[i].LoadBitmap();								// ���J��i��ballon���ϧ�
	apu.LoadBitmap();
	background.LoadBitmap(IDB_BACKGROUND);					// ���J�I�����ϧ�

	// ��������Loading�ʧ@�A�����i��
	ShowInitProgress(50);
	Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep

	// �~����J��L���
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// ���J�������ϧ�
	corner.LoadBitmap(IDB_CORNER);							// ���J�����ϧ�
	corner.ShowBitmap(background);							// �Ncorner�K��background
	bball.LoadBitmap();										// ���J�ϧ�
	hits_left.LoadBitmap();									
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// ���J�s��0���n��ding.wav
	CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// ���J�s��1���n��lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// ���J�s��2���n��ntut.mid

	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%

	gamemap.LoadBitmap();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int exist = 0, RANGE = 25;
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
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
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y

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

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	//eraser.SetMovingLeft(true);
	apu.SetMovingLeft(true);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	//eraser.SetMovingLeft(false);
	apu.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	//eraser.SetMovingRight(true);
	apu.SetMovingRight(true);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	//eraser.SetMovingRight(false);
	apu.SetMovingRight(false);
}

void CGameStateRun::OnShow()
{
	//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
	//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
	//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C

	//  �K�W�I���ϡB�����ơB�y�B���l�B�u�����y
	background.ShowBitmap();			// �K�W�I����
	gamemap.OnShow();					//�K�W�m�ߪ��a��
	//help.ShowBitmap();					// �K�W������
	hits_left.ShowBitmap();
	for (int i = 0; i < NUMBALLONS; i++)
		ballon[i].OnShow();				// �K�W��i���y
	//bball.OnShow();						// �K�W�u�����y
	apu.OnShow();

	//  �K�W���W�Υk�U��������
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
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}

int CGameStateRun::HasGhost(int x1, int y1, int x2, int y2) {
	for (int i = 0; i < NUMBALLONS; i++) {
		if (ballon[i].GetX() >= x1 && ballon[i].GetX() <= x2 && ballon[i].GetY() >= y1 && ballon[i].GetY() <= y2)
			if (ballon[i].IsAlive())
				return i;
			else
				break;
	}
	return -1;
}
}


