#include"CTrophy.h"
#include"CSceneGame.h"
#include"CRectangle.h"
#include"CPLayer.h"
#include"CTexture.h"
extern CTexture Texture;
int CTrophy::TrophyCount = 0;
CTrophy::CTrophy() {
	
		//列挙型
		mTag = ETROPHY;
		w = 30;
		h = 30;
	
}
void CTrophy::Render() {
	CRectangle::Render(Texture, 148, 162, 90, 75);//(左、右、下、上)
}
void CTrophy::Collision(CRectangle* i, CRectangle* y) {
	if (y->mTag == EPLAYER) {

		int mx, my;
		if (CRectangle::Collision(y, &mx, &my)) {
			mEnabled = false;
			CTrophy::TrophyCount += 1;
			CSceneGame::Treasure += 4;
			CSceneGame::SCore += 10000;

		}
	}
}