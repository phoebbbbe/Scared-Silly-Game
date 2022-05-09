#ifndef CAPU_H
#define CAPU_H

namespace game_framework {

	class CApu
	{
	public:
		CApu();
		int GetX1();					// ���P���W�� x �y��
		int GetY1();					// ���P���W�� y �y��
		int GetX2();					// ���P�k�U�� x �y��
		int GetY2();					// ���P�k�U�� y �y��
		int GetMode();
		int GetState();
		bool GetMoved();
		void Initialize();				// �]�w���P����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// ���ʪ��P
		//void Moving(int *map);
		void OnShow();					// �N���P�ϧζK��e��

		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetFightUp(bool flag);     // �]�w�O�Y���b���W����
		void SetFightDown(bool flag);   // �]�w�O�Y���b���U����
		void SetFightLeft(bool flag);   // �]�w�O�Y���b��������
		void SetFightRight(bool flag);  // �]�w�O�Y���b���k����
		void SetAllAction(bool flag);
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
		void SetXY(int stepSize);
		void SetMode(int flag);
		void SetState(int flag);
		void SetMoved(bool flag);
		int GetCurAnimationNum();
		int GetCurAnimationLastNum();
		void ResetCurAnimation();
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
		int curState;				// ���P�{�b����V:1(�W)2(�U)3(��)4(�k)5(���W)6(���U)7(����)8(���k)
		int curMode;				// ���P�{�b�����A:1(�R��), 2(����)
		int x, y;					// ���P���W���y��
		bool isMoved;
		bool isFightUp;             // �O�_���b���W����
		bool isFightDown;           // �O�_���b���U����
		bool isFightLeft;           // �O�_���b��������
		bool isFightRight;          // �O�_���b���k����
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
	};
}

#endif