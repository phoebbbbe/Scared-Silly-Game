#ifndef CGAMEMAP_H
#define CGAMEMAP_H

namespace game_framework {

	/* Map : 1248*624  (24*12)
	Screen : 676*364 (13*7)
	cell : 52*52 */
	enum class CGameMaps {
		CGameMap_1,
		CGameMap_2,
		CGameMap_3,
		CGameMap_4,
		CGameMap_5,
		CGameMap_6,
		CGameMap_7,
		CGameMap_8
	};

	class CGameMap {
	public:
		/* Constructor */
		CGameMap();
		~CGameMap();

		/* Getter */
		int *GetMap();
		POINT GetPieceXY();
		POINT GetSXY();

		/* Setter */
		void SetSX(int);
		void SetSY(int);
		int ScreenX(int);
		int ScreenY(int);

		/* Judge */
		bool IsEmpty(int, int);
		bool HasPiece(int, int, int, int);
		/*bool GAMEOVER;
		bool APUWIN;*/

		/* Ghost Function */
		/*virtual int  GhostNearbyApu(int, int, int, int) = 0;
		virtual void SetGhostFighted(int, bool) = 0;
		virtual void SetGhostMove(int) = 0;
		virtual void SwitchGhostMode() = 0;*/
		//
		void LoadBitmap();
		virtual void LoadLevelBitmap() = 0;
		virtual void OnShow() = 0;
		virtual void OnMove() = 0;

	protected:
		CMovingBitmap brick1;
		CMovingBitmap brick2;
		CMovingBitmap brick3;
		CMovingBitmap brick4;
		CMovingBitmap piece;
		
		int map[30][30];						// 地圖
		int sx, sy;								// 螢幕左上角座標
		const int X, Y;							// 在地圖上的座標
		const int MW, MH;						// 每隔長寬大小
	};

	/* CGameMap_1 */
	class CGameMap_1 : public CGameMap {
	public:
		CGameMap_1();
		~CGameMap_1();

		/*int  GhostNearbyApu(int, int, int, int) override;
		void SetGhostFighted(int, bool) override;
		void SetGhostMove(int) override;
		void SwitchGhostMode() override;*/

		void LoadLevelBitmap() override;
		void OnShow() override;
		void OnMove() override;

	private:
		/* Floor */
		CMovingBitmap turf;						// 草皮
		CMovingBitmap brick3;
		CMovingBitmap brick4;
		/* Background */
		CMovingBitmap explination;
		CMovingBitmap tree[20];
		CMovingBitmap grass[10];
		/* Ghost */

	};

	/* CGameMap_2 */
	class CGameMap_2 : public CGameMap {
	public:
		CGameMap_2();
		~CGameMap_2();

		/*int  GhostNearbyApu(int, int, int, int) override;
		void SetGhostFighted(int, bool) override;
		void SetGhostMove(int) override;
		void SwitchGhostMode() override;*/

		void LoadLevelBitmap() override;
		void OnShow() override;
		void OnMove() override;

	private:
		/* Floor */
		CMovingBitmap turf;						// 草皮
		CMovingBitmap brick3;
		CMovingBitmap brick4;
		CMovingBitmap wall;
		/* Background */
		CMovingBitmap tree[20];
		CMovingBitmap grass[20];
		/* Ghost */
	};

	/* CGameMap_3 */
	class CGameMap_3 : public CGameMap {
	public:
		CGameMap_3();
		~CGameMap_3();

		/*int  GhostNearbyApu(int, int, int, int) override;
		void SetGhostFighted(int, bool) override;
		void SetGhostMove(int) override;
		void SwitchGhostMode() override;*/

		void LoadLevelBitmap() override;
		void OnShow() override;
		void OnMove() override;

	private:
		/* Floor */
		CMovingBitmap floor;						// 草皮
		CMovingBitmap brick3;
		CMovingBitmap brick4;
		CMovingBitmap wall;
		/* Background */
		CMovingBitmap tree[20];
		CMovingBitmap grass[20];
		CMovingBitmap tomb[10];
		/* Ghost */
	};
}

#endif