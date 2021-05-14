#ifndef CMATERIAL_H
#define CMATERIAL_H
#include "CTexture.h"
/*
�}�e���A���N���X
�}�e���A���̃f�[�^���g��
*/
class CMaterial {
public:
	//�}�e���A����
	char mName[64];
	//�g�����̐FR,G,B,A
	float mDiffuse[4];
	//�e�N�X�`��
	CTexture mTexture;
	//�}�e���A���𖳌��ɂ���
	void Disabled();
	//�f�t�H���g�R���X�g���N�^
	CMaterial();
	//�}�e���A����L���ɂ���
	void Enabled();
	//�}�e���A�����Ƃ̒��_��(�|�C���^�j
	int mVertexNum;
};



#endif
