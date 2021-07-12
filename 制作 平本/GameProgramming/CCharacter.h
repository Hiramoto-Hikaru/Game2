#ifndef CCHARACTER_H
#define CCHARACTER_H
#include"CTask.h"

//�R���C�_�N���X�̐錾
	class CCollider;
//�ϊ��s��N���X�̃C���N���[�h
#include"CTransform.h"
//���f���N���X�̃C���N���[�h
#include"CModel.h"
/*�L�����N�^�[�N���X
�Q�[���L�����N�^�[�̊�{�I�ȋ@�\�ƒ�`����
*/
//.���g���ĂQ�̐e�N���X��ǉ�
class CCharacter :public CTransform,public CTask {
public:
	//�R���X�g���N�^
	CCharacter();

	CModel* mpModel;//���f���̃|�C���^

	enum ETag {
		EZERO,//�����l
		EPLAYER,//�v���C���[
		EENEMY,//�G
		
		EENEMY2,
		
		EBULLETPLAYER,//�v���C���[�̒e
		EBULLETENEMY,//�G�̒e
	};
	ETag mTag;
	
	//�`�揈��
	void Render();
	//�f�X�g���N�^
	~CCharacter();
	
	//�Փˏ���
	virtual void Collision(CCollider* m, CCollider* o) {}
};
#endif