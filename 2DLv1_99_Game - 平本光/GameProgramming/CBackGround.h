
#ifndef CBACKGROUND_H
#define CBACKGROUND_H

#include"CRectangle.h"
extern CTexture Texture2;
class CBackGround :public CRectangle {
public:

	CBackGround() {
		w = 580;
		h = 355;
		mTag = EBACKGROUND;
	}


	void Render() {

		CRectangle::Render(Texture2, 0, 234, 178, 0);

	}
};
#endif