#ifndef CGHOST_H
#define CGHOST_H

namespace game_framework {

	class CGhost
	{
	public:
		CGhost();
		bool HitApu(CApu *apu);						// 是否碰到阿噗
		bool IsAlive();											// 是否活著
		bool IsFighted();
		bool IsApuMove();
		void LoadBitmap();										// 載入圖形
		void OnMove();											// 移動
		void OnMove(CApu *apu);
		void OnShow();											// 將圖形貼到畫面
		void SetXY(int nx, int ny);								// 設定圓心的座標
		void SetIsAlive(bool alive);							// 設定是否活著
		void SetIsFighted(bool fighted);
		void SetIsApuMove(bool apu_move);
		void SetDelay(int d);									// 設定旋轉的速度
		void SetMode(int m);
		int WhereIsApu(CApu *apu);
		int GetX();
		int GetY();
		
	protected:
		CAnimation ghost;
		int x, y;					// 鬼怪的座標
		int dx, dy;					// 鬼怪距離圓心的位移量
		int index;					// 鬼怪的「角度」，0-17表示0-360度
		int delay_counter;			// 調整旋轉速度的計數器
		int delay;					// 旋轉的速度
		bool is_alive;				// 是否活著
		bool is_fighted;
		bool is_apu_move;
		int mode;
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形
	};
}


#endif
