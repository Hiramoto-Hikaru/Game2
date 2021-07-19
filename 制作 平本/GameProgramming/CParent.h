#ifndef CPARENT_H
#define CPARENT_H

#include "CCharacter.h"
#include "CCollider.h"

//子クラス
class CChild : public CCharacter
{
private:
	static CModel sModel;
	static int sCount;
	//親へのポインタ
	CCharacter* mpParent;
	//コライダ
	CCollider mCollider;
public:
	CChild(CCharacter* parent);
	
	void Update();
};

//親クラス
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
