#ifndef CDEATHBLOCK_H
#define CDEATHBLOCK_H
#include"CRectangle.h"

class CDeathBlock :public CRectangle {
public:

	CDeathBlock();

	void Update();
	void Render();
	
	void Collision(CRectangle* iiy, CRectangle* yyr);
};
#endif
