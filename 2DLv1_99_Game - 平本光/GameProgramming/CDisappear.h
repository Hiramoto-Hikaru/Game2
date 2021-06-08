#ifndef DISAPPEAR_H
#define DISAPPEAR_H
#include"CRectangle.h"

class CDisappear :public CRectangle {
public:
	static int DisappearCount;
	CDisappear();
	void Render();

};


#endif
