#include"CDisappear.h"
#include"CTexture.h"
extern CTexture Texture;
#define COUNT 3000
int CDisappear::DisappearCount = 0;
CDisappear::CDisappear()

{
	//列挙型
	mTag = EDISAPPEAR;
	w = 30;
	h = 15;

}
void CDisappear::Render() {
	DisappearCount++;//１ずつ加算される
	DisappearCount %= COUNT;

	if (DisappearCount < COUNT/2 )/*	COUNT(100)を２で割ったものより
								小さいとき*/
	{

		CRectangle::Render(Texture, 96, 112, 47, 31);//(左、右、下、上)
	}
	
}
