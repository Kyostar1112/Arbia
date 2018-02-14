#ifndef _SP_2D_JEWEL_SET_H_
#define _SP_2D_JEWEL_SET_H_

#include "Sp2DJewel.h"

#include "Sound.h"

class clsJewerSet
{
public:
	clsJewerSet();
	~clsJewerSet();

	void Create( HWND hWnd,
		ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11,
		int iNo );

	void Move();



	//止まるだけ.
	void Stop(){
		m_vMove = { 0.0f, 0.0f, 0.0f };
		m_fAcc = 0.0f;
	};

	//再スタート前に.
	void ReSet();


	void SetMove( D3DXVECTOR3 vMove, float fAcc ){
		m_vMove = vMove;
		m_fAcc = fAcc;
	}

	bool GetDown(){
		return m_bDown;
	}

	//----- ラップ -----//.
	void Init(){
		m_smpModel->Init();
	};


	void SetScale( float fScale ){
		if( !m_smpModel ) return;
		m_fScale = fScale;
		m_smpModel->m_fScale = m_fScale;
	}

	void AddScale( float fScale );

	void Render(){
		if( !m_smpModel ) return;
		m_smpModel->Render();
	};

	void SetPos( D3DXVECTOR3 vPos ){
		if( !m_smpModel ) return;
		m_smpModel->SetPos( vPos );
	};
	D3DXVECTOR3 GetPos(){
		if( !m_smpModel ) return { -100.0f, -100.0f, -100.0f };
		return m_smpModel->GetPos();
	}

	void SetPosX( float fX ){
		if( !m_smpModel ) return;
		m_smpModel->SetPosX( fX );
	}

	void SetGetFlg( bool bFlg ){
		m_bGet = bFlg;
	}
	bool GetGetFlg(){
		return m_bGet;
	}

//	//音の種類.
//	enum enSound
//	{
//		enS_UP = 0,//宝石が上昇を始める.
////		enS_SHINE,
//
//		enS_MAX,	//最大数.
//	};

	void PlaySe( /*clsJewerSet::enSound enSe*/ ){
		if( m_pSe == nullptr ) return;

//		m_pSe[enSe]->Stop();
		m_pSe->SeekToStart();
		m_pSe->Play();
	}

private:

	unique_ptr<clsJewel> m_smpModel;
	bool m_bDown;//降下中.
	bool m_bEnd;
	D3DXVECTOR3 m_vMove;
	float		m_fAcc;
	bool		m_bGet;//手に入れられる?.


	float m_fScale;



	//効果音.
	clsSound*	m_pSe;
	void SetSe( HWND hWnd, int iNo );


};


#endif//#ifndef _SP_2D_JEWEL_SET_H_