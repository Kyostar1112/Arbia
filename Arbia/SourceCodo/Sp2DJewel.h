#ifndef _SP_2D_JEWEL_H_
#define _SP_2D_JEWEL_H_


#include "Sprite2D.h"

class clsJewel
	: public clsSprite2D
{

public:
	clsJewel();
	~clsJewel();

	//�`��(�����ݸ�)(��DX9MESH����Main����2���݂���̂Œ���).
	virtual void Render();

	//SPRITE_STATE�ύX��K�p���邽�߂ɕK�v.
	virtual void UpDateSpriteSs();


	void AddPos( D3DXVECTOR3 vPos ){
		m_vPos += vPos;
	};

	float	m_fScale;

private:

	////���ٍ쐬.
	virtual HRESULT InitModel( SPRITE_STATE ss );




};




#endif//#ifndef _SP_2D_JEWEL_H_