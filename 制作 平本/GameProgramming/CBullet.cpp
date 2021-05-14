#include"CBullet.h"
#include"CTransform.h"
#include"CCollisionManager.h"
#define COLLISIONRANGE 30
CBullet::CBullet()
:mLife(50)
, mCollider4(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.1f)
{

}

void CBullet::Set(float w, float d) {
	//�X�P�[���ݒ�i�傫���j
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//�O�p�`�̒��_�ݒ�
	mT.SetVertex(CVector(w, 0.0f, 0.0f),CVector(-w, 0.0f, 0.0f),CVector(0.0f, 0.0f, -d));
	//�O�p�`�̖@���ݒ�
	mT.SetNormal(CVector(0.0f, 1.0f, 0.0f));

}
void CBullet::Update() {
	//mLife���O���傫���Ȃ�
	if (mLife-- > 0) {
		CTransform::Update();
		//�ʒu�X�V(�ړ���������j
		mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
	}
	else {
		mEnabled = false;
	}

}
void CBullet::Render() {
	//Deffuse���F�ݒ�
	float c[] = { 1.0f,1.0f,0.0f,1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//�O�p�`�`��
	//mMatrix�Ɠ����ꏊ�ɕ`��
	mT.Render(mMatrix);
	
}
//�R���C�_�̏Փˏ���
void CBullet::Collision(CCollider* m, CCollider* o) {
	//���肪�T�[�`�̂Ƃ��͖߂�
	if (o->mTag == CCollider::ESEARCH) {
		return;
	}
	
	//�R���C�_�̂���o���Փ˂��Ă��邩����
	if (CCollider::Collision(m, o)) {

		mEnabled = false;
	}
}
void CBullet::TaskCollision() {
	//�R���C�_�̗D��x�ύX
	mCollider4.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mCollider4, COLLISIONRANGE);
}