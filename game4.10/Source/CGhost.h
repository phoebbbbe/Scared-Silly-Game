#ifndef CGHOST_H
#define CGHOST_H

namespace game_framework {

	enum class CGhosts {
		CBallon,
		CBat,
		CPumpkin,
	};

	class CGhost
	{
	public:
		CGhost(int x, int y);
		~CGhost();

		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();

		void SetXY(int nx, int ny);			// �]�w���ߪ��y��
		void SetIsAlive(bool alive);		// �]�w�O�_����
		void SetIsFighted(bool fighted);
		void SetMode(int m);
		void SetState(int s);
		void SetFork();

		bool IsAlive();						// �O�_����
		bool IsFighted();					// �O�_�Q����
		bool HitApu(CApu *apu);				// �O�_�I����P

		/* Apu Function */
		void SwitchMode();
		int  WhereIsApu(CApu *apu);
		void FollowApu(CApu *apu, int stepsize);

		void Initialize(int x, int y);
		virtual void LoadBitmap() = 0;					// ���J�ϧ�
		void OnMove();						// ����
		void OnMove(CApu *apu);
		void OnShow();						// �N�ϧζK��e��
		void OnShow(CGameMap *m);

	protected:
		CAnimation ghost;
		CAnimation ghost_die;
		CMovingBitmap fork1;
		CMovingBitmap fork2;
		CMovingBitmap fork3;
		CMovingBitmap fork4;
		POINT pos;					// ���Ǫ��y��
		bool isAlive;				// �O�_����
		bool isFighted;
		int  curMode;				// ���ǲ{�b�����A:1(�R��), 2(����)
		int  curState;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x��
	};

	class CBallon : public CGhost {
	public:
		CBallon(int x, int y);
		~CBallon();
		void LoadBitmap() override;		
	};

	class CBat : public CGhost {
	public:
		CBat(int x, int y);
		~CBat();
		void LoadBitmap() override;
	};

	class CPumpkin : public CGhost {
	public:
		CPumpkin(int x, int y);
		~CPumpkin();
		void LoadBitmap() override;
	};
}


#endif
