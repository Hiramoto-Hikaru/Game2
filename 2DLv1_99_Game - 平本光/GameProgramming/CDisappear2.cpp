#include"CDisappear2.h"
#include"CTexture.h"
#include"CDisappear.h"
extern CTexture Texture;
#define COUNT2 2000


CDisappear2::CDisappear2()
	
{
	//�񋓌^
	mTag = EDISAPPEAR2;
	w = 30;
	h = 15;

}
void CDisappear2::Render() {
	CDisappear::DisappearCount++;//�P�����Z�����
	CDisappear::DisappearCount %= COUNT2;

	if (CDisappear::DisappearCount < COUNT2/2)/*	COUNT(100)���Q�Ŋ��������̂��
								�������Ƃ�*/
	{

		CRectangle::Render(Texture, 96, 112, 47, 31);//(���A�E�A���A��)
	}

}