#ifndef CPLAYER_H
#define CPLAYER_H
#include "CRectangle.h"
#include"CSound.h"
class CPlayer : public CRectangle {
public:
	static CPlayer* spInstance;
	//�ϐ��̒�`
	int mFx, mFy;
	static int DamageCount;//���C�t������Ƒ�����
	int FireCount;
	
     CPlayer();//�R���X�g���N�^
	void Update();
		//�X�V����
	void Render();//�`�揈��
	int mJump;//�W�����v�t���O
	int mVj;//�W�����v�p���x
	int mDj;//�m�b�N�o�b�N
	int mjumpcount;//�W�����v�ł���悤�ɂ���
	int mWorkCount;//���X�ɑ��x�����Z����
	int Count;// DamageCount���ւ炷�^�C�~���O�����߂�
	CSound Se;
	CSound Se2;
	CSound Se3;
	//�Փˏ���
	void Collision(CRectangle *i, CRectangle *y);
	int mAniCount;//�A�j���[�V�����p�J�E���^
	
};

#endif
