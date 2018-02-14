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

<<<<<<< HEAD
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
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
<<<<<<< HEAD
//	ÔøΩÔΩΩeÔøΩÔΩΩÔøΩÔΩΩlÔøΩÔΩΩÔæåÊõ¥ÔøΩÔΩΩV.
=======
//	äeéÌílÇÃçXêV.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
//	äeéÌílÇÃçXêV.
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
<<<<<<< HEAD
//	ÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔæûÔΩ∞ÔøΩÔΩΩÔæåÈñ¢ÈÄ£ÔøΩÔΩΩtÔøΩÔΩΩÔøΩÔΩΩ.
=======
//	”√ﬁŸ√ﬁ∞¿ÇÃä÷òAïtÇØ.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
//	”√ﬁŸ√ﬁ∞¿ÇÃä÷òAïtÇØ.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
//============================================================
void clsCharaSkin::AttachModel( clsD3DXSKINMESH* pModel )
{
	if( pModel == nullptr ){
		return;
	}
<<<<<<< HEAD
<<<<<<< HEAD
	//ÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔæôË®≠ÊäµÔΩøÔΩΩ.
	m_pModel = pModel;
	//ÔøΩÔΩΩÔøΩÔΩΩÔæíÔΩ∞ÔøΩÔΩΩÔøΩÔΩΩÔæùÊâòÔΩøÔΩΩÔøΩÔΩΩx.
//	m_dAnimSpeed = m_pModel->GetAnimSpeed();
	//ÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔæôË®≠ÊäµÔΩøÔΩΩ.
	m_fScale = m_pModel->m_vScale.x;

	//ÔøΩÔΩΩÔøΩÔΩΩÔæíÔΩ∞ÔøΩÔΩΩÔøΩÔΩΩÔæùÔΩ∫ÔøΩÔΩΩÔøΩÔΩΩÔæõÔΩ∞Ôæó„ÅÆÔΩ∏ÔæõÔΩ∞Ôæù‰ΩúÊàê.
=======
=======
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	//”√ﬁŸê›íË.
	m_pModel = pModel;
	//±∆“∞ºÆ›ë¨ìx.
//	m_dAnimSpeed = m_pModel->GetAnimSpeed();
	//Ωπ∞Ÿê›íË.
	m_fScale = m_pModel->m_vScale.x;

	//±∆“∞ºÆ›∫›ƒ€∞◊ÇÃ∏€∞›çÏê¨.
<<<<<<< HEAD
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	LPD3DXANIMATIONCONTROLLER pAC
		= m_pModel->GetAnimController();
	pAC->CloneAnimationController(
		pAC->GetMaxNumAnimationOutputs(),
		pAC->GetMaxNumAnimationSets(),
		pAC->GetMaxNumTracks(),
		pAC->GetMaxNumEvents(),
<<<<<<< HEAD
<<<<<<< HEAD
		&m_pAnimCtrl );	//(out)ÔøΩÔΩΩÔøΩÔΩΩÔæíÔΩ∞ÔøΩÔΩΩÔøΩÔΩΩÔæùÔΩ∫ÔøΩÔΩΩÔøΩÔΩΩÔæõÔΩ∞ÔøΩÔΩΩ.
}
//============================================================
//	ÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔæûÔΩ∞ÔøΩÔΩΩÔæñÈÄ£ÔøΩÔΩΩtÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩ.
//============================================================
void clsCharaSkin::DetatchModel()
{
	if( m_pModel != nullptr ){
		m_pModel = nullptr;
		if( m_pAnimCtrl != nullptr ){
=======
=======
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
		&m_pAnimCtrl );	//(out)±∆“∞ºÆ›∫›ƒ€∞◊.
}
//============================================================
//	”√ﬁŸ√ﬁ∞¿ä÷òAïtÇØâèú.
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
<<<<<<< HEAD
//	ÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔæùÔΩ∏ÔøΩÔΩΩ.
=======
//	⁄›¿ﬁÿ›∏ﬁ.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
//	⁄›¿ﬁÿ›∏ﬁ.
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
<<<<<<< HEAD
	//ÔøΩÔΩΩe.
	if( m_pShadow != nullptr ){
=======
=======
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	//âe.
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
<<<<<<< HEAD
//	ÔøΩÔΩΩÔøΩÔΩΩÔæíÔΩ∞ÔøΩÔΩΩÔøΩÔΩΩÔæùÊúÄÂ§ßÊï∞ÔøΩÔΩΩÔøΩÔΩΩË¨´ÔΩæÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩ.
=======
//	±∆“∞ºÆ›ç≈ëÂêîÇéÊìæÇ∑ÇÈ.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
//	±∆“∞ºÆ›ç≈ëÂêîÇéÊìæÇ∑ÇÈ.
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
<<<<<<< HEAD
//	ÔøΩÔΩΩÔøΩÔΩΩÔæíÔΩ∞ÔøΩÔΩΩÔøΩÔΩΩÔæùÂàáÊâòÔΩøÔΩΩ.
//============================================================
void clsCharaSkin::ChangeAnimSet( int index, double dStatPos )
{
	//ÔøΩÔΩΩÔøΩÔΩΩÔæíÔΩ∞ÔøΩÔΩΩÔøΩÔΩΩÔæù„ÅÆÁØÑÂõ≤Â§ñÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩ.
=======
=======
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
//	±∆“∞ºÆ›êÿë÷.
//============================================================
void clsCharaSkin::ChangeAnimSet( int index, double dStatPos )
{
	//±∆“∞ºÆ›ÇÃîÕàÕäOÇ©¡™Ø∏Ç∑ÇÈ.
<<<<<<< HEAD
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	if( index < 0 || index >= GetAnimSetMax() ){
		return;
	}
	m_pModel->
		ChangeAnimSet_StartPos( index, dStatPos, m_pAnimCtrl );
}


////============================================================
<<<<<<< HEAD
<<<<<<< HEAD
//	ÔøΩÔΩΩpÔøΩÔΩΩxÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩ.
=======
//	äpìxîªíË.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
//	äpìxîªíË.
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
<<<<<<< HEAD
	//ÔøΩÔΩΩpÔøΩÔΩΩxÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔæÑ„ÇëÔΩøÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩ.
=======
	//äpìxÇ™çáÇ¡ÇƒÇ¢ÇΩÇÁ.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
	//äpìxÇ™çáÇ¡ÇƒÇ¢ÇΩÇÁ.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	if( thetaSearchL > dTargTheta &&
		thetaSearchR < dTargTheta )
	{
		return true;
	}
<<<<<<< HEAD
<<<<<<< HEAD
	////ÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔæéÊêæÔΩøÔΩΩ(0ÔøΩÔΩΩÔøΩÔΩΩ360ÔøΩÔΩΩÔæåÂÖ∑ÔΩøÔΩΩÔøΩÔΩΩÔøΩÔΩΩ).
=======
	////àÍé¸ëŒçÙ(0Ç∆360ÇÃã´ñ⁄).
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
	////àÍé¸ëŒçÙ(0Ç∆360ÇÃã´ñ⁄).
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
<<<<<<< HEAD
//	ÔøΩÔΩΩÔøΩÔΩΩuÔøΩÔΩΩÔæÖÊåØÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔæà„ÇëÔΩøÔΩΩ(ÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩXÔøΩÔΩΩÔæâÊåØÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩ).
//============================================================
void clsCharaSkin::YawSpnToTarg( float& NowYaw, float TarYaw, float TurnSpd, float TurnStop )
{
	//360,0ÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩ.
=======
//	àÍèuÇ≈êUÇËå¸Ç©Ç»Ç¢(èôÅXÇ…êUÇËå¸Ç≠).
//============================================================
void clsCharaSkin::YawSpnToTarg( float& NowYaw, float TarYaw, float TurnSpd, float TurnStop )
{
	//360,0ñ‚ëËâåà.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
//	àÍèuÇ≈êUÇËå¸Ç©Ç»Ç¢(èôÅXÇ…êUÇËå¸Ç≠).
//============================================================
void clsCharaSkin::YawSpnToTarg( float& NowYaw, float TarYaw, float TurnSpd, float TurnStop )
{
	//360,0ñ‚ëËâåà.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	if( TarYaw - NowYaw > (float)M_PI ){
		TarYaw -= (float)( M_PI * 2.0 );
	}
	else if( TarYaw - NowYaw < (float)( -M_PI ) ){
		TarYaw += (float)( M_PI * 2.0 );
	}

<<<<<<< HEAD
<<<<<<< HEAD
	//ÔøΩÔΩΩpÔøΩÔΩΩxÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔæü„Å•„ÇëÔΩøÔΩΩ.
=======
	//äpìxÇ™ãﬂÇ√Ç≠.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
	//äpìxÇ™ãﬂÇ√Ç≠.
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
<<<<<<< HEAD
//	ÔøΩÔΩΩÔæäÁΩÆÔøΩÔΩΩXÔøΩÔΩΩVÔøΩÔΩΩÔæñÊí∞ÔΩøÔΩΩ.
=======
//	à íuçXêVä÷êî.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
//	à íuçXêVä÷êî.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
//==================================================
void clsCharaSkin::UpdatePos()
{
	D3DXMATRIX mYaw;
<<<<<<< HEAD
<<<<<<< HEAD
	//ÔøΩÔΩΩÔøΩÔΩΩ].
	D3DXMatrixRotationY( &mYaw, m_vRot.y );	//YÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩ].

	//ZÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔæûÔΩ∏ÔøΩÔΩΩÔæô„ÇëÔΩøÔΩΩpÔøΩÔΩΩÔøΩÔΩΩ.
	D3DXVECTOR3 vecAxisZ( 0.0f, 0.0f, 1.0f );

	//ZËª∏ÔæçÔæûÔΩ∏ÔæÑÔæô„Åù„ÅÆ„ÇÇ„ÅÆ„ÇíÂõûËª¢Áä∂ÊÖã„Å´„Çà„ÇäÂ§âÊèõ„Åô„Çã.
	D3DXVec3TransformCoord( 
		&vecAxisZ,	//(out).
		&vecAxisZ,	//.
		&mYaw );	//YÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩ]ÔøΩÔΩΩsÔøΩÔΩΩÔøΩÔΩΩ.

	//ÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔæâ„ÇëÔΩøÔΩΩÔøΩÔΩΩÔæÑÈÄ≤ÔøΩÔΩΩsÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩlÔøΩÔΩΩÔøΩÔΩΩÔæùÊäµÔΩøÔΩΩ.
=======
	//âÒì].
	D3DXMatrixRotationY( &mYaw, m_vRot.y );	//Yé≤âÒì].

	//Zé≤Õﬁ∏ƒŸÇópà”.
	D3DXVECTOR3 vecAxisZ( 0.0f, 0.0f, 1.0f );

	//Zé≤Õﬁ∏ƒŸÇªÇÃÇ‡ÇÃÇâÒì]èÛë‘Ç…ÇÊÇËïœä∑Ç∑ÇÈ.
	D3DXVec3TransformCoord( 
		&vecAxisZ,	//(out).
		&vecAxisZ,	//.
		&mYaw );	//Yé≤âÒì]çsóÒ.

	//ï˚å¸Ç…ÇÊÇ¡ÇƒêiçsÇ≥ÇπÇÈílÇê›íË.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
	//âÒì].
	D3DXMatrixRotationY( &mYaw, m_vRot.y );	//Yé≤âÒì].

	//Zé≤Õﬁ∏ƒŸÇópà”.
	D3DXVECTOR3 vecAxisZ( 0.0f, 0.0f, 1.0f );

	//Zé≤Õﬁ∏ƒŸÇªÇÃÇ‡ÇÃÇâÒì]èÛë‘Ç…ÇÊÇËïœä∑Ç∑ÇÈ.
	D3DXVec3TransformCoord( 
		&vecAxisZ,	//(out).
		&vecAxisZ,	//.
		&mYaw );	//Yé≤âÒì]çsóÒ.

	//ï˚å¸Ç…ÇÊÇ¡ÇƒêiçsÇ≥ÇπÇÈílÇê›íË.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	switch( m_enDir )
	{
	case enDirection_Stop:
		break;
<<<<<<< HEAD
<<<<<<< HEAD
	case enDirection_Foward:	//ÔøΩÔΩΩOÔøΩÔΩΩi.
		//ÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩ*ÔøΩÔΩΩiÔøΩÔΩΩÔæü„ÇëÔΩøÔΩΩl(0.1f).
		m_vPos -= vecAxisZ * 0.15f * m_fSpd;
		break;
	case enDirection_BackWard:	//ÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩ.
=======
=======
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	case enDirection_Foward:	//ëOêi.
		//å¸Ç©Ç§ï˚å¸*êiÇﬂÇÈíl(0.1f).
		m_vPos -= vecAxisZ * 0.15f * m_fSpd;
		break;
	case enDirection_BackWard:	//å„ëﬁ.
<<<<<<< HEAD
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
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
<<<<<<< HEAD
	//m_enDir = enDirection_Stop;//ÔøΩÔΩΩÔøΩÔΩΩ~.
=======
	//m_enDir = enDirection_Stop;//í‚é~.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
	//m_enDir = enDirection_Stop;//í‚é~.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	//==================================================

}
//==================================================
<<<<<<< HEAD
<<<<<<< HEAD
//	ÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÈò°ÔΩªÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩXÔøΩÔΩΩVÔøΩÔΩΩÔæñÊí∞ÔΩøÔΩΩ.
=======
//	Ç†ÇΩÇËîªíËèÓïÒçXêVä÷êî.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
//	Ç†ÇΩÇËîªíËèÓïÒçXêVä÷êî.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
//==================================================
void clsCharaSkin::UpdateColState()
{
	ColState.vPos = m_vPos;
	ColState.fYaw = m_vRot.y;
}


//==================================================
<<<<<<< HEAD
<<<<<<< HEAD
//	ÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÈò°ÔΩªÔøΩÔΩΩÔøΩÔΩΩÔæåÊìæÔΩøÔΩΩÔøΩÔΩΩÔæå„Ç¢ÔøΩÔΩΩhÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩXÔøΩÔΩΩË¨´ÔΩæ.
=======
//	Ç†ÇΩÇËîªíËÇÃèÓïÒÇÃÉAÉhÉåÉXéÊìæ.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
//	Ç†ÇΩÇËîªíËÇÃèÓïÒÇÃÉAÉhÉåÉXéÊìæ.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
//==================================================
COL_STATE* clsCharaSkin::GetPointerCol()
{
	return &ColState;
}
//==================================================
<<<<<<< HEAD
<<<<<<< HEAD
//	ÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÔøΩÔΩΩÈò°ÔΩªÔøΩÔΩΩÔøΩÔΩΩp.
=======
//	Ç†ÇΩÇËîªíËóp.
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
=======
//	Ç†ÇΩÇËîªíËóp.
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



