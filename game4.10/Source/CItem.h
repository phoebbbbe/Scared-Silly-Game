#ifndef CITEM_H
#define CITEM_H

namespace game_framework {

	enum class ITEMS {
		Tree,			// ��
		Grass,			// ���O
		Fragament,		// �a�ϸH��
		Tomb,			// �ӸO
		Trap			// ������
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