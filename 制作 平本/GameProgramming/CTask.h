#ifndef CTASK_H
#define CTASK_H


class CTask {    //�^�X�N���X�g
public: 
	CTask* mpNext;//���̃|�C���^
	  CTask* mpPrev;//�O�̃|�C���^
	  int mPriority;//�D��x
	  bool mEnabled;//�L���t���O
	  //�f�t�H���g�R���X�g���N�^
	  CTask() :
		  mpNext(0), mpPrev(0), mPriority(0), mEnabled(true) {}
	  virtual ~CTask() {}
	  //�X�V
	  virtual void Update() {}
	  //�`��
	  virtual void Render() {}
	  //�Փˏ���
	  virtual void TaskCollision(){}
};
#endif