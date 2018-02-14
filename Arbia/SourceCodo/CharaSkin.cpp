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

<<<<<<< HEAD
=======

>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
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
<<<<<<< HEAD
//	ï¿½ï½½eï¿½ï½½ï¿½ï½½lï¿½ï½½ï¾Œæ›´ï¿½ï½½V.
=======
//	ŠeŽí’l‚ÌXV.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
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
<<<<<<< HEAD
//	ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¾žï½°ï¿½ï½½ï¾Œé–¢é€£ï¿½ï½½tï¿½ï½½ï¿½ï½½.
=======
//	ÓÃÞÙÃÞ°À‚ÌŠÖ˜A•t‚¯.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
//============================================================
void clsCharaSkin::AttachModel( clsD3DXSKINMESH* pModel )
{
	if( pModel == nullptr ){
		return;
	}
<<<<<<< HEAD
	//ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¾™è¨­æŠµï½¿ï½½.
	m_pModel = pModel;
	//ï¿½ï½½ï¿½ï½½ï¾’ï½°ï¿½ï½½ï¿½ï½½ï¾æ‰˜ï½¿ï½½ï¿½ï½½x.
//	m_dAnimSpeed = m_pModel->GetAnimSpeed();
	//ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¾™è¨­æŠµï½¿ï½½.
	m_fScale = m_pModel->m_vScale.x;

	//ï¿½ï½½ï¿½ï½½ï¾’ï½°ï¿½ï½½ï¿½ï½½ï¾ï½ºï¿½ï½½ï¿½ï½½ï¾›ï½°ï¾—ã®ï½¸ï¾›ï½°ï¾ä½œæˆ.
=======
	//ÓÃÞÙÝ’è.
	m_pModel = pModel;
	//±ÆÒ°¼®Ý‘¬“x.
//	m_dAnimSpeed = m_pModel->GetAnimSpeed();
	//½¹°ÙÝ’è.
	m_fScale = m_pModel->m_vScale.x;

	//±ÆÒ°¼®ÝºÝÄÛ°×‚Ì¸Û°Ýì¬.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	LPD3DXANIMATIONCONTROLLER pAC
		= m_pModel->GetAnimController();
	pAC->CloneAnimationController(
		pAC->GetMaxNumAnimationOutputs(),
		pAC->GetMaxNumAnimationSets(),
		pAC->GetMaxNumTracks(),
		pAC->GetMaxNumEvents(),
<<<<<<< HEAD
		&m_pAnimCtrl );	//(out)ï¿½ï½½ï¿½ï½½ï¾’ï½°ï¿½ï½½ï¿½ï½½ï¾ï½ºï¿½ï½½ï¿½ï½½ï¾›ï½°ï¿½ï½½.
}
//============================================================
//	ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¾žï½°ï¿½ï½½ï¾–é€£ï¿½ï½½tï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½.
//============================================================
void clsCharaSkin::DetatchModel()
{
	if( m_pModel != nullptr ){
		m_pModel = nullptr;
		if( m_pAnimCtrl != nullptr ){
=======
		&m_pAnimCtrl );	//(out)±ÆÒ°¼®ÝºÝÄÛ°×.
}
//============================================================
//	ÓÃÞÙÃÞ°ÀŠÖ˜A•t‚¯‰ðœ.
//============================================================
void clsCharaSkin::DetatchModel()
{
	if( m_pModel != NULL ){
		m_pModel = NULL;

	
		if( m_pAnimCtrl != NULL ){
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
			m_pAnimCtrl->Release();
			m_pAnimCtrl = nullptr;
		}
	}
}




//============================================================
<<<<<<< HEAD
//	ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¾ï½¸ï¿½ï½½.
=======
//	ÚÝÀÞØÝ¸Þ.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
//============================================================
void clsCharaSkin::Render( D3DXMATRIX& mView, D3DXMATRIX& mProj,
	D3DXVECTOR3& vLight, D3DXVECTOR3& vEye,
	D3DXVECTOR4 &vColor, bool alphaFlg )
{
	if( m_pModel == nullptr || m_pAnimCtrl == nullptr ){
		return;
	}
<<<<<<< HEAD
	//ï¿½ï½½e.
	if( m_pShadow != nullptr ){
=======
	//‰e.
	if( m_pShadow != NULL ){
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
		m_pShadow->Render( mView, mProj, vEye );
	}

	UpDateModel();

	m_pModel->Render(
		mView, mProj, vLight, vEye,
		vColor, alphaFlg, m_pAnimCtrl );
}

//============================================================
<<<<<<< HEAD
//	ï¿½ï½½ï¿½ï½½ï¾’ï½°ï¿½ï½½ï¿½ï½½ï¾æœ€å¤§æ•°ï¿½ï½½ï¿½ï½½è¬«ï½¾ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½.
=======
//	±ÆÒ°¼®ÝÅ‘å”‚ðŽæ“¾‚·‚é.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
//============================================================
int clsCharaSkin::GetAnimSetMax()
{
	if( m_pAnimCtrl ){
		return (int)m_pAnimCtrl->GetMaxNumAnimationSets();
	}
	return -1;
}

//============================================================
<<<<<<< HEAD
//	ï¿½ï½½ï¿½ï½½ï¾’ï½°ï¿½ï½½ï¿½ï½½ï¾åˆ‡æ‰˜ï½¿ï½½.
//============================================================
void clsCharaSkin::ChangeAnimSet( int index, double dStatPos )
{
	//ï¿½ï½½ï¿½ï½½ï¾’ï½°ï¿½ï½½ï¿½ï½½ï¾ã®ç¯„å›²å¤–ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½.
=======
//	±ÆÒ°¼®ÝØ‘Ö.
//============================================================
void clsCharaSkin::ChangeAnimSet( int index, double dStatPos )
{
	//±ÆÒ°¼®Ý‚Ì”ÍˆÍŠO‚©Áª¯¸‚·‚é.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	if( index < 0 || index >= GetAnimSetMax() ){
		return;
	}
	m_pModel->
		ChangeAnimSet_StartPos( index, dStatPos, m_pAnimCtrl );
}


////============================================================
<<<<<<< HEAD
//	ï¿½ï½½pï¿½ï½½xï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½.
=======
//	Šp“x”»’è.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
////============================================================
bool clsCharaSkin::ThetaCheck( double dMyTheta, double dTargTheta,
	int iSarchTheta )
{
	double d_thetaArea_h = (double)iSarchTheta / 180.0 * M_PI / 2.0;
	double thetaSearchR, thetaSearchL;
	thetaSearchR = dMyTheta - d_thetaArea_h;
	thetaSearchL = dMyTheta + d_thetaArea_h;

<<<<<<< HEAD
	//ï¿½ï½½pï¿½ï½½xï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¾„ã‚‘ï½¿ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½.
=======
	//Šp“x‚ª‡‚Á‚Ä‚¢‚½‚ç.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	if( thetaSearchL > dTargTheta &&
		thetaSearchR < dTargTheta )
	{
		return true;
	}
<<<<<<< HEAD
	////ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¾Žæ¾ï½¿ï½½(0ï¿½ï½½ï¿½ï½½360ï¿½ï½½ï¾Œå…·ï½¿ï½½ï¿½ï½½ï¿½ï½½).
=======
	////ˆêŽü‘Îô(0‚Æ360‚Ì‹«–Ú).
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
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
<<<<<<< HEAD
//	ï¿½ï½½ï¿½ï½½uï¿½ï½½ï¾…æŒ¯ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¾ˆã‚‘ï½¿ï½½(ï¿½ï½½ï¿½ï½½ï¿½ï½½Xï¿½ï½½ï¾‰æŒ¯ï¿½ï½½ï¿½ï½½ï¿½ï½½).
//============================================================
void clsCharaSkin::YawSpnToTarg( float& NowYaw, float TarYaw, float TurnSpd, float TurnStop )
{
	//360,0ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½.
=======
//	ˆêu‚ÅU‚èŒü‚©‚È‚¢(™X‚ÉU‚èŒü‚­).
//============================================================
void clsCharaSkin::YawSpnToTarg( float& NowYaw, float TarYaw, float TurnSpd, float TurnStop )
{
	//360,0–â‘è‰ðŒˆ.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	if( TarYaw - NowYaw > (float)M_PI ){
		TarYaw -= (float)( M_PI * 2.0 );
	}
	else if( TarYaw - NowYaw < (float)( -M_PI ) ){
		TarYaw += (float)( M_PI * 2.0 );
	}

<<<<<<< HEAD
	//ï¿½ï½½pï¿½ï½½xï¿½ï½½ï¿½ï½½ï¿½ï½½ï¾Ÿã¥ã‚‘ï½¿ï½½.
=======
	//Šp“x‚ª‹ß‚Ã‚­.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
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
<<<<<<< HEAD
//	ï¿½ï½½ï¾Šç½®ï¿½ï½½Xï¿½ï½½Vï¿½ï½½ï¾–æ’°ï½¿ï½½.
=======
//	ˆÊ’uXVŠÖ”.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
//==================================================
void clsCharaSkin::UpdatePos()
{
	D3DXMATRIX mYaw;
<<<<<<< HEAD
	//ï¿½ï½½ï¿½ï½½].
	D3DXMatrixRotationY( &mYaw, m_vRot.y );	//Yï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½].

	//Zï¿½ï½½ï¿½ï½½ï¿½ï½½ï¾žï½¸ï¿½ï½½ï¾™ã‚‘ï½¿ï½½pï¿½ï½½ï¿½ï½½.
	D3DXVECTOR3 vecAxisZ( 0.0f, 0.0f, 1.0f );

	//Zè»¸ï¾ï¾žï½¸ï¾„ï¾™ãã®ã‚‚ã®ã‚’å›žè»¢çŠ¶æ…‹ã«ã‚ˆã‚Šå¤‰æ›ã™ã‚‹.
	D3DXVec3TransformCoord( 
		&vecAxisZ,	//(out).
		&vecAxisZ,	//.
		&mYaw );	//Yï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½]ï¿½ï½½sï¿½ï½½ï¿½ï½½.

	//ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¾‰ã‚‘ï½¿ï½½ï¿½ï½½ï¾„é€²ï¿½ï½½sï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½lï¿½ï½½ï¿½ï½½ï¾æŠµï½¿ï½½.
=======
	//‰ñ“].
	D3DXMatrixRotationY( &mYaw, m_vRot.y );	//YŽ²‰ñ“].

	//ZŽ²ÍÞ¸ÄÙ‚ð—pˆÓ.
	D3DXVECTOR3 vecAxisZ( 0.0f, 0.0f, 1.0f );

	//ZŽ²ÍÞ¸ÄÙ‚»‚Ì‚à‚Ì‚ð‰ñ“]ó‘Ô‚É‚æ‚è•ÏŠ·‚·‚é.
	D3DXVec3TransformCoord( 
		&vecAxisZ,	//(out).
		&vecAxisZ,	//.
		&mYaw );	//YŽ²‰ñ“]s—ñ.

	//•ûŒü‚É‚æ‚Á‚Äis‚³‚¹‚é’l‚ðÝ’è.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	switch( m_enDir )
	{
	case enDirection_Stop:
		break;
<<<<<<< HEAD
	case enDirection_Foward:	//ï¿½ï½½Oï¿½ï½½i.
		//ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½*ï¿½ï½½iï¿½ï½½ï¾Ÿã‚‘ï½¿ï½½l(0.1f).
		m_vPos -= vecAxisZ * 0.15f * m_fSpd;
		break;
	case enDirection_BackWard:	//ï¿½ï½½ï¿½ï½½ï¿½ï½½.
=======
	case enDirection_Foward:	//‘Oi.
		//Œü‚©‚¤•ûŒü*i‚ß‚é’l(0.1f).
		m_vPos -= vecAxisZ * 0.15f * m_fSpd;
		break;
	case enDirection_BackWard:	//Œã‘Þ.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
		m_vPos += vecAxisZ * 0.15f * m_fSpd;
		break;
	//case enDirection_LeftTurn:
	//	break;
	//case enDirection_RightTurn:
	//	break;
	//default:
	//	break;
	}
<<<<<<< HEAD
	//m_enDir = enDirection_Stop;//ï¿½ï½½ï¿½ï½½~.
=======
	//m_enDir = enDirection_Stop;//’âŽ~.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	//==================================================

}
//==================================================
<<<<<<< HEAD
//	ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½é˜¡ï½»ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½Xï¿½ï½½Vï¿½ï½½ï¾–æ’°ï½¿ï½½.
=======
//	‚ ‚½‚è”»’èî•ñXVŠÖ”.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
//==================================================
void clsCharaSkin::UpdateColState()
{
	ColState.vPos = m_vPos;
	ColState.fYaw = m_vRot.y;
}


//==================================================
<<<<<<< HEAD
//	ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½é˜¡ï½»ï¿½ï½½ï¿½ï½½ï¾Œæ“¾ï½¿ï½½ï¿½ï½½ï¾Œã‚¢ï¿½ï½½hï¿½ï½½ï¿½ï½½ï¿½ï½½Xï¿½ï½½è¬«ï½¾.
=======
//	‚ ‚½‚è”»’è‚Ìî•ñ‚ÌƒAƒhƒŒƒXŽæ“¾.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
//==================================================
COL_STATE* clsCharaSkin::GetPointerCol()
{
	return &ColState;
}
//==================================================
<<<<<<< HEAD
//	ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½ï¿½ï½½é˜¡ï½»ï¿½ï½½ï¿½ï½½p.
=======
//	‚ ‚½‚è”»’è—p.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
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



