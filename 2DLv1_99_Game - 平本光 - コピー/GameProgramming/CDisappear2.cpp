#include"CDisappear2.h"
#include"CTexture.h"
#include"CDisappear.h"
extern CTexture Texture;
#define COUNT2 2000


CDisappear2::CDisappear2()
	
{
	//—ñ‹“Œ^
	mTag = EDISAPPEAR2;
	w = 30;
	h = 15;

}
void CDisappear2::Render() {
	CDisappear::DisappearCount++;//‚P‚¸‚Â‰ÁŽZ‚³‚ê‚é
	CDisappear::DisappearCount %= COUNT2;

	if (CDisappear::DisappearCount < COUNT2/2)/*	COUNT(100)‚ð‚Q‚ÅŠ„‚Á‚½‚à‚Ì‚æ‚è
								¬‚³‚¢‚Æ‚«*/
	{

		CRectangle::Render(Texture, 96, 112, 47, 31);//(¶A‰EA‰ºAã)
	}

}