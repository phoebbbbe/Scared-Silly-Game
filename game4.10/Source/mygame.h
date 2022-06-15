#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"
#include "CApu.h"
#include "CGhost.h"
#include "CGameMap.h"

namespace game_framework {

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		//AUDIO_DING,				// 0
		//AUDIO_LAKE,				// 1
		//AUDIO_NTUT,				// 2
		AUDIO_BGM,				// 0
		AUDIO_WIN,				// 1
		AUDIO_LOSE,				// 2
		AUDIO_FIGHT,			// 3
		AUDIO_BUTTON			// 4
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);
	
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
		void OnMove();
		bool isBeginButtonDown;
		bool beginButtonHasDown;
		bool isAboutusButtonDown;
		bool isExplainButtonDown;
		bool isBackButtonDown;
	
	private:
		CAnimation page_begin;
		CMovingBitmap page_aboutus;
		CMovingBitmap page_explain;
		CMovingBitmap page_level;
		CAnimation button_begin;
		CMovingBitmap button_aboutus;
		CMovingBitmap button_explain;
		CMovingBitmap button_back;

		CMovingBitmap levels[12];
		int curPage;									// 1(begin) 2(level)
		int curLevel;
	};	

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		
		int  TheGhostNearbyApu(int x1, int y1, int x2, int y2);
		void AddGhost(int type, int x, int y);

	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	
	private:
		/*
		CMovingBitmap	background;	// �I����
		CMovingBitmap	help;		// ������
		CMovingBitmap	corner;		// ������
		CInteger		hits_left;	// �ѤU��������
		*/
		int				GHOSTNUM;
		
		CGameMap		*gamemap;
		vector<CGhost*> ghost;
		CApu            *apu;		// ���P

		int				overCounter;	// �˼ƭp�ɼ�
		int				curKeyState;
		int				curLevel;
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CAnimation apu_relive;
		int  apu_curMode;
		int  counter;	// �˼Ƥ��p�ƾ�
		int  curLevel;
		int  curState;
	};

}