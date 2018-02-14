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

	void Update();



<<<<<<< HEAD
<<<<<<< HEAD
	//�ｽ~�ｽﾜるだ�ｽ�ｽ.
=======
	//�~�܂邾��.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
	//�~�܂邾��.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	void Stop(){
		m_vMove = { 0.0f, 0.0f, 0.0f };
		m_fAcc = 0.0f;
	};

<<<<<<< HEAD
<<<<<<< HEAD
	//�ｽﾄス�ｽ^�ｽ[�ｽg�ｽO�ｽ�ｽ.
=======
	//�ăX�^�[�g�O��.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
	//�ăX�^�[�g�O��.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	void ReSet();


	void SetMove( D3DXVECTOR3 vMove, float fAcc ){
		m_vMove = vMove;
		m_fAcc = fAcc;
	}

	bool GetDown(){
		return m_bDown;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	void Init(){
		m_smpModel->Init();
}
=======
=======
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	//----- ���b�v -----//.
	void InitSetPos(){
		if( !m_smpModel ) return;
		m_smpModel->InitSetPos();
	};

<<<<<<< HEAD
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara

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

	void PlaySe(){
		if( m_pSe == nullptr ) return;

//		m_pSe[enSe]->Stop();
		m_pSe->SeekToStart();
		m_pSe->Play();
	}

private:

	unique_ptr<clsJewel> m_smpModel;
<<<<<<< HEAD
<<<<<<< HEAD
	bool m_bDown;//�ｽ~�ｽ�ｽ�ｽ�ｽ.
	bool m_bEnd;
	D3DXVECTOR3 m_vMove;
	float		m_fAcc;
	bool		m_bGet;//�ｽ�ｽﾉ難ｿｽ�ｽ�ｽ�ｽ�ｽ?.
=======
	bool m_bDown;//�~����.
	bool m_bEnd;
	D3DXVECTOR3 m_vMove;
	float		m_fAcc;
	bool		m_bGet;//��ɓ������?.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
	bool m_bDown;//�~����.
	bool m_bEnd;
	D3DXVECTOR3 m_vMove;
	float		m_fAcc;
	bool		m_bGet;//��ɓ������?.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara


	float m_fScale;

<<<<<<< HEAD
	//効果音.
=======


	//���ʉ�.
<<<<<<< HEAD
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	clsSound*	m_pSe;	
	void SetSe( HWND hWnd, int iNo );


};


#endif//#ifndef _SP_2D_JEWEL_SET_H_