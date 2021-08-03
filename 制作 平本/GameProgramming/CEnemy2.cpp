#include"CEnemy2.h"
#include"CEffect.h"
#include"CCollisionManager.h"
#include"CBullet.h"
#include"CSceneGame.h"
#include"CUtil.h"
#include"CText.h"
#define OBJ "mini.obj"//���f���̃t�@�C��
#define MTL "mini.mtl"//���f���̃}�e���A���t�@�C��
#define HP 3
#define VELOCITY 0.5f //�}�N��
#define JUMP 7.0f
#define G 1.0f
CModel CEnemy2::mModel;//���f���f�[�^�쐬
//�f�t�H���g�R���X�g���N�^
CEnemy2::CEnemy2()
//�R���C�_�̐ݒ�
	:mCollider(this,&mMatrix,CVector(-0.5f,0.0f,-1.0f),2.0f)

	,mColSearch(this,&mMatrix,CVector(0.0f,0.0f,100.0f),200.0f)
	,mpPlayer(0)
	,mHp(HP)
	,mJump(0)
	,mJump2(0)
	, mEnemyDamage(60)
{
	mTag = EENEMY2;
	//���f���������Ƃ��͓ǂݍ���
	if (mModel.mTriangles.size() == 0) {
		mModel.Load(OBJ, MTL);
	}
	//���f���̃|�C���^�ݒ�
	mpModel = &mModel;
	mTag = EENEMY2;
	mColSearch.mTag = CCollider::ESEARCH;//�^�O�ݒ�
	mCollider.mTag = CCollider::EENEMY2COLLIDER;
}

//CEnemy(�ʒu�A��]�A�g�k�j
CEnemy2::CEnemy2(const CVector& position, const CVector& rotation, const CVector& scale)
:CEnemy2()
{
	//�ʒu�A��]�A�g�k��ݒ肷��
	mPosition = position;//�ʒu�̐ݒ�
	mRotation = rotation;//��]�̐ݒ�
	mScale = scale;//�g�k�̐ݒ�
	CTransform::Update();//�s��̍X�V
	//�ڕW�n�_�̐ݒ�
	mPoint =mPosition + CVector(0.0f, 0.0f, 100.0f) * mMatrixRotate;
	//�D��x���P�ɕύX����
	mPriority = 1;
	CTaskManager::Get()->Remove(this);//�폜����
	CTaskManager::Get()->Add(this);//�ǉ�����
}
//�X�V����
void CEnemy2::Update() {
	//if(mPosition.mY<=mpPlayer->mPosition.mY)
	//�������iX���j�̃x�N�g�������߂�
	CVector vx = CVector(1.0f, 0.0f, 0.0f)*mMatrixRotate;
	//������iY���j�̃x�N�g�������߂�
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	//�O�����iZ���j�̃x�N�g�������߂�
	CVector vz = CVector(0.0f, 0.0f, 5.0f) * mMatrixRotate;
	//�ڕW�n�_�܂ł̃x�N�g�������߂�
	CVector vp = mPoint - mPosition;
	//���x�N�g���Ƃ̓��ς����߂�
	float dx = vp.Dot(vx);
	//��x�N�g���Ƃ̓��ς����߂�
	float dy = vp.Dot(vy);
	//�O�x�N�g���Ƃ̓��ς����߂�
	float dz = vp.Dot(vz);
	float margin = 0.1f;
	//���E�����։�]
	if (dx > margin) {
		mRotation.mY += 1.0f;//���։�]
	}
		else if (dx < -margin) {
		mRotation.mY -= 1.0f;//�E�։�]
        }
	//�ړ�����
	mPosition = mPosition + CVector(0.0f, 0.0f, VELOCITY) * mMatrixRotate;
	CTransform::Update();//�s��X�V
	int r = rand() % 60; //rand()�͐����̗�����Ԃ�
	          
						 //%180�͂P�W�O�Ŋ������]������߂�
	if (r == 0) {
		if (mpPlayer) {
			mPoint = mpPlayer->mPosition;

		}
		else {
			mPoint = mPoint * CMatrix().RotateY(80);
		}
	}
	mpPlayer = 0;
	if (mHp <= 0) {
		mHp--;
		//15�t���[�����ƂɃG�t�F�N�g
		if (mHp % 15 == 0) {
            //�G�t�F�N�g����
			new CEffect(mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		}
		CTransform::Update();
	}
	if (mHp <= -100) {
		mEnabled = false;
		CSceneGame::mEnemyCount -= 1;
	}
	if (mJump > 0) {
     mPosition.mZ -= mJump;
	 mJump--;
	}
	if (mJump2 > 0) {
		mPosition.mY += mJump;
		mJump2--;
	}
	if (mPosition.mY > 2.0f) {
      mPosition.mY -= G;
	}
}
//Collision(�R���C�_�P�C�R���C�_�Q�C�j
void CEnemy2::Collision(CCollider* m, CCollider* o) {
	//�������T�[�`�p�̂Ƃ�
	if (m->mTag == CCollider::ESEARCH) {
		//���肪�e�R���C�_�̂Ƃ�
		if (o->mType == CCollider::ESPHERE) {
			//���肪�v���C���[�̂Ƃ��A
			if (o->mpParent->mTag == EPLAYER) {
				//�Փ˂��Ă���Ƃ�
				if (CCollider::Collision(m, o)) {
					//�v���C���[�̃|�C���^�ݒ�
					mpPlayer = o->mpParent;
				}
			}
		}
		return;
	}
	if (m->mType == CCollider::ESPHERE) {
		if (o->mType == CCollider::ESPHERE) {
			//���肪����̂Ƃ��A
			if (o->mpParent->mTag == EWEAPON) {
				//�Փ˂��Ă���Ƃ�
				if (CCollider::Collision(m, o)) {
					//15�t���[�����ƂɃG�t�F�N�g
					if (mEnemyDamage % 10 == 0) {
						new CEffect(o->mpParent->mPosition, 3.0f, 3.0f, "Attack.tga", 2, 6, 2);
					}
					mJump = JUMP;
					mJump2 = JUMP;
					mHp--;
				}
			}
		}
		if (o->mType == CCollider::ETRIANGLE) {
            CVector adjust;//�����l
			//�O�p�R���C�_�Ƌ��R���C�_�̏Փ˔���
			//adjust�A�A�A�����l
			if (CCollider::CollisionTriangleSphere(o, m, &adjust))
			{
				//�Փ˂��Ȃ��ʒu�܂Ŗ߂�
				mPosition = mPosition + adjust;
			}
		}
		return;
	}
}
void CEnemy2::TaskCollision() {
	mColSearch.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mColSearch, COLLISIONRANGE);
	//�R���C�_�̗D��x�ύX
	mCollider.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}
