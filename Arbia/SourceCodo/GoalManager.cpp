#include "Resource.h"
#include "GoalManager.h"

const float fMODEL_SCALE = 1.0f;
const double fANIM_SPD = 0.01;


//宝箱を開ける音.
#define ALIAS_NAME_OPEN "GoalBreak"
#define  FILE_PATH_OPEN "SE\\300Trap\\400TrBox.wav"
const int	  iVOL_OPEN = 1000;

////チェーン壊れる.
//#define ALIAS_NAME_KEY "GoalKeyBreak"
//#define  FILE_PATH_KEY "SE\\300Trap\\900GateBreak.wav"					
//const int	  iVOL_KEY = 1000;


//----- 蹴られ判定用 -----//.
const float fCOL_RANGE = 1.5f;
const float fCOL_HEIGHT = 1.0f;


//宝箱がどれだけ奥にあるか.
const float fTREASURE_Z = 22.0f;


//エフェクト.
const D3DXVECTOR3 vEFF_SCALE = { 0.5f, 0.5f, 0.5f };



clsGoalMgr::clsGoalMgr()
{
	m_pFloor = nullptr;
	m_pTreasurer = nullptr;
	m_pTrBoxCol = nullptr;

	

	m_ppSe = nullptr;
	m_pEffect = nullptr;
}

clsGoalMgr::~clsGoalMgr()
{
	Release();
}

void clsGoalMgr::Create( HWND hWnd, ID3D11Device* pDevice, ID3D11DeviceContext* pContext )
{
	if( m_pFloor != nullptr ||
		m_pTreasurer != nullptr ||
		m_pTrBoxCol != nullptr ||
		m_ppSe != nullptr ||
		m_pEffect != nullptr )
	{
		return;
	}

	//床.
	m_pFloor = new clsCharaStatic;
	m_pFloor->AttachModel(
		clsResource::GetInstance()->GetStaticModels(
			clsResource::enST_MODEL_GOOL ) );

	//宝箱あたり.
	m_pTrBoxCol = new clsCharaStatic;
	m_pTrBoxCol->AttachModel(
		clsResource::GetInstance()->GetStaticModels(
			clsResource::enST_MODEL_TR_BOX_COL ) );

	//宝箱.
	m_pTreasurer = new clsCharaSkin;

	CD3DXSKINMESH_INIT si;//skin_Init.
	si.hWnd = hWnd;
	si.pDevice = pDevice;
	si.pDeviceContext = pContext;

	m_pTreasurer->m_pModel = new clsD3DXSKINMESH;
	m_pTreasurer->m_pModel->Init( &si );

	m_pTreasurer->AttachModel(
		clsResource::GetInstance()->GetSkinModels(
			clsResource::enSK_MODEL_TR_BOX ) );

	m_pTreasurer->SetScale( fMODEL_SCALE );
	m_pTreasurer->SetAnimSpeed( fANIM_SPD );


	//蹴られ判定用.
	ColState.fRange = fCOL_RANGE;
	ColState.fHeight = fCOL_HEIGHT;

	//----- SE -----//
	//サウンド構造体.
	clsSound::SOUND_DATA tmpSData[] =
	{
		{ ALIAS_NAME_OPEN,	FILE_PATH_OPEN,	iVOL_OPEN	},
	};
	m_iSeMax = sizeof( tmpSData ) / sizeof( tmpSData[0] );

	//サウンドクラス作成.
	m_ppSe = new clsSound*[m_iSeMax];
	for( int i=0; i<m_iSeMax; i++ ){
		m_ppSe[i] = new clsSound;
		//現音量初期化.
		m_ppSe[i]->SetVolume( 0 );
		//名前.
		char cAliasName[STR_BUFF_MAX] = "";
		strcat_s( cAliasName, sizeof( cAliasName ), tmpSData[i].sAlias );
		//作成.
		m_ppSe[i]->Open( tmpSData[i].sPath, cAliasName, hWnd );
		//最大音量設定.
		m_ppSe[i]->SetMaxVolume( tmpSData[i].iMaxVolume );
	}
	//----- SE 終了 -----//

	//エフェクト.
	if( m_pEffect == nullptr ){
		m_pEffect = clsEffects::GetInstance();
	}

	Init();
}
void clsGoalMgr::Init()
{
	m_bOpen = false;
	SetColPos( m_vPos );
	m_dAnimTimer = 0.0;
	ChangeAnimMode( enANIM_IDLE );

	//エフェクト止める.
	if( m_pEffect == nullptr ) return;
	m_pEffect->Stop( m_ehOpen );
	m_pEffect->Stop( m_ehLoop );
}


void clsGoalMgr::Release()
{
	m_pEffect = nullptr;


	if( m_ppSe != nullptr ){
		for( int i=0; i<m_iSeMax; i++ ){
			m_ppSe[i]->Close();
			delete m_ppSe[i];
			m_ppSe[i] = nullptr;
		}
		delete[] m_ppSe;
		m_ppSe = nullptr;
	}

	if( m_pTreasurer != nullptr ){
		delete m_pTreasurer;
		m_pTreasurer = nullptr;
	}

	if( m_pTrBoxCol!= nullptr ){
		delete m_pTrBoxCol;
		m_pTrBoxCol = nullptr;
	}


	if( m_pFloor!= nullptr ){
		delete m_pFloor;
		m_pFloor = nullptr;
	}
}

//描画.
void clsGoalMgr::Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
	D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye )
{
	if( m_pFloor == nullptr || m_pTreasurer == nullptr ) return;

	//床.
	m_pFloor->Render( mView, mProj, vLight, vEye );
	//箱.
	m_pTreasurer->Render( mView, mProj, vLight, vEye );

//	m_pTrBoxCol->Render( mView, mProj, vLight, vEye );
}


void clsGoalMgr::SetPosition( D3DXVECTOR3 vPos )
{
	if( m_pFloor == nullptr ||
		m_pTreasurer == nullptr ||
		m_pTrBoxCol == nullptr )
	{
		return;
	}

	m_vPos = vPos;

	//子分.
	if( m_pFloor != nullptr ){
		m_pFloor->SetPosition( m_vPos );
	}
	if( m_pTreasurer != nullptr ){
		m_pTreasurer->SetPosition( m_vPos );
		m_pTreasurer->AddPositionZ( fTREASURE_Z );
	}

	if( m_pTrBoxCol != nullptr && m_pTreasurer != nullptr ){
		m_pTrBoxCol->SetPosition( m_pTreasurer->GetPosition() );
	}

	SetColPos( m_vPos );

	Init();
}


void clsGoalMgr::Update( float fEarZ )
{
	if( m_pEffect == nullptr ) return;

//	m_fEarZ = fEarZ;
	Animation();

	//エフェクト.
	if( m_pEffect == nullptr ) return;

	if( m_bOpen ){
		//開くエフェクトが終わってる.
		if( !m_pEffect->PlayCheck( m_ehOpen ) ){
			m_ehLoop = m_pEffect->Play( clsEffects::enEfcType_TRB_LOOP, m_pTreasurer->GetPosition() );
			m_pEffect->SetScale( m_ehLoop, vEFF_SCALE );
		}
	}
}





//============================================================
//	蹴られたとき.
//============================================================
void clsGoalMgr::BoxBreak()
{
	if( m_pEffect == nullptr ) return;

	m_bOpen = true;

	PlaySe( enSOUND_OPEN );

	ChangeAnimMode( enANIM_OPEN );

	//エフェクト再生.
	if( m_pEffect == nullptr ) return;

	if( !m_pEffect->PlayCheck( m_ehOpen ) ){
		m_ehOpen = m_pEffect->Play( clsEffects::enEfcType_TRB_OPEN, m_pTreasurer->GetPosition() );
		m_pEffect->SetScale( m_ehOpen, vEFF_SCALE );
	}
	if( !m_pEffect->PlayCheck( m_ehLoop ) ){
		m_ehLoop = m_pEffect->Play( clsEffects::enEfcType_TRB_LOOP, m_pTreasurer->GetPosition() );
		m_pEffect->SetScale( m_ehLoop, vEFF_SCALE );
	}

}


//============================================================
//	効果音再生.
//============================================================
void clsGoalMgr::PlaySe( enSound enSe )
{
	if( m_ppSe == nullptr ) return;

#if 0
	//再生する距離なら.
	int vol = ChangeVolumeDistance( m_fEarZ, m_vPos.z );
vol = 1;
	if( vol ){
		m_ppSe[enSe]->GetMaxVolRate( vol );
		m_ppSe[enSe]->SeekToStart();
		m_ppSe[enSe]->SetVolume( vol );
m_ppSe[enSe]->SetVolume( iVOL );
		m_ppSe[enSe]->Play();
	}
	//再生しない距離なら.
	else{
		m_ppSe[enSe]->SetVolume( 0 );
	}
#else
	m_ppSe[enSe]->SeekToStart();
	m_ppSe[enSe]->SetVolume( iVOL_OPEN );
	m_ppSe[enSe]->Play();
#endif
}


//==================================================
//	あたり判定用.
//==================================================
void clsGoalMgr::SetColPos( D3DXVECTOR3 vPos )
{
	ColState.vPos = vPos;
	ColState.vPos.z += fTREASURE_Z;
}

//============================================================
//	箱のアニメ.
//============================================================
void clsGoalMgr::Animation()
{
	if( m_pTreasurer == nullptr ) return;

	//ループしないアニメ.
	if( m_enAnimNo == enANIM_OPEN ){
		m_dAnimTimer += m_pTreasurer->m_pModel->GetAnimSpeed();
		
		const double dRATE = 5.0;//何倍飛ばす?.

		//現在のアニメーションを終えたら.
		if( m_pTreasurer->m_pModel->GetAnimPeriod( m_enAnimNo ) - ( dANIM_ONE_FRAME_OVER_SOLUTION * dRATE ) <= m_dAnimTimer ){
			//動かなくなる.
			ChangeAnimMode( enANIM_DEAD );
		}
	}
}

//============================================================
//	アニメーションモードを変更.
//============================================================
void clsGoalMgr::ChangeAnimMode( enAnimation anim )
{
	if( m_pTreasurer == nullptr ) return;

	m_enAnimNo = anim;
	m_pTreasurer->ChangeAnimSet( m_enAnimNo );//アニメセット.
	m_dAnimTimer = 0.0;
}
