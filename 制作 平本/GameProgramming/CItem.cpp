
#include"CPlayer.h"
#include"CEffect.h"
#include"CCollisionManager.h"
#include"CItem.h"
#define OBJ "eyeball.obj"
#define MTL "eyeball.mtl"
int CItem::mItemCount = 0;
CModel CItem::mModel;//���f���f�[�^�쐬
CItem::CItem(const CVector& position, const CVector& rotation, const CVector& scale)
	: CItem()
{

	mPosition = position;
	mRotation = rotation;
	mScale = scale;
	mCollider.mTag = CCollider::EITEMCCOLLIDER;
	mTag = EITEM;
	CTransform::Update();//�s��̍X�V
	//�D��x���P�ɕύX����
	mPriority = 1;
	CTaskManager::Get()->Remove(this);//�폜����
	CTaskManager::Get()->Add(this);//�ǉ�����
}
CItem::CItem() 
	: mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 2.0f)
	
{
	//���f���̃|�C���^�ݒ�
	mpModel = &mModel;
	//���f���������Ƃ��͓ǂݍ���
	if (mModel.mTriangles.size() == 0) {
		mModel.Load(OBJ, MTL);
	}

}
void CItem::Update() {
mRotation.mY++;
}
void CItem::Collision(CCollider* m, CCollider* o) {
	switch (m->mType) {
	case CCollider::ESPHERE:
		if (o->mType == CCollider::ESPHERE) {
			if (o->mpParent->mTag == EPLAYER) {

				//�Փ˂��Ă���Ƃ�
				if (CCollider::Collision(m, o)) {
					mItemCount = 600;
					mEnabled = false;
				}

			}
		}
	}
	
}
void CItem::TaskCollision() {
	//�R���C�_�̗D��x�ύX
	mCollider.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}
