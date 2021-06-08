#ifndef CCOIN_H
#define CCOIN_H
#include"CRectangle.h"


class CCoin :public CRectangle {
public:

	CCoin();
	void Collision(CRectangle* i, CRectangle* y);
	void Render();
	int CoinAni;
};
#endif