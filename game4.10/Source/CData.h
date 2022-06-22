#ifndef CDATA_H
#define CDATA_H

#define N 30
#define M 16
#define POS 2

namespace game_framework {

	int LEVEL1_MAP[N][M] = {
		  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,1,1,3,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,0,0,1,3,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,1,1,3,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,2,2,4,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,1,1,3,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,1,1,3,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
	};
	int LEVEL1_TREE[][POS] = {
		{-400,-70},
		{-200,-70},
		{0,   -70},
		{200, -70},
		{400, -70},
		{600, -70},
		{800, -70},
		{1000,-70},
		{1200,-70},
		{1400,-70},
		{-300, 30},
		{-100,30},
		{100, 30},
		{300, 30},
		{500, 30},
		{700, 30},
		{900, 30},
		{1100,30},
		{1300,30},
		{1500,30},
		{-300, 530},
		{-100, 530},
		{100,  530},
		{300,  530},
		{500,  580},
		{700,  580},
		{900,  530},
		{1100, 530},
		{1300, 530},
		{1500, 530},
		{-400, 680},
		{-200, 680},
		{0,    680},
		{200,  680},
		{400,  680},
		{600,  680},
		{800,  680},
		{1000, 680},
		{1200, 680},
		{1400, 680},
	};
	int LEVEL1_GRASS[][POS] = {
		{170, 350},
		{370, 350},
		{1200, 350},
		{770, 350},
		{970, 350},
		{70, 350},
		{270, 350},
		{1000, 350},
		{670, 350},
		{870, 350},
	};

	int LEVEL2_MAP[N][M] = {
		  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,1,1,3,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,1,2,4,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,2,1,1,3,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,1,1,1,3,0,0,0,0,0,0 },
		  { 0,0,0,0,0,2,1,2,1,3,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,3,0,2,4,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,3,0,1,3,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,1,1,2,4,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,2,2,4,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,1,1,3,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,1,2,4,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
	};
	int LEVEL2_TREE[][POS] = {
		{-400,-70},
		{-200,-70},
		{0,   -70},
		{200, -70},
		{400, -70},
		{600, -70},
		{800, -70},
		{1000,-70},
		{1200,-70},
		{1400,-70},
		{-300, 30},
		{-100,30},
		{100, 30},
		{300, 30},
		{500, 30},
		{700, 30},
		{900, 30},
		{1100,30},
		{1300,30},
		{1500,30},
		{-300, 530},
		{-100, 530},
		{100,  530},
		{300,  530},
		{500,  580},
		{700,  580},
		{900,  530},
		{1100, 530},
		{1300, 530},
		{1500, 530},
		{-400, 680},
		{-200, 680},
		{0,    680},
		{200,  680},
		{400,  680},
		{600,  680},
		{800,  680},
		{1000, 680},
		{1200, 680},
		{1400, 680},
	};
	
	int LEVEL3_MAP[N][M] = {
		  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,1,2,4,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,2,1,3,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,1,1,3,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,1,2,1,3,0,0,0,0,0,0 },
		  { 0,0,0,0,0,2,1,1,1,3,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,3,0,2,4,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,3,0,1,3,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,2,1,1,3,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,2,2,4,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,2,1,1,3,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,1,1,1,3,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0 },
		  { 0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0 },
	};
	int LEVEL3_TREE[][POS] = {
		{-300,30},
		{30,  30},
		{100, 30},
		{300, 30},
		{500, 30},
		{700, 30},
		{900, 30},
		{1100,30},
		{1300,30},
		{1500,30},
		{-400,-200},
		{-200,-200},
		{0,   -200},
		{200, -200},
		{400, -200},
		{600, -200},
		{800, -200},
		{1000,-200},
		{1200,-200},
		{1400,-200},
		{-300, 530},
		{-100, 530},
		{100,  530},
		{300,  530},
		{500,  580},
		{700,  580},
		{900,  530},
		{1100, 530},
		{1300, 530},
		{1500, 530},
		{-400, 680},
		{-200, 680},
		{0,    680},
		{200,  680},
		{400,  680},
		{600,  680},
		{800,  680},
		{1000, 680},
		{1200, 680},
		{1400, 680},
	};
}

#endif
