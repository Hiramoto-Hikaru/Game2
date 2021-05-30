#include"CRectangle.h"
#include"CTexture.h"
#include"CBackGround.h"
extern CTexture Texture2;

CBackGround::CBackGround()

{
	mTag = EBACKGROUND;
	w = 300;
	h = 300;
}
void CBackGround::Render() {
	CRectangle::Render(Texture2, 0, 234, 178, 0);
}