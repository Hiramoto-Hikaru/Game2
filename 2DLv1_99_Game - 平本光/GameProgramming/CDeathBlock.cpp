#include"CDeathBlock.h"
#include "CTexture.h"
#include "CSceneGame.h"


//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture Texture;

CDeathBlock::CDeathBlock()

{   //�G��Ǝ��ʃu���b�N
	//�񋓌^
	mTag = EDEATHBLOCK;
	w = 27;	//���ݒ�
	h = 27;	//�����ݒ�
	mEnabled = true;
}

void CDeathBlock::Update() {

}
void CDeathBlock::Render() {
	CRectangle::Render(Texture, 176,192, 46, 32);//(���A�E�A���A��)
}

void CDeathBlock::Collision(CRectangle* iiy, CRectangle* yyr) {
	if (iiy->mEnabled && yyr->mEnabled) {
		if (yyr->mTag == EPLAYER) {
			if (iiy->Collision(*yyr)) {
				CSceneGame::Life =0;
				CSceneGame::ItemPoint = 0;
				return;
			}



		}
	}
}