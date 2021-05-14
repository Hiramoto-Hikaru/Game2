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
CMatrix Matrix;
CPlayer::CPlayer()
//�����R���C�_�̐ݒ�i�e�A�e�s��A���_�P�A���_�Q�j
	:mLine(this, &mMatrix, CVector(0.0f, 9.0f, -7.0f), CVector(0.0f, 9.0f, 10.0f)) //�O��̐����R���C�_
	, mLine2(this, &mMatrix, CVector(0.0f, 12.0f, -4.0f), CVector(0.0f, 6.0f, -4.0f))  //�㉺�̐����R���C�_
	, mLine3(this, &mMatrix, CVector(7.0f, 9.0f, -4.0f), CVector(-7.0f, 9.0f, -4.0f))  //���E�̐����R���C�_
	,mCollider(this,&mMatrix,CVector(0.0f,9.0f,0.0f),0.1f)
	,mRotationCount1(30)
    ,mRotationCount2(0)
    ,mRotationCount3(0)
    ,mRotationCount4(0)
	, mStamina(200)
{
//�e�N�X�`���t�@�C���̓ǂݍ���(�P�s�U�S��j
mText.LoadTexture("FontWhite.tga", 1, 64);
mTag = EPLAYER;//�^�O�̐ݒ�

}
void CPlayer::Update() {
	
	//�X�y�[�X�L�[���͂Œe����
	if (CKey::Push(VK_SPACE)) {
		//Y���̉�]�l�𑝉�
		mRotation.mY += 50;
		//CBullet��bullet�ɕϊ�
		CBullet* bullet = new CBullet();
		//mPlayer�̎��_�Ɠ��������ɔ��
		bullet->Set(0.1f, 1.5f);
        bullet->mPosition = CVector(0.0f, 0.0f, 10.0f) * mMatrix;
        bullet->mRotation = mRotation;
		bullet->Update();
		//�e�N���X�̃C���X�^���X���^�X�N���X�g�ɒǉ�
		//TaskManager.Add(bullet);

	}
	if (mStamina <= 200) {
    mStamina++;
	}
	
	//�O�i
	 if (CKey::Push('I')) {
		if (mRotationCount1 <= 30) {
        //Y���̉�]�l�𑝉�
		mRotation.mY += 3;
		mRotationCount1 += 1;
		}
		else if (mRotationCount1 >= 30) {
			//Y���̉�]�l�𑝉�
			mRotation.mY -= 3;
			mRotationCount1 -= 1;
		}
		if (CKey::Push('C')) {
			//X��������-�P�i�񂾒l����]�ړ�������
			mPosition = CVector(0.0f, 0.0f, 3.0f) * mMatrix;
			mStamina-=2;
		}
		else {
			//X��������-�P�i�񂾒l����]�ړ�������
			mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
		}
		
		
	}
	//���
	else if (CKey::Push('K')) {
		if (mRotationCount2 <= 30) {
			//Y���̉�]�l�𑝉�
			mRotation.mY += 3;
			mRotationCount2 += 1;
		}
		else if (mRotationCount2 >= 30) {
			//Y���̉�]�l�𑝉�
			mRotation.mY -= 3;
			mRotationCount2 -= 1;
		}
		if (CKey::Push('C')) {
			//X��������-�P�i�񂾒l����]�ړ�������
			mPosition = CVector(0.0f, 0.0f, 3.0f) * mMatrix;
			mStamina -= 2;
		}
		else {
			//X��������-�P�i�񂾒l����]�ړ�������
			mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
		}
	}
	//����
	else if (CKey::Push('J')) {
		 //�E�������Ă���Ƃ��ɍ��ɉ�]������
		if (mRotationCount3 <= 30 - mRotationCount4) {
			//Y���̉�]�l�𑝉�
			mRotation.mY += 3;
			mRotationCount3 += 1;
			mRotationCount4 += 1;
		}
		else if (mRotationCount3 >= 30 + mRotationCount4) {
			//Y���̉�]�l�𑝉�
			mRotation.mY -= 3;
			mRotationCount3 -= 1;
			mRotationCount4 -= 1;
		}
		if (CKey::Push('C')) {
			//X��������-�P�i�񂾒l����]�ړ�������
			mPosition = CVector(0.0f, 0.0f, 3.0f) * mMatrix;
			mStamina -= 2;
		}
		else {
			//X��������-�P�i�񂾒l����]�ړ�������
			mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
		}
		

	}
	//�E��
	else if (CKey::Push('L')) {
		if (mRotationCount4 <= 30- mRotationCount3) {
			//Y���̉�]�l�𑝉�
			mRotation.mY += 3;
			mRotationCount4 += 1;
			mRotationCount3 += 1;
		}
		else if (mRotationCount4 >= 30+ mRotationCount3) {
			//Y���̉�]�l�𑝉�
			mRotation.mY -= 3;
			mRotationCount4 -= 1;
			mRotationCount3 -= 1;
		}
		if (CKey::Push('C')) {
			//X��������-�P�i�񂾒l����]�ړ�������
			mPosition = CVector(0.0f, 0.0f, 3.0f) * mMatrix;
			mStamina -= 2;
		}
		else {
        //X��������-�P�i�񂾒l����]�ړ�������
		mPosition = CVector(0.0f, 0.0f, 1.0f) * mMatrix;
		}
		

	}

    //������
	 if (CKey::Push('A')) {
		//Y���̉�]�l�𑝉�
		mRotation2.mY += 3;
	}
	//�E����
	if (CKey::Push('D')) {
		//Y���̉�]�l�����Z
		mRotation2.mY -= 3;
	}
	//�����
	if (CKey::Push('S')) {
		//X���̉�]�l�����Z
		mRotation2.mX -= 3;
	}
	//������
	if (CKey::Push('W')) {
		//X���̉�]�l�����Z
		mRotation2.mX += 3;
	}


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
	sprintf(buf, "PY:%7.2f", mPosition.mY);
	//������̕`��
	mText.DrawString(buf, 100, 30, 8, 16);

	//X���W�̕\��
	//������̐ݒ�
	sprintf(buf, "RX:%7.2f", mRotation2.mX);
	//������̕`��
	mText.DrawString(buf, 100, 0, 8, 16);

	//Y����]�l�̕\��
	//������̐ݒ�
	sprintf(buf, "RY:%7.2f", mRotation2.mY);
	mText.DrawString(buf, 100, -100, 8, 16);
	//2D�̕`��I��
	CUtil::End2D();


}