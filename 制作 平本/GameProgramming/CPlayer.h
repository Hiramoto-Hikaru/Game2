#ifndef CPLAYER_H
#define CPLAYER_H
#include"CBullet.h"
#include"CCharacter.h"
#include"CColliderLine.h"
#include"CBullet.h"
#include"CText.h"
#include"CText.h"
class CPlayer : public CCharacter {
public:

    CPlayer();
    CColliderLine mLine;//�����R���C�_
    CColliderLine mLine2;//�����R���C�_
    CColliderLine mLine3;//�����R���C�_
    CBullet bullet();
    void Update();
   //�Փˏ���
    void Collision(CCollider* m, CCollider* o);
    void TaskCollision();
    CText mText;
    void Render();
    CCollider mCollider;//�{�̗p�R���C�_
    int mRotationCount1;
    int mRotationCount2;
    int mRotationCount3;
    int mRotationCount4;
    int mStamina;
};
#endif
  
