namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class����¶��骺�y
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CBall
	{
	public:
		CBall();
		bool HitEraser(CEraser *eraser);						// �O�_�I�����l
		bool IsAlive();											// �O�_����
		bool IsFighted();
		void LoadBitmap();										// ���J�ϧ�
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
		void SetXY(int nx, int ny);								// �]�w��ߪ��y��
		void SetIsAlive(bool alive);							// �]�w�O�_����
		void SetIsFighted(bool fighted);
		void SetDelay(int d);									// �]�w���઺�t��
		int GetX();
		int GetY();
	protected:
		CAnimation ghost;
		//CMovingBitmap bmp;			// �y����
		//CMovingBitmap bmp_center;	// ��ߪ���			
		int x, y;					// ��ߪ��y��
		int dx, dy;					// �y�Z����ߪ��첾�q
		int index;					// �y���u���סv�A0-17���0-360��
		int delay_counter;			// �վ����t�ת��p�ƾ�
		int delay;					// ���઺�t��
		bool is_alive;				// �O�_����
		bool is_fighted;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}