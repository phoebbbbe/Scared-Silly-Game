#ifndef CGHOST_H
#define CGHOST_H

namespace game_framework {

	class CGhost
	{
	public:
		CGhost();
		int  GetX();
		int  GetY();
		bool HitApu(CApu *apu);				// 是否碰到阿噗
		bool IsAlive();						// 是否活著
		bool IsFighted();
		void LoadBitmap();					// 載入圖形
		void OnMove();						// 移動
		void OnMove(CApu *apu);
		void OnShow();						// 將圖形貼到畫面
		void SetXY(int nx, int ny);			// 設定圓心的座標
		void SetIsAlive(bool alive);		// 設定是否活著
		void SetIsFighted(bool fighted);
		void SetDelay(int d);				// 設定旋轉的速度
		void SetMode(int m);
		void SetState(int s);
		void SwitchMode();
		int  WhereIsApu(CApu *apu);
		void FollowApu(CApu *apu, int stepsize);
	protected:
		CAnimation ghost;
		CAnimation ghost_die;
		CMovingBitmap fork;
		int x, y;					// 鬼怪的座標
		int dx, dy;					// 鬼怪距離圓心的位移量
		int index;					// 鬼怪的「角度」，0-17表示0-360度
		int delay_counter;			// 調整旋轉速度的計數器
		int delay;					// 旋轉的速度
		bool isAlive;				// 是否活著
		bool isFighted;
		int curMode;				// 鬼怪現在的狀態:1(靜止), 2(移動)
		int curState;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};
}


#endif
