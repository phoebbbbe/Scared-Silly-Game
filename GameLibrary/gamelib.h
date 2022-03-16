#define SIZE_X 640
#define SIZE_Y 480
#define OPEN_AS_FULLSCREEN false
#define SHOW_LOAD_PROGRESS true
#define DEFAULT_BG_COLOR RGB(0,0,0);
#define GAME_CYCLE_TIME 33
#define ENABLE_GAME_PAUSE true
#define ENABLE_AUDIO true

enum GAME_STATES {
    GAME_STATE_INIT,
    GAME_STATE_RUN,
    GAME_STATE_OVER
};

#include <list>
#include <vector>
#include <map>
using namespace std;

#define GAME_ASSERT(boolexp, str)                                           \
        if (!(boolexp)) {                                                   \
            int id;                                                         \
            char s[300] = "";                                               \
            sprintf(s, "Game fatal error:\n\n%s\n\nFile: %s\n\nLine: %d"    \
				"\n\n(Press Retry to debug the application, "				\
				"if it is executed in debug mode.)"							\
				"\n(Press Cancel otherwise.)",								\
				 str , __FILE__,__LINE__);                                  \
            id = AfxMessageBox(s, MB_RETRYCANCEL);                          \
            if (id == IDCANCEL)												\
				exit(1);													\
			AfxDebugBreak();	                                            \
        }

namespace game_framework {

class CMovingBitmap { //提供動態可移動的圖形
public:
    CMovingBitmap();
    int Height();
    int Left();
    void LoadBitmap(int, COLORREF=CLR_INVALID);
    void LoadBitmap(char *, COLORREF=CLR_INVALID);
    void SetTopLeft(int, int);
    void ShowBitmap();
    void ShowBitmap(double factor);
    void ShowBitmap(CMovingBitmap &);
    void Top();
    int Width();
protected:
    CRect location;
    bool isBitmapLoaded;
    unsigned SurfaceID;
};

class CAnimation {
public:
    CAnimation(int = 10);
    void AddBitmap(int, COLORREF=CLR_INVALID);
    void AddBitmap(char *, COLORREF=CLR_INVALID);
    int GetCurrentBitmapNumber();
    int Height();
    bool IsFinalBitmap();
    int Left();
    void OnMove();
    void OnShow();
    void Reset();
    void SetDelayCount(int);
    void SetTopLeft(int, int);
    int Top();
    int Width();
private:
    list<CMovingBitmap> bmp;
    list<CMovingBitmap>::iterator bmp_iter;
    int bmp_counter;
    int delay_counter;
    int delay_count;
    int x, y;
};

class CGame;
class CGameStateInit;
class CGameStateRun;
class CGameStateOver;

class CGameState {
public:
    CGameState(CGame *g);
    void OnDraw();
    void OnCycle();

    virtual ~CGameState() {}
    virtual void OnInit() {}
    virtual void OnKeyDown(UINT, UINT, UINT) {}
    virtual void OnKeyUp(UINT, UINT, UINT) {}
    virtual void OnLButtonDown(UINT nFlags, CPoint point) {}
    virtual void OnLButtonUp(UINT nFlags, CPoint point) {}
    virtual void OnMouseMove(UINT nFlags, CPoint point) {}
    virtual void OnRButtonDown(UINT nFlags, CPoint point) {}
    virtual void OnRButtonUp(UINT nFlags, CPoint point) {}
protected:
    void GotoGameState(int state);
    void ShowInitProgress(int percent);
    virtual void OnMove() {}
    virtual void OnShow() = 0;
    CGame *game;
};

class CGame {
public:
	CGame();										// Constructor
	~CGame();										// Destructor
	bool IsRunning();								// 讀取遊戲是否正在進行中
	void OnDraw();									// 對應CGameView的OnDraw()
	void OnFilePause();								// 遊戲暫停
	void OnInit();									// 遊戲繪圖及音效的初始化
	void OnInitStates();							// 遊戲各狀態的初值及圖形設定
	bool OnIdle();									// 遊戲的主迴圈
	void OnKeyDown(UINT, UINT, UINT);				// 處理鍵盤Down的動作
	void OnKeyUp(UINT, UINT, UINT);					// 處理鍵盤Up的動作
	void OnKillFocus();								// 遊戲被迫暫停
	void OnLButtonDown(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	void OnMouseMove(UINT nFlags, CPoint point);    // 處理滑鼠的動作 
	void OnRButtonDown(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	void OnResume();								// 處理自「待命」還原的動作
	void OnSetFocus();								// 處理Focus
	void OnSuspend();								// 處理「待命」的動作
	void SetGameState(int);
	static CGame *Instance();
private:
	bool			running;			// 遊戲是否正在進行中(未被Pause)
	bool            suspended;			// 遊戲是否被suspended
	const int		NUM_GAME_STATES;	// 遊戲的狀態數(3個狀態)
	CGameState		*gameState;			// pointer指向目前的遊戲狀態
	CGameState		*gameStateTable[3];	// 遊戲狀態物件的pointer
	static CGame	instance;			// 遊戲唯一的instance
};
}
