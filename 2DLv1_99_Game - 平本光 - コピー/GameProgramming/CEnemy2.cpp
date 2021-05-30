#include"CEnemy2.h"
#include"CRectangle.h"
#include "CTexture.h"
#include"CSceneGame.h"

extern CTexture Texture;
CEnemy2::CEnemy2()
	: mFx(1.0f), 
	  mFy(0.0f)
{
	//�񋓌^
	mTag = EENEMY2;
	w = 23;
	h = 20;
}

void CEnemy2::Update() {  //�N���{�[
	//mEnabled��false�Ȃ�߂�
	if (!mEnabled) return;
	x -= mFx;
}
void CEnemy2::Render() {

	if (mFx >= 0) //�������ɐi��ł����
	{
		CRectangle::Render(Texture, 122, 104, 178, 159);//(���A�E�A���A��)

	}


	else
		//-x�����ɐi��ł����
	{
		CRectangle::Render(Texture, 104, 122, 178, 159);//(���A�E�A���A��)
	}
}
void CEnemy2::Collision(CRectangle* i, CRectangle* y) {
	//�e��Collision���\�b�h���Ăяo��
	if (CRectangle::Collision(*y)) {
		switch (y->mTag) {
		case EBLOCK:
			//�Փ˂��Ă���Δ��]
			mFx *= -1;
			mFy *= -1;

			break;
		case EPLAYERBULLET:
			

			//�v���C���[�̒e�ɓ�����ƁA�����ɂ���
			mEnabled = false;
			CSceneGame::SCore += 10;
		    
			break;
			
		case EPLAYER:
         
		      	mEnabled = false;
				
                 CSceneGame::Life -= 1;
                  CSceneGame::ItemPoint -= 1;
				
				
				
			
			
				break;

			
		}

	}
	

}
