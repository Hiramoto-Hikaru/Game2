#ifndef CBILLBOARD_H
#define CBILLBOARD_H
#include"CCharacter.h"
/*�r���{�[�h�N���X
�i��ɃJ�����̕����������l�p�`�j*/
class CBillBoard :public CCharacter {
public:
	//�O�p�`�Q��
	CTriangle mT[2];
	//�}�e���A��
	CMaterial mMaterial;
	//�R���X�g���N�^
	CBillBoard();
	//CBillboard(�ʒu�A���A�����j
	CBillBoard(CVector pos, float w, float h);
	//�ʒu�Ƒ傫���̐ݒ�
	//Set(�ʒu�A���A�����j
	void Set(CVector pos, float w, float h);
	//�X�V
	void Update();
	//�`��
	void Render();
	void Render(CMaterial* mpMaterial);
};
#endif