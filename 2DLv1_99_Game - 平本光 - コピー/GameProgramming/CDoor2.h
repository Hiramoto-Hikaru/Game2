#ifndef CDOOR2_H
#define CDOOR2_H
#include"CRectangle.h"
#include"CBoss.h"

class CDoor2 :public CRectangle {
public:
	CDoor2();

	void Update();
	void Render();


};

#endif
