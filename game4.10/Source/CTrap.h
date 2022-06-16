#ifndef CTRAP_H
#define CTRAP_H

namespace game_framework {

	enum class CTraps {
		CClaw,
		CSpike,
		CBouncingBrick,
	};

	class CTrap {
	public:
		CTrap(int x, int y);
		~CTrap();

		int GetX1();
		int GetY1();
		int  GetCurAnimationNum();
		int  GetCurAnimationLastNum();
		void ResetCurAnimation();

		void SetXY(int nx, int ny);
		void SetMode(int mode);
		void SetState(int state);

		void SwitchState();

		void Initialize(int x, int y);
		virtual void LoadBitmap() = 0;
		/*virtual void OnMove(CGameMap *map, CApu *apu);
		virtual void OnShow(CGameMap *map);*/
	protected:
		CAnimation trap_up;
		CAnimation trap_down;
		POINT pos;
		POINT pos_show;
		bool switchState;
		int curMode;  // 1 : still, 2 move
		int curState; // 1 : up, 2 : down
		int counter;
	};

	class CClaw : public CTrap {
	public:
		CClaw(int x, int y);
		~CClaw();
		void LoadBitmap() override;
		/*void OnMove(CGameMap *map, CApu *apu) override;
		void OnShow(CGameMap *map) override;*/
	};
	class CSpike : public CTrap {
		CSpike(int x, int y);
		~CSpike();
		void LoadBitmap() override;
		/*void OnMove(CGameMap *map, CApu *apu) override;
		void OnShow(CGameMap *map) override;*/
	};
	class CBouncingBrick : public CTrap {
		CBouncingBrick(int x, int y);
		~CBouncingBrick();

		void LoadBitmap() override;
		/*void OnMove(CGameMap *map, CApu *apu) override;
		void OnShow(CGameMap *map) override;*/
	};
}
#endif