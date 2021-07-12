#include"CTaskManager.h"
#include"CTask.h"
//�^�X�N�}�l�[�W���̃C���X�^���X
CTaskManager* CTaskManager::mpInstance = 0;
//�C���X�^���X�̎擾
CTaskManager* CTaskManager::Get() {
	//�C���X�^���X���Ȃ����
	if (mpInstance == 0) {
		//�C���X�^���X�𐶐�����
		mpInstance = new CTaskManager();
	}
	return mpInstance;
}

CTaskManager::CTaskManager() {
	mHead.mpNext = &mTail;
	mTail.mpPrev = &mHead;



}
//�f�X�g���N�^
CTaskManager::~CTaskManager() {

}
//���X�g�ɒǉ�
//Add�i�^�X�N�̃|�C���^�j
void CTaskManager::Add(CTask* addTask) {
	//mHead�̎����猟��
	CTask* task = mHead.mpNext;
	//�D��x�̑傫�����Ƀ^�X�N��}��
	//�}���ʒu�̌���(�D��x���������������^�X�N�̑O�j�傫�����̂��ɏ���
	//��Priority>=0�̂���
	while (addTask->mPriority < task->mPriority)
	{
		task = task->mpNext;//����
	}
	//�e�͏o���ꂽ�u�ԃ|�C���^���ړ����邱�Ƃŏ����邱�ƂȂ��ړ��ł���

	//mpPrev=�O�̃|�C���^
	//mpNext�����̃|�C���^
	//CTask���|�C���^�ɕϊ����AmTail�̑O�ɒǉ�
	//addTask->task->addTask,,,�ƂȂ�
	//addTask�̎���task
	addTask->mpNext = task;
	//addTask�̑O��task�̑O��
	addTask->mpPrev = task->mpPrev;
	//addTask�̑O�̎���addTask��
	addTask->mpPrev->mpNext = addTask;
	//task�̑O��addTask��
	task->mpPrev = addTask;
}
//�X�V
void CTaskManager::Update() {
	//�擪����Ō�܂ŌJ��Ԃ�
	CTask* task = mHead.mpNext;
	while (task->mpNext) {
		//�X�V�������Ă�
		task->Update();
		//����
		task = task->mpNext;
	}
}
void CTaskManager::Render() {
	//�擪����Ō�܂ŌJ��Ԃ�
	CTask* task = mHead.mpNext;
	while (task->mpNext) {
		//�`�揈�����Ă�
		task->Render();
		//����
		task = task->mpNext;
	}
}
//���X�g����폜
void CTaskManager::Remove(CTask* task) {
	//�^�X�N�̑O�̎����^�X�N�̎��ɂ���
	task->mpPrev->mpNext = task->mpNext;
	//�^�X�N�̎��̑O���^�X�N�̑O�ɂ���
	task->mpNext->mpPrev = task->mpPrev;

}
void CTaskManager::Delete() {
	//�擪����Ō�܂ł��肩����
	CTask* task = mHead.mpNext;
	while (task->mpNext) {
		//task��del�Ƃ���
		CTask* del = task;
		//����
		task = task->mpNext;
		//��Enabled��false�Ȃ�폜
		if (del->mEnabled == false) {
			delete del;
		}
	}
}
void CTaskManager::TaskCollision() {


	//�擪����Ō�܂ŌJ��ւ���
	CTask* task = mHead.mpNext;
	while (task->mpNext) {
		//�Փˏ������Ă�
		task->TaskCollision();
		//����
		task = task->mpNext;
	}
}