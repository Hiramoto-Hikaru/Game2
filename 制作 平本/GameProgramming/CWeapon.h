#ifndef CWEAPON
#define CWEAPON
#include"CCharacter.h"
#include"CModel.h"
#include"CCollider.h"
#include"CPlayer.h"
class CWeapon :public CCharacter {
public:
	CWeapon(CModel* model, CVector position, CVector rotation, CVector scale);
	int mAction1;
	int mAction2;
	int mAction3;

	CCharacter* mpPlayer;//�v���C���[�̃|�C���^
	CCollider mCollider;
	void Update();
	CWeapon();
	CPlayer mPlayer;
	//�Փˏ���
//Collision(CCollider*m,CCollider*o)
	void Collision(CCollider* m, CCollider* o);

	void TaskCollision();
};
#endif