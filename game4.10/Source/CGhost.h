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
		/* Constructor */
		CGhost();
		~CGhost();

		/* Getter */
		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();

		/* Setter */
		void SetXY(int nx, int ny);			// 設定中心的座標
		void SetIsAlive(bool alive);		// 設定是否活著
		void SetIsFighted(bool fighted);
		void SetMode(int m);
		void SetState(int s);
		void SetFork();

		/* judge */
		bool IsAlive();						// 是否活著
		bool IsFighted();					// 是否被攻擊
		bool HitApu(CApu *apu);				// 是否碰到阿噗

		/* Member Function */
		void SwitchMode();
		int  WhereIsApu(CApu *apu);
		void FollowApu(CApu *apu, int stepsize);

		//
		virtual void LoadBitmap() = 0;					// 載入圖形
		void OnMove();						// 移動
		void OnMove(CApu *apu);
		void OnShow();						// 將圖形貼到畫面

	protected:
		CAnimation ghost;
		CAnimation ghost_die;
		CMovingBitmap fork1;
		CMovingBitmap fork2;
		CMovingBitmap fork3;
		CMovingBitmap fork4;
		POINT pos;					// 鬼怪的座標
		bool isAlive;				// 是否活著
		bool isFighted;
		int  curMode;				// 鬼怪現在的狀態:1(靜止), 2(移動)
		int  curState;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};

	class CBallon : public CGhost {
	public:
		CBallon();
		~CBallon();
		void LoadBitmap() override;		
	};

	class CBat : public CGhost {
	public:
		CBat();
		~CBat();
		void LoadBitmap() override;
	};

	class CPumpkin : public CGhost {
	public:
		CPumpkin();
		~CPumpkin();
		void LoadBitmap() override;
	};
}


#endif
