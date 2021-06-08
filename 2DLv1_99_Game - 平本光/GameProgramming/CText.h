#ifndef CTEXT_H
#define CTEXT_H

#include "CTexture.h"
#include"CSceneGame.h"
#include"CSceneManager.h"
#include"CScene.h"
/*
文字の描画
*/
class CText {
public:
	//テクスチャのインスタンス
	static CTexture mFont;
	//文字の描画
	static void DrawChar(char ch, int x, int y, int w, int h);
	//文字列の描画
	static void DrawString(char *s, int x, int y, int w, int h);
};

#endif
