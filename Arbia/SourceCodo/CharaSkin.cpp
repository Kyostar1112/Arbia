#include "CharaSkin.h"

clsCharaSkin::clsCharaSkin()
{
	m_pModel = nullptr;
	m_pAnimCtrl = nullptr;
	m_pShadow = nullptr;
	m_dAnimSpeed = 0.025;

	//m_vPos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	//m_vRot = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	//m_fScale = 1.0f;
	m_pShadow = nullptr;

}

clsCharaSkin::~clsCharaSkin()
{
	if( m_pShadow != nullptr ){
		delete m_pShadow;
		m_pShadow = nullptr;
	}

	DetatchModel();
}


//============================================================
//	�ｽe�ｽ�ｽl�ｽﾌ更�ｽV.
//============================================================
void clsCharaSkin::UpDateModel()
{
	if( m_pModel == nullptr ){
		return;
	}

	m_pModel->m_vPos	= m_vPos;

	m_pModel->m_fYaw	= m_vRot.y;
	m_pModel->m_fPitch	= m_vRot.x;
	m_pModel->m_fRoll	= m_vRot.z;

	m_pModel->m_vScale	=
		D3DXVECTOR3( m_fScale, m_fScale, m_fScale );

	m_pModel->m_dAnimSpeed = m_dAnimSpeed;
}


//============================================================
//	�ｽ�ｽ�ｽ�ｽ�ｽﾞｰ�ｽﾌ関連�ｽt�ｽ�ｽ.
//============================================================
void clsCharaSkin::AttachModel( clsD3DXSKINMESH* pModel )
{
	if( pModel == nullptr ){
		return;
	}
	//�ｽ�ｽ�ｽﾙ設抵ｿｽ.
	m_pModel = pModel;
	//�ｽ�ｽﾒｰ�ｽ�ｽﾝ托ｿｽ�ｽx.
//	m_dAnimSpeed = m_pModel->GetAnimSpeed();
	//�ｽ�ｽ�ｽﾙ設抵ｿｽ.
	m_fScale = m_pModel->m_vScale.x;

	//�ｽ�ｽﾒｰ�ｽ�ｽﾝｺ�ｽ�ｽﾛｰﾗのｸﾛｰﾝ作成.
	LPD3DXANIMATIONCONTROLLER pAC
		= m_pModel->GetAnimController();
	pAC->CloneAnimationController(
		pAC->GetMaxNumAnimationOutputs(),
		pAC->GetMaxNumAnimationSets(),
		pAC->GetMaxNumTracks(),
		pAC->GetMaxNumEvents(),
		&m_pAnimCtrl );	//(out)�ｽ�ｽﾒｰ�ｽ�ｽﾝｺ�ｽ�ｽﾛｰ�ｽ.
}
//============================================================
//	�ｽ�ｽ�ｽ�ｽ�ｽﾞｰ�ｽﾖ連�ｽt�ｽ�ｽ�ｽ�ｽ.
//============================================================
void clsCharaSkin::DetatchModel()
{
	if( m_pModel != nullptr ){
		m_pModel = nullptr;
		if( m_pAnimCtrl != nullptr ){
			m_pAnimCtrl->Release();
			m_pAnimCtrl = nullptr;
		}
	}
}




//============================================================
//	�ｽ�ｽ�ｽ�ｽ�ｽﾝｸ�ｽ.
//============================================================
void clsCharaSkin::Render( D3DXMATRIX& mView, D3DXMATRIX& mProj,
	D3DXVECTOR3& vLight, D3DXVECTOR3& vEye,
	D3DXVECTOR4 &vColor, bool alphaFlg )
{
	if( m_pModel == nullptr || m_pAnimCtrl == nullptr ){
		return;
	}
	//�ｽe.
	if( m_pShadow != nullptr ){
		m_pShadow->Render( mView, mProj, vEye );
	}

	UpDateModel();

	m_pModel->Render(
		mView, mProj, vLight, vEye,
		vColor, alphaFlg, m_pAnimCtrl );
}

//============================================================
//	�ｽ�ｽﾒｰ�ｽ�ｽﾝ最大数�ｽ�ｽ謫ｾ�ｽ�ｽ�ｽ�ｽ.
//============================================================
int clsCharaSkin::GetAnimSetMax()
{
	if( m_pAnimCtrl ){
		return (int)m_pAnimCtrl->GetMaxNumAnimationSets();
	}
	return -1;
}

//============================================================
//	�ｽ�ｽﾒｰ�ｽ�ｽﾝ切托ｿｽ.
//============================================================
void clsCharaSkin::ChangeAnimSet( int index, double dStatPos )
{
	//�ｽ�ｽﾒｰ�ｽ�ｽﾝの範囲外�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ�ｽ.
	if( index < 0 || index >= GetAnimSetMax() ){
		return;
	}
	m_pModel->
		ChangeAnimSet_StartPos( index, dStatPos, m_pAnimCtrl );
}


////============================================================
//	�ｽp�ｽx�ｽ�ｽ�ｽ�ｽ.
////============================================================
bool clsCharaSkin::ThetaCheck( double dMyTheta, double dTargTheta,
	int iSarchTheta )
{
	double d_thetaArea_h = (double)iSarchTheta / 180.0 * M_PI / 2.0;
	double thetaSearchR, thetaSearchL;
	thetaSearchR = dMyTheta - d_thetaArea_h;
	thetaSearchL = dMyTheta + d_thetaArea_h;

	//�ｽp�ｽx�ｽ�ｽ�ｽ�ｽ�ｽ�ｽﾄゑｿｽ�ｽ�ｽ�ｽ�ｽ.
	if( thetaSearchL > dTargTheta &&
		thetaSearchR < dTargTheta )
	{
		return true;
	}
	////�ｽ�ｽ�ｽﾎ搾ｿｽ(0�ｽ�ｽ360�ｽﾌ具ｿｽ�ｽ�ｽ).
	else{
		if( dMyTheta < dTargTheta ){
			dTargTheta -= M_PI * 2.0;
			if( thetaSearchL > dTargTheta &&
				thetaSearchR < dTargTheta )
			{
				return true;
			}
		}
		else if( dMyTheta > dTargTheta ){
			dTargTheta += M_PI * 2.0;
			if( thetaSearchL > dTargTheta &&
				thetaSearchR < dTargTheta )
			{
				return true;
			}
		}
	}

	return false;
}


//============================================================
//	�ｽ�ｽu�ｽﾅ振�ｽ�ｽ�ｽﾈゑｿｽ(�ｽ�ｽ�ｽX�ｽﾉ振�ｽ�ｽ�ｽ).
//============================================================
void clsCharaSkin::YawSpnToTarg( float& NowYaw, float TarYaw, float TurnSpd, float TurnStop )
{
	//360,0�ｽ�ｽ�ｽ�ｽ.
	if( TarYaw - NowYaw > (float)M_PI ){
		TarYaw -= (float)( M_PI * 2.0 );
	}
	else if( TarYaw - NowYaw < (float)( -M_PI ) ){
		TarYaw += (float)( M_PI * 2.0 );
	}

	//�ｽp�ｽx�ｽ�ｽ�ｽﾟづゑｿｽ.
	if( abs( TarYaw - NowYaw ) > TurnStop ){
		if( NowYaw < TarYaw ){
			NowYaw += TurnSpd;
		}
		else if( NowYaw > TarYaw ){
			NowYaw -= TurnSpd;
		}
	}
}



//==================================================
//	�ｽﾊ置�ｽX�ｽV�ｽﾖ撰ｿｽ.
//==================================================
void clsCharaSkin::UpdatePos()
{
	D3DXMATRIX mYaw;
	//�ｽ�ｽ].
	D3DXMatrixRotationY( &mYaw, m_vRot.y );	//Y�ｽ�ｽ�ｽ�ｽ].

	//Z�ｽ�ｽ�ｽﾞｸ�ｽﾙゑｿｽp�ｽ�ｽ.
	D3DXVECTOR3 vecAxisZ( 0.0f, 0.0f, 1.0f );

	//Z軸ﾍﾞｸﾄﾙそのものを回転状態により変換する.
	D3DXVec3TransformCoord( 
		&vecAxisZ,	//(out).
		&vecAxisZ,	//.
		&mYaw );	//Y�ｽ�ｽ�ｽ�ｽ]�ｽs�ｽ�ｽ.

	//�ｽ�ｽ�ｽﾉゑｿｽ�ｽﾄ進�ｽs�ｽ�ｽ�ｽ�ｽ�ｽ�ｽl�ｽ�ｽﾝ抵ｿｽ.
	switch( m_enDir )
	{
	case enDirection_Stop:
		break;
	case enDirection_Foward:	//�ｽO�ｽi.
		//�ｽ�ｽ�ｽ�ｽ*�ｽi�ｽﾟゑｿｽl(0.1f).
		m_vPos -= vecAxisZ * 0.15f * m_fSpd;
		break;
	case enDirection_BackWard:	//�ｽ�ｽ�ｽ.
		m_vPos += vecAxisZ * 0.15f * m_fSpd;
		break;
	//case enDirection_LeftTurn:
	//	break;
	//case enDirection_RightTurn:
	//	break;
	//default:
	//	break;
	}
	//m_enDir = enDirection_Stop;//�ｽ�ｽ~.
	//==================================================

}
//==================================================
//	�ｽ�ｽ�ｽ�ｽ�ｽ阡ｻ�ｽ�ｽ�ｽ�ｽX�ｽV�ｽﾖ撰ｿｽ.
//==================================================
void clsCharaSkin::UpdateColState()
{
	ColState.vPos = m_vPos;
	ColState.fYaw = m_vRot.y;
}


//==================================================
//	�ｽ�ｽ�ｽ�ｽ�ｽ阡ｻ�ｽ�ｽﾌ擾ｿｽ�ｽﾌア�ｽh�ｽ�ｽ�ｽX�ｽ謫ｾ.
//==================================================
COL_STATE* clsCharaSkin::GetPointerCol()
{
	return &ColState;
}
//==================================================
//	�ｽ�ｽ�ｽ�ｽ�ｽ阡ｻ�ｽ�ｽp.
//==================================================
void clsCharaSkin::SetColPos( D3DXVECTOR3* vPos, float fYaw )
{
	ColState.vPos = *vPos;
	if( fYaw < -1.0f ){
		ColState.fYaw = fYaw;
	}
}


//==================================================
//	.
//==================================================
void clsCharaSkin::SetDropoutFlg( bool flg )
{
	m_bDropout = flg;
}



