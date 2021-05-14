#include"CCollider.h"
#include"CCollisionManager.h"
#include"CColliderLine.h"
//�R���C�_�[�E�E�E�RD���f�����ł̓����蔻��B���̌`
//�C�ӂ̃��f���ɓ\��t���邱�Ƃ�
CCollider::CCollider(CCharacter* parent, CMatrix* matrix, CVector position, float radius)
	:CCollider()
{
	//�e�ݒ�
	mpParent = parent;
	//�e�s��ݒ�
	mpMatrix = matrix;
	//CTransform�ݒ�
	mPosition = position;//�ʒu
	//���a�ݒ�
	mRadius = radius;
	//Collision���X�g�ɒǉ�
	//CCollisionManager::Get()->Add(this);
	

}
CCollider::~CCollider() {
	//Collision���X�g����폜
	CCollisionManager::Get()->Remove(this);
}
CCollider::CCollider()
:mpParent(0)
,mpMatrix(&mMatrix)
,mType(ESPHERE)
,mTag(EBODY)
{
	//�R���W�����}�l�[�W���ɒǉ�
	CCollisionManager::Get()->Add(this);

}
void CCollider::Render() {
	glPushMatrix();
	//�R���C�_�̒��S���W���v�Z
	//�����̍��W*�e�̕ϐ��s���������
	CVector pos = mPosition * *mpMatrix;//*�|�C���^,,,����
	//���S���W�ֈړ�
	glMultMatrixf(CMatrix().Translate(pos.mX, pos.mY, pos.mZ). mM[0]);
	//DIFFUSE�ԐF�ݒ�
	float c[] = { 1.0f,0.0f,0.0f,1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//���`��(�����蔻��̂���e�jglutWireSphere(���a�A�������A�������j
	glutWireSphere(mRadius, 16, 16);
	glPopMatrix();
}
//�Փ˔���
//CCollision(�R���C�_�P�C�R���C�_�Q�j
//return:true(�Փ˂��Ă���j�@false(�Փ˂��Ă��Ȃ��j
bool CCollider::Collision(CCollider* m, CCollider* o) {
	//�e�R���C�_�̒��S���W�����߂�
	//���_*�R���C�_�̕ϊ��s��*�e�̕ϊ��s��
	CVector mpos = m->mPosition * *m->mpMatrix;
	CVector opos = o->mPosition * *o->mpMatrix;
	//���S���璆�S�ւ̃x�N�g�������߂�
	mpos = mpos - opos;
	//���S�̋��������a�̍��v��菬�����ƏՓ�
	if (m->mRadius + o->mRadius > mpos.Length()) {
		//�Փ˂��Ă���
		return true;
	}
	//�Փ˂��Ă��Ȃ�
	return false;
}
//�����R���C�_�̏Փ˔���
bool CCollider::CollisionTriangleLine(CCollider* t, CCollider* l, CVector* a) {
	CVector v[3], sv, ev;  //sv,,,�n�_�Aev,,,�I�_
	//�e�R���C�_�̒��_�����[���h���W�֕ϊ�
	v[0] = t->mV[0] * *t->mpMatrix;
	v[1] = t->mV[1] * *t->mpMatrix;
	v[2] = t->mV[2] * *t->mpMatrix;

	sv = l->mV[0] * *l->mpMatrix;
	ev = l->mV[1] * *l->mpMatrix;
	//�ʂ̖@�����A�O�ς𐳋K�����Ă��Ƃ߂�
	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	//�O�p�̒��_��������n�_�ւ̃x�N�g�������߂�
	CVector v0sv = sv - v[0];
	//�O�p�̒��_��������I�_�ւ̃x�N�g�������߂�
	CVector v0ev = ev - v[0];
	//�������ʂƌ������Ă��邩�m�F����
	float dots = v0sv.Dot(normal);
	float dote = v0ev.Dot(normal);
	//�v���X�͌������Ă��Ȃ��i�ʂ͍����O�̈ʒu�ɂ��邽�߁j
	if (dots * dote >= 0.0f) {
		//�Փ˂��Ă��Ȃ�(�����s�v�j
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//�����͖ʂƌ������Ă���


	//�ʂƐ����̌�_�����߂�
	//��_�̌v�Z
	//�n�_+�i�n�_����I�_�܂ł̋����j*(v0sv�Ɩ@���̓���/�n�_����I�_�܂ł̓��ς̘a
	CVector cross = sv + (ev - sv) * (abs(dots) / (abs(dots) + abs(dote)));

	//��_���O�p�`���Ȃ�Փ˂��Ă���i�O�p�`�Ȃ̂Œ��_�R���̏Փˏ����j
	//�O�ρA�A�A�Q�̃x�N�g���̌�_���琂���ɐL�т钼��
	//���ρA�A�x�N�g���̐�Βl*�x�N�g�����̐�Βl*�Q�̃x�N�g������Ȃ�Cos��
	//���_�P�`���_�Q�x�N�g���ƒ��_1�`��_�x�N�g���Ƃ̌�_�����߁A�@���Ƃ̓��ς��}�C�i�X�Ȃ�O�p�`�̊O
	//(�P�`�Q�̃x�N�g���̒����j�A�i�P�`��_�̒����j�A�i�@���Ƃ̓��ρj
	if ((v[1] - v[0]).Cross(cross - v[0]).Dot(normal) < 0.0f) {
		//�Փ˂��Ă��Ȃ�
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//���_�Q�`���_�R�x�N�g���ƒ��_�Q�`��_�x�N�g���Ƃ̊O�ς����߁A�@���Ƃ̓��ς��}�C�i�X�Ȃ�O�p�`�̊O
	if ((v[2] - v[1]).Cross(cross - v[1]).Dot(normal) < 0.0f) {
		//�Փ˂��Ă��Ȃ�
		//*a�A�A�A�����R���C�_��߂��l
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//���_�R�`���_�P�x�N�g���ƁA���_�R�`��_�x�N�g���Ƃ̊O�ς����߁A�@���Ƃ̊O�ς��}�C�i�X�Ȃ�O�p�`�̊O
	if ((v[0] - v[2]).Cross(cross - v[2]).Dot(normal) < 0.0f) {
		//�Փ˂��Ă��Ȃ�
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	//�����l�v�Z�i�Փ˂��Ȃ��ʒu�܂Ŗ߂�)

	if (dots < 0.0f) {
		//�n�_������
		*a = normal * -dots;
	}
	else {
		//�I�_������
		*a = normal * -dote;
	}
	return true;
}
//���ƎO�p�`�̏Փ˔�����s������
bool CCollider::CollisionTriangleSphere(CCollider* t, CCollider* s, CVector* a) {
	CVector v[3], sv, ev;
	//�e�R���C�_�̒��_�����[���h���W�֕ϊ�
	v[0] = t->mV[0] * *t->mpMatrix;
	v[1] = t->mV[1] * *t->mpMatrix;
	v[2] = t->mV[2] * *t->mpMatrix;
	//�ʂ̖@����,�O�ς𐳋K�����ċ��߂�
	CVector normal=(v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	//���R���C�_�����[���h���W�ō쐬
	sv = s->mPosition * *s->mpMatrix + normal * s->mRadius;
	ev = s->mPosition * *s->mpMatrix - normal * s->mRadius;
	CColliderLine line(NULL, NULL, sv, ev);
	//�O�p�R���C�_�Ɛ��R���C�_�̏Փˏ���
	return CollisionTriangleLine(t, &line, a);

}
//�D��x�̕ύX
void CCollider::ChangePriority() {
	//�����̍��W*�e�̕ϊ��s����|���ă��[���h�ϐ������߂�
	CVector pos = mPosition * *mpMatrix;
	//�ׂ��g���̒������D��x
	mPriority = pos.Length();
	CCollisionManager::Get()->Remove(this);//��U�폜
	CCollisionManager::Get()->Add(this);//�ǉ�
}
