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
		CGameMap();
		~CGameMap();

		int *GetMap();
		POINT GetPieceXY();
		POINT GetSXY();

		void SetSX(int x);
		void SetSY(int y);
		int ScreenX(int x);
		int ScreenY(int y);
		POINT ScreenXY(POINT xy);

		bool IsEmpty(int x, int y);
		bool HasPiece(int x1, int y1, int x2, int y2);

		virtual void LoadBitmap() = 0;
		virtual void OnShow() = 0;
		virtual void OnMove() = 0;

	protected:
		CMovingBitmap brick1;
		CMovingBitmap brick2;
		CMovingBitmap brick3;
		CMovingBitmap brick4;
		CMovingBitmap piece;
		
		int map[30][30];						// �a��
		int sx, sy;								// �ù����W���y��
		const int X, Y;							// �b�a�ϤW���y��
		const int MW, MH;						// �C�j���e�j�p
	};

	/* CGameMap_1 */
	class CGameMap_1 : public CGameMap {
	public:
		CGameMap_1();
		~CGameMap_1();

		void LoadBitmap() override;
		void OnShow() override;
		void OnMove() override;

	private:
		CMovingBitmap turf;
		CMovingBitmap brick3;
		CMovingBitmap brick4;
		CMovingBitmap explination;
		CMovingBitmap tree[40];
		CMovingBitmap grass[10];

	};

	/* CGameMap_2 */
	class CGameMap_2 : public CGameMap {
	public:
		CGameMap_2();
		~CGameMap_2();

		void LoadBitmap() override;
		void OnShow() override;
		void OnMove() override;

	private:
		CMovingBitmap turf;
		CMovingBitmap brick3;
		CMovingBitmap brick4;
		CMovingBitmap wall;
		CMovingBitmap tree[20];
		CMovingBitmap grass[20];
	};

	/* CGameMap_3 */
	class CGameMap_3 : public CGameMap {
	public:
		CGameMap_3();
		~CGameMap_3();

		void LoadBitmap() override;
		void OnShow() override;
		void OnMove() override;

	private:
		CMovingBitmap floor;
		CMovingBitmap brick3;
		CMovingBitmap brick4;
		CMovingBitmap wall;
		CMovingBitmap tree[20];
		CMovingBitmap grass[20];
		CMovingBitmap tomb[10];
	};
}

#endif