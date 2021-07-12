#include"CModel.h"
//�W�����o�͂̃C���N���[�h
#include<stdio.h> //�V�X�e���̃w�b�_�́����ň͂�
#include<string.h>
#include"CVector.h"
#include"CTriangle.h"

//C�W���֐����g�����߂ɃC���N���[�h
//���f���t�@�C���̓���
//Load(���f���t�@�C�����@�}�e���A���t�@�C�����j

CModel::CModel() 
	: mpVertex(0),
	mpNormal(0), 
	mpTextureCoord(0)
{
}
//�f�X�g���N�^
CModel::~CModel() {
	//delete...�폜
	//mpMaterials[i]���폜
	for (int i = 0; i < mpMaterials.size(); i++) {
		delete mpMaterials[i];
	}
	if (mpVertex) {
		//���_���W�z��폜
		delete[]mpVertex;
	}
	if (mpNormal) {
	  //�@���z��폜
		delete[]mpNormal;
	}
	if (mpTextureCoord) {
      //�e�N�X�`���}�b�s���O�z��폜
		delete[]mpTextureCoord;
	}
}
void CModel::Load(char* obj, char* mtl) {//�ϐ��̃A�h���X
	//���_�f�[�^�̕ۑ��iCVector�^�j
	std::vector<CVector>vertex;
	//�@���f�[�^�̕ۑ�
	std::vector<CVector>normal;
	//�e�N�X�`���}�b�s���O�̕ۑ�
	std::vector<CVector>uv;
	//�t�@�C���|�C���^�ϐ��̍쐬
	FILE* fp;
	//�t�@�C���̃I�[�v��
	//fopen�i�t�@�C����,���[�h�j
	//�I�[�v���ł��Ȃ��Ƃ���NULL��Ԃ�
	//�}�e���A���t�@�C�����I�[�v��
	fp = fopen(mtl, "r"); //r=���́Aw=�o�́Aa=�ǉ�


	//�t�@�C���I�[�v���G���[����
	//	fp��NULL�̂Ƃ��i�t�@�C�����J���Ȃ��Ƃ��j�̓G���[
	if (fp == NULL) {
		//�R���\�[���ɃG���[�o�͂��Ė߂�
		printf("%s file open error\n", obj);//s���o��
		return;
	}


	//�t�@�C��������f�[�^�����
	//���̓G���A���쐬
	char buf[256];//�o�C�g��
	//�}�e���A���C���f�b�N�X
	int idx = 0;
	//�t�@�C��������P�s����
	//fgets�i���̓G���A�A�G���A�T�C�Y�A�t�@�C���|�C���^�j
	//�t�@�C���̍Ō�ɂȂ��NULL��Ԃ�
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//�f�[�^�𕪊�����
		char str[4][64] = { "","","","" };
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);
		if (strcmp(str[0], "newmtl") == 0)
		{//������̔�r�i�O���������j
			CMaterial* pm = new CMaterial();
			//�}�e���A�����̃R�s�[
			strncpy(pm->mName, str[1], sizeof(pm->mName) - 1);
			//�}�e���A���̉ϒ���ɒǉ�
			mpMaterials.push_back(pm);
			//�z��̒������擾
			idx = mpMaterials.size() - 1;
		}
		//�擪��Kd�̂Ƃ��ADiffuse��ݒ肷��
		else if (strcmp(str[0], "Kd") == 0) {
			mpMaterials[idx]->mDiffuse[0] = atof(str[1]);
			mpMaterials[idx]->mDiffuse[1] = atof(str[2]);
			mpMaterials[idx]->mDiffuse[2] = atof(str[3]);
			//mpMaterial�̂�Diffuse��str�ɓ��������������
		}
		//�擪�����̂Ƃ�a�l��ݒ肷��
		else if (strcmp(str[0], "d") == 0) {
			mpMaterials[idx]->mDiffuse[3] = atof(str[1]);
		}
		else if (strcmp(str[0], "map_Kd") == 0) {
			mpMaterials[idx]->mTexture.Load(str[1]);
		}

		//sizeof=�w�肵���ϐ��̃o�C�g�����擾
		//���͂����l���R���\�[���ɏo�͂���
	}
	//�t�@�C���̃N���[�Y
	fclose(fp);//�g�p��̃t�@�C���̓N���[�Y

 	//�I�u�W�F�N�g�t�@�C�����I�[�v��
	fp = fopen(obj, "r");
	//	fp��NULL�̂Ƃ��i�t�@�C�����J���Ȃ��Ƃ��j�̓G���[
	if (fp == NULL) {
		//�R���\�[���ɃG���[�o�͂��Ė߂�
		printf("%s file open error\n", obj);
		return;
	}


	//�t�@�C��������f�[�^�����
	//���̓G���A���쐬

		 //�t�@�C��������P�s����
		 //fgets�i���̓G���A�A�G���A�T�C�Y�A�t�@�C���|�C���^�j
		 //�t�@�C���̍Ō�ɂȂ��NULL��Ԃ�
	//buf���g����
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//�f�[�^�𕪊�����
		//""=������@''=����
		char str[4][64] = { "","","","" };

		//�����񂩂�f�[�^���S�ϐ��ɑ������
		//sscanf�i������P�A������Q�j�I�u�W�F�N�g�t�@�C���̕�����𕪊�
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);
		//%S��������œ���
		//������P�ƕ�����Q���������O�C�قȂ�Ƃ��͂O�ȊO��Ԃ�
		//�擪�����̂Ƃ��A���_��vertex�ɒǉ�����
		//strcmp��������̔�r
		if (strcmp(str[0], "v") == 0) {//������̔�r�i�O���������j
			//�ϒ���vertex�ɒǉ�
			//atof(������j�@������float�^�̒l��Ԃ�
			vertex.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));


		}
		//�擪��vn�̂Ƃ�
		//normal�ɖ@����ǉ�
		if (strcmp(str[0], "vn") == 0) {//������̔�r�i�O���������j
			//�ϒ���normal�ɒǉ�
			//atof(������j�@������float�^�̒l��Ԃ�
			normal.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		//�擪��usemtl�̂Ƃ�
		else if (strcmp(str[0], "usemtl") == 0) {

			//�ϒ��z������Ƃ����r
			for (idx = mpMaterials.size() - 1; idx > 0; idx--) {
				//�������O�̃}�e���A��������΃��[�v�I��
				if (strcmp(mpMaterials[idx]->mName, str[1]) == 0) {
					break;//���[�v���甲����
				}
			}
		}
		//�擪�����̂Ƃ��O�p�`���쐬���Ēǉ�����
		else if (strcmp(str[0], "f") == 0) { //f=Face
		//���_�Ɩ@���̔ԍ��쐬
			int v[3], n[3];
			//�e�N�X�`���}�b�s���O�̗L���𔻒�
			if (strstr(str[1], "//")) {


				//���_�Ɩ@���̔ԍ��擾
				sscanf(str[1], "%d//%d", &v[0], &n[0]); //�u���_//�@���v�ƂȂ�
				sscanf(str[2], "%d//%d", &v[1], &n[1]);//sscanf=������̒l��ϐ��ɑ��
				sscanf(str[3], "%d//%d", &v[2], &n[2]);//%d��int�^�ɕϊ����鉉�Z�q�A�P�O�i���œ���
				//�O�p�`�쐬
				CTriangle t;
				t.SetVertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				//�@���x�N�g���̒ǉ�
				t.SetNormal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				//mMaterialIdx��idx����
				t.mMaterialIdx = idx;
				//�ϒ���Triangles�ɎO�p�`��ǉ�
				//push_back���z��ɗv�f��ǉ�
				mTriangles.push_back(t);
			}

			else {
				//�e�N�X�`���}�b�s���O����
				int u[3];//�e�N�X�`���}�b�s���O�̔ԍ�

				//���_�Ɩ@���̔ԍ��擾�ƃ}�b�s���O�̔ԍ��擾
				sscanf(str[1], "%d/%d/%d", &v[0], &u[0], &n[0]); //�u���_//�}�b�s���O//�@���v�ƂȂ�
				sscanf(str[2], "%d/%d/%d", &v[1], &u[1], &n[1]);//sscanf=������̒l��ϐ��ɑ��
				sscanf(str[3], "%d/%d/%d", &v[2], &u[2], &n[2]);//%d��int�^�ɕϊ����鉉�Z�q�A�P�O�i���œ���
				//�O�p�`�쐬
				CTriangle t;
				//�z��̂P�Ԗڂ͂O����Ȃ̂łP���Z���ĂO����J�E���g����
				t.SetVertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				//�@���x�N�g���̒ǉ�
				t.SetNormal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				//�e�N�X�`���}�b�s���O�̐ݒ�
				t.mUv[0] = uv[u[0] - 1];
				t.mUv[1] = uv[u[1] - 1];
				t.mUv[2] = uv[u[2] - 1];
				//�}�e���A���ԍ��̐ݒ�
				t.mMaterialIdx = idx;
				//�ϒ��z��Trianglesb�ɎO�p�`��ǉ�
				mTriangles.push_back(t);
			}
		}
		else if (strcmp(str[0], "vt") == 0) {
			//�ϒ��z�񂤂��ɒǉ�
			//atof(������)  �����񂩂�float�^�̒l��Ԃ�
			uv.push_back(CVector(atof(str[1]), atof(str[2]), 0.0));
		}

	}
	//�t�@�C���̃N���[�Y
	fclose(fp);//�g�p��̃t�@�C���̓N���[�Y
	   //fgets�i���̓G���A�A�G���A�T�C�Y�A�t�@�C���|�C���^�j
	   //�t�@�C���̍Ō�ɂȂ��NULL��Ԃ�

 //���_���W�z��̍쐬	
	//���ׂĂ̍��W�̒l���}�e���A���̏��Ԃɕۑ�����
	mpVertex = new float[mTriangles.size() * 9];
	//�S�Ă̖@���̒l���}�e���A���̏��Ԃɕۑ�����
	mpNormal = new float[mTriangles.size() * 9];
	//�S�Ẵe�N�X�`���}�b�s���O�̒l���}�e���A���̏��Ԃɕۑ�����
	mpTextureCoord = new float[mTriangles.size() * 6];

	int v = 0, t = 0;
	//�}�e���A�����Ƃɒ��_�z��ɐݒ肷��
	for (int i = 0; i < mpMaterials.size(); i++) {
		//�S�Ă̎O�p�`���r	
		for (int j = 0; j < mTriangles.size(); j++) {
			//�}�e���A���ԍ�����v����Ƃ�
			if (i == mTriangles[j].mMaterialIdx) {
				//���_�z��ɐݒ肷��
			//���_���W
				//float�^�̒l����
				//3���*X�AY�AZ
				mpVertex[v++] = mTriangles[j].mV[0].mX;
				mpVertex[v++] = mTriangles[j].mV[0].mY;
				mpVertex[v++] = mTriangles[j].mV[0].mZ;
				mpVertex[v++] = mTriangles[j].mV[1].mX;
				mpVertex[v++] = mTriangles[j].mV[1].mY;
				mpVertex[v++] = mTriangles[j].mV[1].mZ;
				mpVertex[v++] = mTriangles[j].mV[2].mX;
				mpVertex[v++] = mTriangles[j].mV[2].mY;
				mpVertex[v++] = mTriangles[j].mV[2].mZ;
				v -= 9;
				//�@��
				//3���*X�AY�AZ
				mpNormal[v++] = mTriangles[j].mN[0].mX;
				mpNormal[v++] = mTriangles[j].mN[0].mY;
			    mpNormal[v++] = mTriangles[j].mN[0].mZ;
				mpNormal[v++] = mTriangles[j].mN[1].mX;
				mpNormal[v++] = mTriangles[j].mN[1].mY;
				mpNormal[v++] = mTriangles[j].mN[1].mZ;
				mpNormal[v++] = mTriangles[j].mN[2].mX;
				mpNormal[v++] = mTriangles[j].mN[2].mY;
				mpNormal[v++] = mTriangles[j].mN[2].mZ;
				//�e�N�X�`���}�b�s���O
				//3���*X�AY
				mpTextureCoord[t++] = mTriangles[j].mUv[0].mX;
				mpTextureCoord[t++] = mTriangles[j].mUv[0].mY;
				mpTextureCoord[t++] = mTriangles[j].mUv[1].mX;
				mpTextureCoord[t++] = mTriangles[j].mUv[1].mY;
				mpTextureCoord[t++] = mTriangles[j].mUv[2].mX;
				mpTextureCoord[t++] = mTriangles[j].mUv[2].mY;
		
			}
	    }
		//���_����ݒ�
		//X���AY���AZ���i�R�j�łP�̒��_
		mpMaterials[i]->mVertexNum = v/3;
     }
}	

void CModel::Render(const CMatrix& m) {
	//�s��̑ޔ�
	glPushMatrix();
	//�����s����|����
	glMultMatrixf(&m.mM[0][0]);


	//���_�z��̍��W��L��
	glEnableClientState(GL_VERTEX_ARRAY);
	//�@���̔z���L���ɂ���
	glEnableClientState(GL_NORMAL_ARRAY);
	//�e�N�X�`���}�b�s���O�̔z���L��
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);


	//���_���W�̔z����w��
	glVertexPointer(3, GL_FLOAT, 0, mpVertex);
	//�@���̔z����w��
	glNormalPointer(GL_FLOAT, 0, mpNormal);
	//�e�N�X�`���R�[�h�̔z����w��
	glTexCoordPointer(2, GL_FLOAT, 0, mpTextureCoord);

	int first = 0;//�`��ʒu
	//�}�e���A�����Ƃɕ`��
	for (int i = 0; i < mpMaterials.size(); i++) {
		//�}�e���A����K�p����
		mpMaterials[i]->Enabled();
		//�`��ʒu����̃f�[�^�ŎO�p�`��`��
		glDrawArrays(GL_TRIANGLES, first, mpMaterials[i]->mVertexNum - first);
		//�}�e���A���𖳌��ɂ���
		mpMaterials[i]->Disabled();
		//�`��ʒu���ړ�
		first = mpMaterials[i]->mVertexNum;

	}

	glPopMatrix();
	//Disable...�����@Cliant...�N���C�A���g
	//���_�̔z��𖳌��ɂ���
	glDisableClientState(GL_VERTEX_ARRAY);
	//�@���̔z��𖳌��ɂ���
	glDisableClientState(GL_NORMAL_ARRAY);
	//�e�N�X�`���}�b�s���O�̔z��𖳌��ɂ���
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	return;
}