#ifndef CDOOR_H
#define CDOOR_H
#include"CRectangle.h"
#include"CBoss.h"

class CDoor :public CRectangle {
public:
	CDoor();

	void Update();
	void Render();

	
};

#endif