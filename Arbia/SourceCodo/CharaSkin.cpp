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
//	�e��l�̍X�V.
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
//	�����ް�̊֘A�t��.
//============================================================
void clsCharaSkin::AttachModel( clsD3DXSKINMESH* pModel )
{
	if( pModel == nullptr ){
		return;
	}
	//���ِݒ�.
	m_pModel = pModel;
	//��Ұ��ݑ��x.
//	m_dAnimSpeed = m_pModel->GetAnimSpeed();
	//���ِݒ�.
	m_fScale = m_pModel->m_vScale.x;

	//��Ұ��ݺ��۰̸ׂ۰ݍ쐬.
	LPD3DXANIMATIONCONTROLLER pAC
		= m_pModel->GetAnimController();
	pAC->CloneAnimationController(
		pAC->GetMaxNumAnimationOutputs(),
		pAC->GetMaxNumAnimationSets(),
		pAC->GetMaxNumTracks(),
		pAC->GetMaxNumEvents(),
		&m_pAnimCtrl );	//(out)��Ұ��ݺ��۰�.
}
//============================================================
//	�����ް�֘A�t����.
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
//	�����ݸ�.
//============================================================
void clsCharaSkin::Render( D3DXMATRIX& mView, D3DXMATRIX& mProj,
	D3DXVECTOR3& vLight, D3DXVECTOR3& vEye,
	D3DXVECTOR4 &vColor, bool alphaFlg )
{
	if( m_pModel == nullptr || m_pAnimCtrl == nullptr ){
		return;
	}
	//�e.
	if( m_pShadow != nullptr ){
		m_pShadow->Render( mView, mProj, vEye );
	}

	UpDateModel();

	m_pModel->Render(
		mView, mProj, vLight, vEye,
		vColor, alphaFlg, m_pAnimCtrl );
}

//============================================================
//	��Ұ��ݍő吔��擾����.
//============================================================
int clsCharaSkin::GetAnimSetMax()
{
	if( m_pAnimCtrl ){
		return (int)m_pAnimCtrl->GetMaxNumAnimationSets();
	}
	return -1;
}

//============================================================
//	��Ұ��ݐؑ�.
//============================================================
void clsCharaSkin::ChangeAnimSet( int index, double dStatPos )
{
	//��Ұ��݂͈̔͊O���������.
	if( index < 0 || index >= GetAnimSetMax() ){
		return;
	}
	m_pModel->
		ChangeAnimSet_StartPos( index, dStatPos, m_pAnimCtrl );
}


////============================================================
//	�p�x����.
////============================================================
bool clsCharaSkin::ThetaCheck( double dMyTheta, double dTargTheta,
	int iSarchTheta )
{
	double d_thetaArea_h = (double)iSarchTheta / 180.0 * M_PI / 2.0;
	double thetaSearchR, thetaSearchL;
	thetaSearchR = dMyTheta - d_thetaArea_h;
	thetaSearchL = dMyTheta + d_thetaArea_h;

	//�p�x������Ă�����.
	if( thetaSearchL > dTargTheta &&
		thetaSearchR < dTargTheta )
	{
		return true;
	}
	////���΍�(0��360�̋���).
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
//	��u�ŐU���Ȃ�(���X�ɐU���).
//============================================================
void clsCharaSkin::YawSpnToTarg( float& NowYaw, float TarYaw, float TurnSpd, float TurnStop )
{
	//360,0����.
	if( TarYaw - NowYaw > (float)M_PI ){
		TarYaw -= (float)( M_PI * 2.0 );
	}
	else if( TarYaw - NowYaw < (float)( -M_PI ) ){
		TarYaw += (float)( M_PI * 2.0 );
	}

	//�p�x���߂Â�.
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
//	�ʒu�X�V�֐�.
//==================================================
void clsCharaSkin::UpdatePos()
{
	D3DXMATRIX mYaw;
	//��].
	D3DXMatrixRotationY( &mYaw, m_vRot.y );	//Y����].

	//Z���޸�ق�p��.
	D3DXVECTOR3 vecAxisZ( 0.0f, 0.0f, 1.0f );

	//Z軸ﾍﾞｸﾄﾙそのものを回転状態により変換する.

	D3DXVec3TransformCoord(
		&vecAxisZ,	//(out).
		&vecAxisZ,	//.
		&mYaw );	//Y����]�s��.

	//���ɂ��Đi�s������l��ݒ�.
	switch( m_enDir )
	{
	case enDirection_Stop:
		break;
	case enDirection_Foward:	//�O�i.
		//����*�i�߂�l(0.1f).
		m_vPos -= vecAxisZ * 0.15f * m_fSpd;
		break;
	case enDirection_BackWard:	//���.
		m_vPos += vecAxisZ * 0.15f * m_fSpd;
		break;
	//case enDirection_LeftTurn:
	//	break;
	//case enDirection_RightTurn:
	//	break;
	//default:
	//	break;
	}
	//m_enDir = enDirection_Stop;//��~.
	//==================================================

}
//==================================================
//	�����蔻����X�V�֐�.
//==================================================
void clsCharaSkin::UpdateColState()
{
	ColState.vPos = m_vPos;
	ColState.fYaw = m_vRot.y;
}


//==================================================
//	�����蔻��̏��̃A�h���X�擾.
//==================================================
COL_STATE* clsCharaSkin::GetPointerCol()
{
	return &ColState;
}
//==================================================
//	�����蔻��p.
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



