#include"CEffect.h"

//�}�e���A���A�e�N�X�`��
CMaterial CEffect::sMaterial;
//(�ʒu�A���A�����A�e�N�X�`�����A�s���A�񐔁A�P�R�}������̃t���[����
CEffect::CEffect(const CVector& pos, float w, float h, char* texture,
	int row, int col, int fps)
	//�ϐ��̐��l�͓G�N���X�ȂǂŐݒ�
	:CBillBoard(pos, w, h), mRows(row), mCols(col), mFps(fps), mFrame(0) {
	//�e�N�X�`����ǂ�ł��Ȃ��ꍇ�͓ǂ�
	if (sMaterial.mTexture.mId == 0);
	{
		sMaterial.mTexture.Load(texture);
		sMaterial.mDiffuse[0] = sMaterial.mDiffuse[1] =
			sMaterial.mDiffuse[2] = sMaterial.mDiffuse[3] = 1.0f;
	}
}
void CEffect::Update() {

	//�R�}���̌v�Z
	int frame = mFrame++ / mFps;
	frame %= (mRows * mCols);
	//�R�}�P�̑傫���̐ݒ�
	//�A�j���[�V������tga�� �s�Ɨ񂩂�Ȃ�
	//UV��(1.0�i�E�[�̒l�j/��*�i�R�}��/�񐔁j
	float left = 1.0f / mCols * (frame % mCols);
	//UV�E�i�����W+�P.0/��)
	float righ = left + 1.0f / mCols;
	//UV��(1.0-1.0/�s��*�R�}��/��)
	float top = 1.0f - 1.0f / mRows * (frame / mCols);
	//UV��(����W�[1.0/�s���j
	float bot = top - 1.0f / mRows;
	//�e�N�X�`���}�b�s���O(�O�p�`�Q�Ńe�N�X�`���P�͈̔͂�ݒ�j
	mT[0].mUv[0] = CVector(righ, top, 0.0f);//�E��
	mT[0].mUv[1] = CVector(left, bot, 0.0f);//����
	mT[0].mUv[2] = CVector(righ,bot, 0.0f);//�E��

	mT[1].mUv[0] = CVector(left, top, 0.0f);//����
	mT[1].mUv[1] = CVector(left, bot, 0.0f);//����
	mT[1].mUv[2] = CVector(righ, top, 0.0f);//�E��
	//�r���{�[�h�X�V
	CBillBoard::Update();

	if ((mRows * mCols)==(mFrame/mFps)) {  //��Frame,,�R�}���iframe*mFps)�G�N���X����Q��
      mEnabled = false;
    }
	
}
void CEffect::Render() {
	glDisable(GL_DEPTH_TEST);  //�k�x�e�X�g����
	CBillBoard::Render(&sMaterial);
	glEnable(GL_DEPTH_TEST);  //�k�x�e�X�g�L��

}