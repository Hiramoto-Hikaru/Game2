#include "CMaterial.h"
//memset�̃C���N���[�h
#include <string.h>
#include"glut.h"


//�f�t�H���g�R���X�g���N�^
CMaterial::CMaterial()
:mVertexNum(0)
{
	//���O���O�Ŗ���
	//memset=�w�肵���G���A�ɒl���o�C�g�����ݒ�
	//memset(�G���A�A�l�A�o�C�g���j
	memset(mName, 0, sizeof(mName));
	memset(mDiffuse, 0, sizeof(mDiffuse));
	

}
void CMaterial::Enabled() {
	//�g���q�̐ݒ�
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	//�e�N�X�`������
	if (mTexture.mId) {
		//�e�N�X�`�����g�p�\�ɂ���
		glEnable(GL_TEXTURE_2D);
		//�e�N�X�`�����o�C���h����
		glBindTexture(GL_TEXTURE_2D, mTexture.mId);
		//�A���t�@�u�����h��L���ɂ���
		glEnable(GL_BLEND);
		//�u�����h���@���w��
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}
	//glMaterialfv(�ʁA��ށA�ݒ�l�j
	//�ʁFGL_FRONT�F�\�ʂ̂�
	//��ށFGL_DIFFUSE�F�g���q
	//�ݒ�l�Ffloat�^�̔z��[0]��[1]��[2]��[3]�A���t�@
}
void CMaterial::Disabled() {
	//�e�N�X�`������
	if (mTexture.mId)
	{
		//�A���t�@�t�����h�𖳌�
		glDisable(GL_BLEND);
		//�e�N�X�`���̃o�C���h������
		glBindTexture(GL_TEXTURE_2D, 0);
		//�e�N�X�`���𖳌��ɂ���
		glDisable(GL_TEXTURE_2D);

	}
}

