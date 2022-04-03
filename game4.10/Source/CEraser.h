namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CEraser
	{
	public:
		CEraser();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// �������l
		void OnShow();					// �N���l�ϧζK��e��
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetFightUp(bool flag);
		void SetFightDown(bool flag);
		void SetFightBack(bool flag);
		void SetFightFront(bool flag);
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
	protected:
		CAnimation animation;		// ���l���ʵe
		CAnimation animationRunUp;
		CAnimation animationRunDown;
		CAnimation animationRunBack;
		CAnimation animationRunFront;
		CAnimation animationFightUp;
		CAnimation animationFightDown;
		CAnimation animationFightBack;
		CAnimation animationFightFront;
		CAnimation animationFail;
		CAnimation animationSuccess;
		CMovingBitmap bmpInitApu;
		int curState = 0;
		int x, y;					// ���l���W���y��
		bool isFightUp; // �O�_���b���W����
		bool isFightDown; // �O�_���b���U����
		bool isFightBack; // �O�_���b�������
		bool isFightFront; // �O�_���b���e����
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
	};
}