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

    int mRotationCountFirst;
	int mRotationCount;
	int mRotationCount2;
	int mRotationCount3;
	int mRotationCount4;
	int mStamina2;
public:
	CChild(CCharacter* parent);
	
	void Update();
};

//�e�N���X
class CParent : public CCharacter
{
private:
	static CModel mModel;
	static int sCount;
	
public:
	CParent();
	
	void Update();
};

#endif
