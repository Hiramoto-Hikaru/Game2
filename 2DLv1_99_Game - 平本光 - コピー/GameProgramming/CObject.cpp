#include"CObject.h"
#include"CTexture.h"
#include"CSceneGame.h"
#include"CRectangle.h"

extern CTexture Texture;
CObject::CObject() {
	w = 30;
	h = 30;
	mTag = EOBJECT;
}

void CObject::Render() {
	CRectangle::Render(Texture, 196,224,68, 49);//(左、右、下、上)
};
