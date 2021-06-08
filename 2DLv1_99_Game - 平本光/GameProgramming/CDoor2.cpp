#include"CDoor2.h"
#include"CBoss.h"
#include"CTexture.h"
#include"CSceneGame.h"
#include"CRectangle.h"
extern CTexture Texture;
CDoor2::CDoor2() {
	w = 20;
	h = 30;
}
void CDoor2::Update() {
	if (CSceneGame::BossLife <= 0) {
		mEnabled = false;
	}
};
void CDoor2::Render() {
	CRectangle::Render(Texture, 112, 128, 31, 0);//(左、右、下、上)
};

