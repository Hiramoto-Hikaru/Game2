#include"CDoor.h"
#include"CBoss.h"
#include"CTexture.h"
#include"CSceneGame.h"
#include"CRectangle.h"
extern CTexture Texture;
CDoor::CDoor() {
	w = 20;
	h = 30;
	mEnabled = true;
}
void CDoor::Update(){
	if (CSceneGame::Treasure == 3) {
		mEnabled = false;
	}
};
void CDoor::Render() {
	CRectangle::Render(Texture, 112, 128, 31, 0);//(左、右、下、上)
};

