#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"
#include "CApu.h"
#include "CGhost.h"
#include "CGameMap.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
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
		//int chooseLevel;
		int level;
	private:
		//CMovingBitmap logo;							// csie��logo
		CAnimation page_begin;
		CAnimation button_begin;
		CMovingBitmap page_level;
		CMovingBitmap levels[12];
		int curPage;									// 1(begin) 2(level)
	};	

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		int  HasGhost(int x1, int y1, int x2, int y2);

	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		const int		NUMBALLONS;
		int				curKeyState;
		CMovingBitmap	background;	// �I����
		CMovingBitmap	help;		// ������
		CMovingBitmap	corner;		// ������
		CInteger		hits_left;	// �ѤU��������
		CGameMap		*gamemap;
		CGameMap_1		gamemap1;	// Level_1
		CGameMap_2		gamemap2;	// Level_2
		CGameMap_3		gamemap3;	// Level_3
		CApu            apu;		// ���P
		CGhost			*ballon;	// ����y��
		int				counter;	// �˼ƭp�ɼ�
		int				level;
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
		CApu apu;
		int  counter;	// �˼Ƥ��p�ƾ�
	};

}