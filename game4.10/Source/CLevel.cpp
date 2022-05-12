#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CLevel.h"
#include "CGameMap.h"

namespace game_framework {
	/* Constructor */
	CLevel::CLevel() {

	}

	CLevel::~CLevel() {

	}

	/* Getter */

	/* Setter */

	/* Member Function */
	void CLevel::clean() {

	}
	//
	void CLevel::OnInit(int l) {
		level = l;

		clean();

		switch (level) {
			// Level 1
			case static_cast<int>(LEVELS::LEVEL_1) :
				// Backgrount
				// Item
				// Ghost
				break;
				case static_cast<int>(LEVELS::LEVEL_2) :
					// Background
					// Item
					// Ghost
					break;
					case static_cast<int>(LEVELS::LEVEL_3) :
						// Background
						// Item
						// Ghost
						break;
		}
	}

	void CLevel::OnMove() {

	}
	void CLevel::OnShow() {

	}
}