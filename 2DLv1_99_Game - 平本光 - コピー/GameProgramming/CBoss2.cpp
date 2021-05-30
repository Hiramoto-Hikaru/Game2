#include"CBoss2.h"
#include"CTexture.h"
#define G  1//重力
extern CTexture Texture;

CBoss2::CBoss2()
: mFireCount(0)
, mVj(0)
, mJump(0)//０はジャンプ可能
, bosscount(0)
,mFx(0)
,mFy(0)
{
	//列挙型
	mTag = EBOSS2;
	w = 20;
	h = 20;

}
void CBoss2::Update() {

}
void CBoss2::Render() {

}
void CBoss2::Collision(CRectangle* i, CRectangle* y) {

}

