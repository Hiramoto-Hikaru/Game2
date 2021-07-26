#ifndef CPARENT_H
#define CPARENT_H

#include "CCharacter.h"
#include "CCollider.h"

//�q�N���X
class CChild : public CCharacter
{
private:
	static CModel sModel;
	static int sCount;
	//�e�ւ̃|�C���^
	CCharacter* mpParent;
	//�R���C�_
	CCollider mCollider;
	CVector mInitPose;
   
public:
	CChild(CCharacter* parent);
	void CChild::Collision(CCollider* m, CCollider* o);
	void Update();
	void CChild::TaskCollision();
};


#endif
