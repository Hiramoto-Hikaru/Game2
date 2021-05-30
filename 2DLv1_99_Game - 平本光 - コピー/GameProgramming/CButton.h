#ifndef CBUTTON_H
#define CBUTTON_H
#include"CSceneGame.h"
#include"CRectangle.h"

class CButton :public CRectangle {
public:
	CButton();
	void Update();
	void Collision(CRectangle* i, CRectangle* y);
	void Render();
	static int bcount;
	
};
#endif