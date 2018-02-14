#ifndef _SP_2D_JEWEL_H_
#define _SP_2D_JEWEL_H_


#include "Sprite2D.h"

class clsJewel
	: public clsSprite2D
{

public:
	clsJewel();
	~clsJewel();

	//描画(ﾚﾝﾀﾞﾘﾝｸﾞ)(※DX9MESH内とMain内で2つ存在するので注意).
	virtual void Render();

	//SPRITE_STATE変更を適用するために必要.
	virtual void UpDateSpriteSs();


	void AddPos( D3DXVECTOR3 vPos ){
		m_vPos += vPos;
	};

	float	m_fScale;

private:

	////ﾓﾃﾞﾙ作成.
	virtual HRESULT InitModel( SPRITE_STATE ss );




};




#endif//#ifndef _SP_2D_JEWEL_H_