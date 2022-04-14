#ifndef CGHOST_H
#define CGHOST_H

namespace game_framework {

	class CGhost
	{
	public:
		CGhost();
		bool HitApu(CApu *apu);						// �O�_�I����P
		bool IsAlive();											// �O�_����
		bool IsFighted();
		bool IsApuMove();
		void LoadBitmap();										// ���J�ϧ�
		void OnMove();											// ����
		void OnMove(CApu *apu);
		void OnShow();											// �N�ϧζK��e��
		void SetXY(int nx, int ny);								// �]�w��ߪ��y��
		void SetIsAlive(bool alive);							// �]�w�O�_����
		void SetIsFighted(bool fighted);
		void SetIsApuMove(bool apu_move);
		void SetDelay(int d);									// �]�w���઺�t��
		void SetMode(int m);
		int WhereIsApu(CApu *apu);
		int GetX();
		int GetY();
		
	protected:
		CAnimation ghost;
		int x, y;					// ���Ǫ��y��
		int dx, dy;					// ���ǶZ����ߪ��첾�q
		int index;					// ���Ǫ��u���סv�A0-17���0-360��
		int delay_counter;			// �վ����t�ת��p�ƾ�
		int delay;					// ���઺�t��
		bool is_alive;				// �O�_����
		bool is_fighted;
		bool is_apu_move;
		int mode;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}


#endif
