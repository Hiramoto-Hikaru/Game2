#include"CRectangle.h"
#include"CTreasure.h"
#include"CTexture.h"
#include"CPlayer.h"
#include"CSceneGame.h"
extern CTexture Texture;
CTreasure::CTreasure()
{
	mTag = ETREASURE;
	w = 15;
	h = 15;
}

void CTreasure::Update() {

}
void CTreasure::Render() {
	CRectangle::Render(Texture, 226, 239, 33, 15);
}
void CTreasure::Collision(CRectangle* si, CRectangle* sy) {
	if (CSceneGame::Life > 0) {
		if (sy->mTag == EPLAYER) {
				int mx, my;
				if (CRectangle::Collision(sy, &mx, &my)) {
					mEnabled = false;
					CSceneGame::Treasure += 1;
					CSceneGame::SCore += 100;
			
				}
			}
	}
	
}


