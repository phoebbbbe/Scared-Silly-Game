#ifndef CBOUNCINGBALL_H
#define CBOUNCINGBALL_H
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѷ|�@���u�����y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CBouncingBall
	{
	public:
		CBouncingBall();
		void LoadBitmap();		// ���J�ϧ�
		void OnMove();			// ����
		void OnShow();			// �N�ϧζK��e��
		void SetFloor(int);
		void SetXY(int, int);
		void SetVelocity(int);
	private:
		int x, y;				// �ϧήy��
		int floor;				// �a�O��Y�y��
		bool rising;			// true��W�ɡBfalse��U��
		int initial_velocity;	// ��l�t��
		int velocity;			// �ثe���t��(�I/��)
		CAnimation animation;	// �Q�ΰʵe�@�ϧ�
	};

}

#endif