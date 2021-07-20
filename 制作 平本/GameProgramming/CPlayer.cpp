//�v���C���[�N���X

#include"CPlayer.h"


#include"CKey.h"
#include"CBullet.h"
#include"CTaskManager.h"
#include"CTransform.h"
#include"CColliderLine.h"
#include"CTask.h"
#include"CUtil.h"
#include"CText.h"
//#include"CWeapon.h"
CMatrix Matrix;
int CPlayer::mAction1 = 100;//�P��ڂ̍U���̕\������
int CPlayer::mAction2 = 100;//�Q��ڂ̍U���̕\������
int CPlayer::mAction3 = 100;//�R��ڂ̍U���̕\������
int CPlayer::mSpaceCount1 = 0;
int CPlayer::mSpaceCount2 = 0;
int CPlayer::mSpaceCount3 = 0;
int CPlayer::mStamina = 400;
int CPlayer::mWeaponCount = 0;
CPlayer::CPlayer()
//�����R���C�_�̐ݒ�i�e�A�e�s��A���_�P�A���_�Q�j
	:mLine(this, &mMatrix, CVector(0.0f, 9.0f, -7.0f), CVector(0.0f, 9.0f, 10.0f)) //�O��̐����R���C�_
	, mLine2(this, &mMatrix, CVector(0.0f, 12.0f, -4.0f), CVector(0.0f, 6.0f, -4.0f))  //�㉺�̐����R���C�_
	, mLine3(this, &mMatrix, CVector(7.0f, 9.0f, -4.0f), CVector(-7.0f, 9.0f, -4.0f))  //���E�̐����R���C�_
	,mCollider(this,&mMatrix,CVector(0.0f,9.0f,0.0f),1.0f)
	, mRotationCountFirst(1)
	,mRotationCount(0)
	,mRotationCount2(0)
	,mRotationCount3(0)
	,mRotationCount4(0)
	, mColliderCount(0)
	,mChild(this)
{
//�e�N�X�`���t�@�C���̓ǂݍ���(�P�s�U�S��j
mText.LoadTexture("FontWhite.tga", 1, 64);
mCollider.mTag = CCollider::EPLAYER;//�^�O�̐ݒ�
mTag = EPLAYER;
mModelW.Load("Weapon.obj", "Weapon.mtl");
} 
void CPlayer::Update() {
	//��ɕ���\��
	if (CKey::Push('U')) {
		if (mSpaceCount1 >= 0 || mSpaceCount2 >= 0 || mSpaceCount3 >= 0) {
			//new CWeapon(&mModelW, mPosition, CVector(), CVector(0.7f, 0.7f, 0.7f));

		}
	}
	//�X�y�[�X�L�[���͂ŕ���
	if (CKey::Once(VK_SPACE)) {
		//�ŏ��̍U��
 		if (mSpaceCount1 <= 0&&mAction3>=10) {
			mSpaceCount1 = 60;
			mAction1 = 0;

			mSpaceCount3 = 0;
			mAction3 = 100;
			//new CWeapon(&mModelW, mPosition, CVector(), CVector(0.7f, 0.7f, 0.7f));
		}
		//�Q��ڂ̍U��
		else if (mSpaceCount2 <=0 && mAction1 >= 10) {
			if (mAction1 < 100) {
				mSpaceCount2 = 100;
	     		mAction2 =0;

				mAction1 = 60;
				mSpaceCount1 = 0;
				//new CWeapon(&mModelW, mPosition, CVector(), CVector(0.7f, 0.7f, 0.7f));
			}
			
		}
		//�R��ڂ̍U��
		else if (mSpaceCount3 <=0 &&  mAction2 >=10) {
			if (mAction2 < 100) {
				mSpaceCount3 = 60;
  				mAction3 = 0;

				mAction2 = 100;
				mSpaceCount2 = 0;
				//new CWeapon(&mModelW, mPosition, CVector(), CVector(0.7f, 0.7f, 0.7f));
			}
		}
	}
	//����̕\������
	if (mSpaceCount1 > 0) {
			mSpaceCount1--;
		}
		if (mSpaceCount2 > 0) {
			mSpaceCount2--;
		}
		if (mSpaceCount3 > 0) {
			mSpaceCount3--;
		}
		//�X�^�~�i��
	if (mStamina <= 400) {
    mStamina++;
	}
	if (mAction1 >= 60 && mAction2 >=60 && mAction3 >=60) {
		//�O�i
		if (CKey::Push('I')) {
			mWeaponCount = 0;
			if (mRotationCount <= 0) {
				mRotationCount += 1;
				if (mRotationCountFirst > 0) {
					mRotationCountFirst--;

				}
			}
			else if (mRotationCount2 > 0) {//�E�������Ă����Ƃ�
				mRotation.mY += 90;
				mRotationCount2 -= 1;
			}
			else if (mRotationCount3 > 0) {//���������Ă����Ƃ�
				mRotation.mY += 180;
				mRotationCount3 -= 1;
			}
			else if (mRotationCount4 > 0) {//���������Ă����Ƃ�
				mRotation.mY -= 90;
				mRotationCount4 -= 1;
			}
			if (CKey::Push('C')) {
				if (mStamina > 0) {

					//X��������-�P�i�񂾒l����]�ړ�������
					mPosition = CVector(0.0f, 0.0f, 4.0f) * mMatrix;
					mStamina -= 2;
				}
				else if (mStamina <= 2 || mStamina >= 0) {
					//X��������-�P�i�񂾒l����]�ړ�������
					mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
					mStamina -= 2;
				}
			}
			else {
				//X��������-�P�i�񂾒l����]�ړ�������
				mPosition = CVector(0.0f, 0.0f, 2.0f) * mMatrix;
			}


		}
		//���
		else if (CKey::Push('K')) {
			mWeaponCount = 1;
			if (mRotationCount3 <= 0) {
				mRotationCount3 += 1;
				if (mRotationCountFirst > 0) {
					mRotation.mY += 180;
					mRotationCountFirst--;
				}
			}
			else if (mRotationCount2 > 0) {//�E�������Ă����Ƃ�
				mRotation.mY -= 90;
				mRotationCount2 -= 1;
			}
			else if (mRotationCount > 0) {//���ʂ������Ă����Ƃ�
				mRotation.mY += 180;
				mRotationCount -= 1;
			}
			else if (mRotationCount4 > 0) {//���������Ă����Ƃ�
				mRotation.mY += 90;
				mRotationCount4 -= 1;
			}
			if (CKey::Push('C')) {
				if (mStamina > 0) {
					//X��������-�P�i�񂾒l����]�ړ�������
					mPosition = CVector(0.0f, 0.0f, 4.0f) * mMatrix;
					mStamina -= 2;
				}
				else if (mStamina <= 2 || mStamina >= 0) {
					//X��������-�P�i�񂾒l����]�ړ�������
					mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
					mStamina -= 2;
				}
			}
			else {
				//X��������-�P�i�񂾒l����]�ړ�������
				mPosition = CVector(0.0f, 0.0f, 2.0f) * mMatrix;
			}

		}
		//����
		else if (CKey::Push('J')) {
			mWeaponCount = 2;
			if (mRotationCount4 <= 0) {
				mRotationCount4 += 1;
				if (mRotationCountFirst > 0) {
					mRotation.mY += 90;
					mRotationCountFirst--;
				}
			}
			else if (mRotationCount2 > 0) {//�E�������Ă����Ƃ�
				mRotation.mY += 180;
				mRotationCount2 -= 1;
			}
			else if (mRotationCount3 > 0) {//���������Ă����Ƃ�
				mRotation.mY -= 90;
				mRotationCount3 -= 1;
			}
			else if (mRotationCount > 0) {//���ʂ������Ă����Ƃ�
				mRotation.mY += 90;
				mRotationCount -= 1;
			}
			if (CKey::Push('C')) {
				if (mStamina > 0) {
					//X��������-�P�i�񂾒l����]�ړ�������
					mPosition = CVector(0.0f, 0.0f, 4.0f) * mMatrix;
					mStamina -= 2;
				}
				else if (mStamina <= 2 || mStamina >= 0) {
					//X��������-�P�i�񂾒l����]�ړ�������
					mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
					mStamina -= 2;
				}
			}
			else {
				//X��������-�P�i�񂾒l����]�ړ�������
				mPosition = CVector(0.0f, 0.0f, 2.0f) * mMatrix;
			}


		}
		//�E��
		else if (CKey::Push('L')) {
		mWeaponCount = 3;
			if (mRotationCount2 <= 0) {
				mRotationCount2 += 1;
				if (mRotationCountFirst > 0) {
					mRotation.mY -= 90;
					mRotationCountFirst--;
				}
			}
			else if (mRotationCount > 0) {//���ʂ������Ă����Ƃ�
				mRotation.mY -= 90;
				mRotationCount -= 1;
			}
			else if (mRotationCount3 > 0) {//���������Ă����Ƃ�
				mRotation.mY += 90;
				mRotationCount3 -= 1;
			}
			else if (mRotationCount4 > 0) {//���������Ă����Ƃ�
				mRotation.mY += 180;
				mRotationCount4 -= 1;
			}
			if (CKey::Push('C')) {
				if (mStamina > 0) {
					//X��������-�P�i�񂾒l����]�ړ�������
					mPosition = CVector(0.0f, 0.0f, 4.0f) * mMatrix;
					mStamina -= 2;
				}
				else if (mStamina <= 2 || mStamina >= 0) {
					//X��������-�P�i�񂾒l����]�ړ�������
					mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
					mStamina -= 2;
				}
			}
			else {
				//X��������-�P�i�񂾒l����]�ړ�������
				mPosition = CVector(0.0f, 0.0f, 2.0f) * mMatrix;
			}
		}
	}
    //������
	 if (CKey::Push('A')) {
		//Y���̉�]�l�𑝉�
		mRotation2.mY += 3;
		mRotation.mY += 3;
	 }
	//�E����
	if (CKey::Push('D')) {
		//Y���̉�]�l�����Z
		mRotation2.mY -= 3;
		mRotation.mY -= 3;
	}
	//�����
	if (CKey::Push('S')) {
		//X���̉�]�l�����Z
		if (mRotation2.mX > -60) {

			mRotation2.mX -= 3;
		}
	}
	//������
	if (CKey::Push('W')) {
		//X���̉�]�l�����Z
		if (mRotation2.mX < 90) {

			mRotation2.mX += 3;
		}                 
	}

	/*if (mColliderCount > 0) {
		mColliderCount--;
		mPosition.mZ -= mColliderCount;
		mPosition.mY += mColliderCount;
	}
	if (mPosition.mY > 0.0f) {
		mPosition.mY -= 1.0f;
	}*/
	//CCharacter�̍X�V
	CTransform::Update();
}	
void CPlayer::Collision(CCollider* m, CCollider* o) {
	//���g�̃R���C�_�̐ݒ�
	switch (m->mType) {
	case CCollider::ELINE://�����R���C�_
			//����̃R���C�_���O�p�R���C�_�̏ꍇ
				if (o->mType == CCollider::ETRIANGLE) {
					CVector adjust;//�����p�x�N�g��
					//�O�p�`�Ɛ����̏Փ˔���
					CCollider::CollisionTriangleLine(o, m, &adjust);
					//�ʒu�̍X�V�imPosition+adjust)
					mPosition = mPosition - adjust * -1;
					//�s��̍X�V
					CTransform::Update();

				}
				if (o->mType == CCollider::ESPHERE) {
					/*CVector adjust;//�����p�x�N�g��
				//�O�p�`�Ɛ����̏Փ˔���
				// //���肪�v���C���[�̂Ƃ��A
					if (o->mpParent->mTag == CCollider::EENEMYCOLLIDER1) {
						CCollider::CollisionTriangleLine(o, m, &adjust);
						mColliderCount = 2.0f;
					}
					if (o->mpParent->mTag == CCollider::EENEMY2COLLIDER) {
						CCollider::CollisionTriangleLine(o, m, &adjust);
						mColliderCount = 2.0f;
					}*/
					
				}
	case CCollider::EPLAYER://�����R���C�_
		if (o->mType == CCollider::ESPHERE) {
			CVector adjust;//�����p�x�N�g��
		//�O�p�`�Ɛ����̏Փ˔���
		// //���肪�v���C���[�̂Ƃ��A
			if (o->mpParent->mTag == CCollider::EENEMYCOLLIDER1) {
				CCollider::CollisionTriangleLine(o, m, &adjust);
				mColliderCount = 20.0f;
			}
			if (o->mpParent->mTag == CCollider::EENEMY2COLLIDER) {
				CCollider::CollisionTriangleLine(o, m, &adjust);
				mColliderCount = 20.0f;
			}

		}
			break;
	}
}

void CPlayer::TaskCollision() {
	//�R���C�_�̗D��x�ύX
	mLine.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	mCollider.ChangePriority();
	
	//	�Փˏ��������s
	CCollisionManager::Get()->Collision(&mLine, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine3, COLLISIONRANGE);

}
void CPlayer::Render() {
	//�e�̕`�揈��
	CCharacter::Render();
	//2D�̕`��J�n
	CUtil::Start2D(-400, 400, -300, 300);
	//�`��F�̐ݒ�i�ΐF�̔������j
	glColor4f(0.0f, 1.0f, 0.0f, 0.4f);
	//������ҏW�G���A�̍쐬
	char buf[64];

	//Y���W�̕\��
	//������̐ݒ�
	sprintf(buf, "ACTION:%7.2d", mAction1);
	//������̕`��
	mText.DrawString(buf, 100, 30, 8, 16);
	//������̐ݒ�
	sprintf(buf, "STAMINA:%7.2d", mStamina);
	//������̕`��
	mText.DrawString(buf, 100, 130, 8, 16);
	//������̐ݒ�
	sprintf(buf, "SPACE:%7.2d", mSpaceCount1);
	//������̕`��
	mText.DrawString(buf, 100, 80, 8, 16);

	//X���W�̕\��
	//������̐ݒ�
	sprintf(buf, "RX:%7.2f", mRotation2.mX);
	//������̕`��
	mText.DrawString(buf, 100, 0, 8, 16);

	//Y����]�l�̕\��
	//������̐ݒ�
	sprintf(buf, "RY:%7.2f", mRotation2.mY);
	//mText.DrawString(buf, 100, -100, 8, 16);
	//������̐ݒ�
	sprintf(buf, "%10d", mRotationCount);
	mText.DrawString(buf, 100, -100, 8, 16);

	//2D�̕`��I��
	CUtil::End2D();


}