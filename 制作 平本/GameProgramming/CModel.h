#ifndef CMODEL_H
#define CMODEL_H
#include"CMaterial.h"
/*
���f���N���X
���f���f�[�^�̓��͂�\��
*/
#include<vector>
#include"CTriangle.h"
class CModel {
public:
	//���f���t�@�C���̓���
	//Load �i���f���t�@�C�����@�}�e���A���t�@�C�����j
	void Load(char* obj, char* mtl);
	//�O�p�`�̉ϒ��z��
	std::vector<CTriangle>mTriangles;
	std::vector<CMaterial*>mpMaterials;
	//�f�X�g���N�^�A�A�A�C���X�^���X���폜�����Ǝ��s
	~CModel();
	//���_�z��  �i�|�C���^�ϐ��j
	float *mpVertex;//���_���W	
	float *mpNormal;//�@��
	float *mpTextureCoord;//�e�N�X�`���}�b�s���O
	//�f�t�H���g�R���X�g���N�^
	CModel();
	void Render(const CMatrix& m);
};
#endif
