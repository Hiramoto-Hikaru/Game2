#include"CButton.h"
#include"CTexture.h"
#include"CSceneGame.h"
#include"CBoss.h"
#include"CRectangle.h"

#define ANICOUNT 15
extern CTexture Texture;

int CButton::bcount = 0;

CButton::CButton() 

{
	//列挙型
	mTag = EBUTTON;
	w = 30;
	h = 30;
}
void CButton::Update() {

}
void CButton::Collision(CRectangle* i, CRectangle* y) {
	if (y->mTag == EPLAYER) {
		int mx, my;
		if (CRectangle::Collision(y, &mx, &my)) {
			if (abs(mx) < abs(my))
			{
				
			}
			else {
				CSceneGame::BossLife -=20;
				mEnabled = false;
				
			}
		}
	}
}
void CButton::Render() {
	bcount++;
	bcount  %= ANICOUNT;
	if (bcount > ANICOUNT / 2) {
		CRectangle::Render(Texture, 145, 160, 68, 54);//(左、右、下、上)
	}
	else {
		CRectangle::Render(Texture, 160, 175, 68, 54);//(左、右、下、上)
	}
}