#ifndef CCOLLIDERMESH_H
#define CCOLLIDERMESH_H

#include "CModel.h"
#include"CColliderTriangle.h"

class CColliderMesh {
public:
	//�O�p�R���C�_�̔z��쐬
	CColliderTriangle* mpColliderTriangles;
	//�R���X�g���N�^
	CColliderMesh();
	//�f�X�g���N�^
	~CColliderMesh();
	//Set�i�e�A�e�s��A���f���j
	//���f������O�p�R���C�_�̍쐬
	//parent,,,�e�̃C���X�^���X
	//matrix,,,	�R���C�_�̊g�k�A��]�A�ړ����s�������s��
	//model,,,�R���C�_�𐶐����錳�ƂȂ郂�f��
	void Set(CCharacter* parent, CMatrix* matrix, CModel* model);


};
#endif
