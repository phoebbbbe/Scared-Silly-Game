#ifndef CGHOST_H
#define CGHOST_H

namespace game_framework {

	class CGhost
	{
	public:
		CGhost();
		int  GetX();
		int  GetY();
		bool HitApu(CApu *apu);				// �O�_�I����P
		bool IsAlive();						// �O�_����
		bool IsFighted();
		void LoadBitmap();					// ���J�ϧ�
		void OnMove();						// ����
		void OnMove(CApu *apu);
		void OnShow();						// �N�ϧζK��e��
		void SetXY(int nx, int ny);			// �]�w��ߪ��y��
		void SetIsAlive(bool alive);		// �]�w�O�_����
		void SetIsFighted(bool fighted);
		void SetDelay(int d);				// �]�w���઺�t��
		void SetMode(int m);
		void SetState(int s);
		void SwitchMode();
		int  WhereIsApu(CApu *apu);
		void FollowApu(CApu *apu, int stepsize);
	protected:
		CAnimation ghost;
		CAnimation ghost_die;
		CMovingBitmap fork;
		int x, y;					// ���Ǫ��y��
		int dx, dy;					// ���ǶZ����ߪ��첾�q
		int index;					// ���Ǫ��u���סv�A0-17���0-360��
		int delay_counter;			// �վ����t�ת��p�ƾ�
		int delay;					// ���઺�t��
		bool isAlive;				// �O�_����
		bool isFighted;
		int curMode;				// ���ǲ{�b�����A:1(�R��), 2(����)
		int curState;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};
}


#endif
