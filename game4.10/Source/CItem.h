#ifndef CITEM_H
#define CITEM_H

namespace game_framework {

	enum class ITEMS {
		Tree,			// ¾ð
		Grass,			// ¯óÂO
		Fragament,		// ¦a¹Ï¸H¤ù
		Tomb,			// ¹Ó¸O
		Trap			// ³´¨À¤â
	};

	class CItem {
	public:
		CItem();
		~CItem();
		/* Getter */
		int Width();
		int Height();
		int Top();
		int Left();
		/* Setter */
		void SetTopLeft(int, int);
		void SetFloor(int);
		/* Member Function */

		//
		//virtual void OnInit();
		//virtual void OnMove();
		//virtual void OnShow();
	private:
		POINT pos;
		CAnimation item;
	};

	class Tree {

	};

	class Grass {

	};

	class Fragament {

	};

	class Tomb {

	};

	class Trap {

	};
}

#endif