#ifndef CLEVEL_H
#define CLEVEL_H

namespace game_framework {
	enum class LEVELS {
		LEVEL_1,
		LEVEL_2,
		LEVEL_3
	};

	class CLevel
	{
	public:
		/* Constructor */
		CLevel();
		//CLevel(int);
		~CLevel();

		/* Getter */

		/* Setter */

		/* Member Function */
		void clean();
		//
		void OnInit(int);
		void OnMove();
		void OnShow();
	protected:
	private:
		int level;

		/*CApu apu;
		CGameMap map;
		vector<CGhost*> balloon;*/

	};
}
#endif
