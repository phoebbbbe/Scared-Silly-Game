#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"
#include "CApu.h"
#include "CGhost.h"
#include "CGameMap.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
		void OnMove();
		bool isBeginButtonDown;
		bool beginButtonHasDown;
		//int chooseLevel;
		int level;
	private:
		//CMovingBitmap logo;							// csie的logo
		CAnimation page_begin;
		CAnimation button_begin;
		CMovingBitmap page_level;
		CMovingBitmap levels[12];
		int curPage;									// 1(begin) 2(level)
	};	

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		int  HasGhost(int x1, int y1, int x2, int y2);

	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		const int		NUMBALLONS;
		int				curKeyState;
		CMovingBitmap	background;	// 背景圖
		CMovingBitmap	help;		// 說明圖
		CMovingBitmap	corner;		// 角落圖
		CInteger		hits_left;	// 剩下的撞擊數
		CGameMap		*gamemap;
		CGameMap_1		gamemap1;	// Level_1
		CGameMap_2		gamemap2;	// Level_2
		CGameMap_3		gamemap3;	// Level_3
		CApu            apu;		// 阿噗
		CGhost			*ballon;	// 綠色氣球怪
		int				counter;	// 倒數計時數
		int				level;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CApu apu;
		int  counter;	// 倒數之計數器
	};

}