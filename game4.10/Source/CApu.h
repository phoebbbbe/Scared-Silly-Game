#ifndef CAPU_H
#define CAPU_H

namespace game_framework {

	class CApu
	{
	public:
		CApu();
		int  GetX1();					// ���P���W�� x �y��
		int  GetY1();					// ���P���W�� y �y��
		int  GetX2();					// ���P�k�U�� x �y��
		int  GetY2();					// ���P�k�U�� y �y��
		void Initialize();				// �]�w���P����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// ���ʪ��P
		void OnShow();					// �N���P�ϧζK��e��
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetFightUp(bool flag);     // �]�w�O�Y���b���W����
		void SetFightDown(bool flag);   // �]�w�O�Y���b���U����
		void SetFightLeft(bool flag);   // �]�w�O�Y���b��������
		void SetFightRight(bool flag);  // �]�w�O�Y���b���k����
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
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
		int curState = 0;
		int x, y;					// ���P���W���y��
		bool isFightUp;             // �O�_���b���W����
		bool isFightDown;           // �O�_���b���U����
		bool isFightLeft;           // �O�_���b�������
		bool isFightRight;          // �O�_���b���e����
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
	};
}

#endif