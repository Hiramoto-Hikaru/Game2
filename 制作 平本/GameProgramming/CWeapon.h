#ifndef CWEAPON
#define CWEAPON
#include"CCharacter.h"
#include"CModel.h"
#include"CCollider.h"
#include"CPlayer.h"
class CWeapon :public CCharacter {
public:
	CWeapon(CModel* model, CVector position, CVector rotation, CVector scale);
	
	int mRotationCountFirst;
	int mRotationCount;
	int mRotationCount2;
	int mRotationCount3;
	int mRotationCount4;
	int mStamina2;
	CModel mModelW;
	CCharacter* mpPlayer;//�v���C���[�̃|�C���^
	CCollider mCollider;
	void Update();
	CWeapon();
	
	//�Փˏ���
//Collision(CCollider*m,CCollider*o)
	void Collision(CCollider* m, CCollider* o);

	void TaskCollision();
};
#endif