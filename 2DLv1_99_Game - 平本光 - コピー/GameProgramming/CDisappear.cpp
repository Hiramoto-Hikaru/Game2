#include"CDisappear.h"
#include"CTexture.h"
extern CTexture Texture;
#define COUNT 3000
int CDisappear::DisappearCount = 0;
CDisappear::CDisappear()

{
	//�񋓌^
	mTag = EDISAPPEAR;
	w = 30;
	h = 15;

}
void CDisappear::Render() {
	DisappearCount++;//�P�����Z�����
	DisappearCount %= COUNT;

	if (DisappearCount < COUNT/2 )/*	COUNT(100)���Q�Ŋ��������̂��
								�������Ƃ�*/
	{

		CRectangle::Render(Texture, 96, 112, 47, 31);//(���A�E�A���A��)
	}
	
}
