#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H
#include"CTask.h"
class CTaskManager {
	//�V���O���g�����f��
	//�C���X�^���X���f����������������A���̃C���X�^���X�ɂ̂݃A�N�Z�X������d�g��
private:
	//�^�X�N�}�l�[�W���̃C���X�^���X
	static CTaskManager* mpInstance;
protected:
	//�f�t�H���g�R���X�g���N�^
		CTaskManager();
public:
	//�C���X�^���X�̎擾
	static CTaskManager* Get();
	CTask mHead;//�擪�^�X�N
	CTask mTail;//�ŏI�^�X�N
		
		//���X�g����폜
		//Remove(�^�X�N�̃|�C���^�j
		void Remove(CTask *task);
	//�f�X�g���N�^
	virtual ~CTaskManager();
	//���X�g�ɒǉ�
	//Add�i�^�X�N�̃|�C���^�j
	void Add(CTask* addTask);
	//�X�V	
	void Update();
	//�`��
	void Render();
	//�^�X�N�̍폜
	void Delete();
	void TaskCollision();
};


#endif

