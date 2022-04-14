#ifndef CAPU_H
#define CAPU_H

namespace game_framework {

	class CApu
	{
	public:
		CApu();
		int  GetX1();					// 阿噗左上角 x 座標
		int  GetY1();					// 阿噗左上角 y 座標
		int  GetX2();					// 阿噗右下角 x 座標
		int  GetY2();					// 阿噗右下角 y 座標
		void Initialize();				// 設定阿噗為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動阿噗
		void OnShow();					// 將阿噗圖形貼到畫面
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetFightUp(bool flag);     // 設定是某正在往上攻擊
		void SetFightDown(bool flag);   // 設定是某正在往下攻擊
		void SetFightLeft(bool flag);   // 設定是某正在往左攻擊
		void SetFightRight(bool flag);  // 設定是某正在往右攻擊
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
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
		int x, y;					// 阿噗左上角座標
		bool isFightUp;             // 是否正在往上攻擊
		bool isFightDown;           // 是否正在往下攻擊
		bool isFightLeft;           // 是否正在往後攻擊
		bool isFightRight;          // 是否正在往前攻擊
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
	};
}

#endif