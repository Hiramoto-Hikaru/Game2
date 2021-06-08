#include"CDisappear.h"
#include"CTexture.h"
extern CTexture Texture;
#define COUNT 3000
int CDisappear::DisappearCount = 0;
CDisappear::CDisappear()

{
	//—ñ‹“Œ^
	mTag = EDISAPPEAR;
	w = 30;
	h = 15;

}
void CDisappear::Render() {
	DisappearCount++;//‚P‚¸‚Â‰ÁŽZ‚³‚ê‚é
	DisappearCount %= COUNT;

	if (DisappearCount < COUNT/2 )/*	COUNT(100)‚ð‚Q‚ÅŠ„‚Á‚½‚à‚Ì‚æ‚è
								¬‚³‚¢‚Æ‚«*/
	{

		CRectangle::Render(Texture, 96, 112, 47, 31);//(¶A‰EA‰ºAã)
	}
	
}
