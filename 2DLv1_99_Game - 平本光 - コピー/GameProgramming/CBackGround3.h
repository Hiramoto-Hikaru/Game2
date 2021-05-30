#ifndef CBACKGROUND2_H
#define CBACKGROUND2_H

#include"CRectangle.h"
extern CTexture Texture5;
class CBackGround3 :public CRectangle {
public:

	CBackGround3() {
		w = 400;
		h = 360;
		mTag = EBACKGROUND3;
	}


	void Render() {

		CRectangle::Render(Texture5, 1, 222, 224, 1);

	}
};
#endif
