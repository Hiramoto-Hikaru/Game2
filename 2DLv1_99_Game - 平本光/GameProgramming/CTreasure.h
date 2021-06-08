#ifndef CHEART_H
#define CHEART_H
#include "CTexture.h"
#include"CRectangle.h"
#include"CSceneGame.h"
class CTreasure : public CRectangle {
public:
	CTreasure();
	int Treasure;
	void Update();
	void Render();

	void Collision(CRectangle* i, CRectangle* y);
};

#endif