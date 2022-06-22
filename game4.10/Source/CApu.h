#ifndef CAPU_H
#define CAPU_H
#include "CGameMap.h"
namespace game_framework {

	class CApu
	{
	public:
		CApu();
		CApu(int x, int y);
		~CApu();
		int	  GetInitX1();
		int	  GetInitY1();
		int	  GetX1();					// ���P���W�� x �y��
		int   GetY1();					// ���P���W�� y �y��
		int   GetX2();					// ���P�k�U�� x �y��
		int   GetY2();					// ���P�k�U�� y �y��
		POINT GetXY();
		int   GetMode();
		int   GetState();
		bool  GetMoved();
		int   GetCurAnimationNum();
		int   GetCurAnimationLastNum();
		void  ResetCurAnimation();

		void  SetXY(int nx, int ny);		// �]�w���P���W���y��
		void  SetXY(int stepSize);
		//void SetInitTopLeft();

		void  SetMoving(int flag);
		void  SetMoved(bool flag);
		void  SetMode(int flag);
		void  SetState(int flag);

		bool  IsSucceed();
		bool  IsFail();

		void  Initialize(int x, int y);
		void  LoadBitmap();
		void  OnMove(CGameMap *map);
		void  OnShow(CGameMap *map);

	protected:
		CAnimation moveUp;
		CAnimation moveDown;
		CAnimation moveLeft;
		CAnimation moveRight;
		CAnimation fightUp;
		CAnimation fightDown;
		CAnimation fightLeft;
		CAnimation fightRight;
		CAnimation fail;
		CAnimation success;
		CMovingBitmap initApu;
		CMovingBitmap initUp;
		CMovingBitmap initDown;
		CMovingBitmap initLeft;
		CMovingBitmap initRight;
		POINT pos;
		POINT pos_init;
		POINT pos_show;
		int curState;				// ���P�{�b����V:1(�W)2(�U)3(��)4(�k)5(���W)6(���U)7(����)8(���k)
		int curMode;				// ���P�{�b�����A:1(�R��), 2(����)
		bool isMoved;
		bool isSpace;
	};
}

#endif