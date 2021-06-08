#ifndef CBACKGROUND2_H
#define CBACKGROUND2_H

#include"CRectangle.h"
extern CTexture Texture4;
class CBackGround2 :public CRectangle {
public:

	CBackGround2() {
		w = 305;
		h = 305;
		mTag = EBACKGROUND2;
	}


	void Render() {

		CRectangle::Render(Texture4, 15, 300, 303, 15);

	}
};
#endif
