#ifndef CITEM_H
#define CITEM_H
#include "CRectangle.h"
#include"CPlayer.h"
#include"CSound.h"
class CItem :public CRectangle {
public:

	CSound Se3;
	CItem();
	
	void Render();
	bool Collision(const CRectangle& r);
	void Collision(CRectangle* i, CRectangle* y);
	void Update();
};

#endif