#ifndef CTROPHY_H
#define CTROPHY_H

#include"CRectangle.h"
class CTrophy :public CRectangle {
public:


	CTrophy();
	static int TrophyCount;
	void Collision(CRectangle * i, CRectangle * y);
	void Render();


};
#endif