#ifndef CITEM_H
#define CITEM_H

namespace game_framework {

	enum class ITEMS {
		Button,			// ����
		MapPiece,		// �a��
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
		virtual void OnInit() = 0;
		virtual void OnMove() = 0;
		virtual void OnShow() = 0;
	private:
		POINT pos;
		CAnimation item;
	};

	class Button {

	};

	class MapPiece {

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