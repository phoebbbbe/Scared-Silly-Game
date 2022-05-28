#ifndef CAPU_H
#define CAPU_H
#include "CGameMap.h"
namespace game_framework {

	class CApu
	{
	public:
		/* Constructor */
		CApu();
		~CApu();

		/* Getter */
		int  GetX1();					// ���P���W�� x �y��
		int  GetY1();					// ���P���W�� y �y��
		int  GetX2();					// ���P�k�U�� x �y��
		int  GetY2();					// ���P�k�U�� y �y��
		int  GetMode();
		int  GetState();
		bool GetMoved();
		int  GetCurAnimationNum();
		int  GetCurAnimationLastNum();

		/* Setter */
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetFightUp(bool flag);     // �]�w�O�Y���b���W����
		void SetFightDown(bool flag);   // �]�w�O�Y���b���U����
		void SetFightLeft(bool flag);   // �]�w�O�Y���b��������
		void SetFightRight(bool flag);  // �]�w�O�Y���b���k����
		void SetAllAction(bool flag);
		//void SetInitTopLeft();
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
		void SetXY(int stepSize);
		void SetMode(int flag);
		void SetState(int flag);
		void SetMoved(bool flag);
		void ResetCurAnimation();

		/* Judge */
		bool IsSucceed();

		//
		void Initialize();				// �]�w���P����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// ���ʪ��P
		void OnMove(CGameMap *map);
		void OnShow();					// �N���P�ϧζK��e��
		void OnShow(CGameMap *map);

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
		CAnimation relive;
		CMovingBitmap initApu;
		CMovingBitmap initUp;
		CMovingBitmap initDown;
		CMovingBitmap initLeft;
		CMovingBitmap initRight;
		int curState;				// ���P�{�b����V:1(�W)2(�U)3(��)4(�k)5(���W)6(���U)7(����)8(���k)
		int curMode;				// ���P�{�b�����A:1(�R��), 2(����)
		POINT pos;
		bool isMoved;
		bool isFightUp;             // �O�_���b���W����
		bool isFightDown;           // �O�_���b���U����
		bool isFightLeft;           // �O�_���b��������
		bool isFightRight;          // �O�_���b���k����
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isSucceed;
	};
}

#endif