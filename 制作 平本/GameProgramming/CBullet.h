#ifndef CBULLET_H
#define CBULLET_H
#include"CCharacter.h"
#include"CCollider.h"
class CBullet : public CCharacter {
public:
	CBullet();
	int mLife;

	//�O�p�`CTriangle��mT�Ƃ���
	CTriangle mT;
	//w,d�̒l��ݒ�i�l�͕ς�����j
	void Set(float w, float d);
	//w;//��
	//d;//����
	//�O�p�`�����̕��A�����ɐݒ�
	//�O�p�`�̖@����������ɐݒ�
	//mScale��S�ĂP�{�ɂ���
	void Update();
	//CCharacter::Update�����s
	CCollider mCollider4;

	void CBullet::Render();
	
	//�Փˏ���
//Collision(CCollider*m,CCollider*o)
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();

};
#endif
