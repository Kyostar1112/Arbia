#include "Resource.h"
#include "GoalManager.h"

const float fMODEL_SCALE = 1.0f;
const double fANIM_SPD = 0.01;


//螳晉ｮｱ繧帝幕縺代ｋ髻ｳ.
#define ALIAS_NAME_OPEN "GoalBreak"
#define  FILE_PATH_OPEN "SE\\300Trap\\400TrBox.wav"
const int	  iVOL_OPEN = 1000;

////繝√ぉ繝ｼ繝ｳ螢翫ｌ繧.
//#define ALIAS_NAME_KEY "GoalKeyBreak"
//#define  FILE_PATH_KEY "SE\\300Trap\\900GateBreak.wav"					
//const int	  iVOL_KEY = 1000;


//----- 雹ｴ繧峨ｌ蛻､螳夂畑 -----//.
const float fCOL_RANGE = 1.5f;
const float fCOL_HEIGHT = 1.0f;


//螳晉ｮｱ縺後←繧後□縺大･･縺ｫ縺ゅｋ縺.
const float fTREASURE_Z = 22.0f;


//繧ｨ繝輔ぉ繧ｯ繝.
const D3DXVECTOR3 vEFF_SCALE = { 0.5f, 0.5f, 0.5f };



clsGoalMgr::clsGoalMgr()
{
	m_pFloor = nullptr;
	m_pTreasurer = nullptr;
	m_pTrBoxCol = nullptr;

	m_ppSe = nullptr;

	m_pEffect = nullptr;
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

	//螳晉ｮｱ縺ゅ◆繧.
	m_pTrBoxCol = new clsCharaStatic;
	m_pTrBoxCol->AttachModel(
		clsResource::GetInstance()->GetStaticModels(
			clsResource::enST_MODEL_TR_BOX_COL ) );

	//螳晉ｮｱ.
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


	//雹ｴ繧峨ｌ蛻､螳夂畑.
	ColState.fRange = fCOL_RANGE;
	ColState.fHeight = fCOL_HEIGHT;

	//----- SE -----//
	//繧ｵ繧ｦ繝ｳ繝画ｧ矩菴.
	clsSound::SOUND_DATA tmpSData[] =
	{
		{ ALIAS_NAME_OPEN,	FILE_PATH_OPEN,	iVOL_OPEN	},
	};
	m_iSeMax = sizeof( tmpSData ) / sizeof( tmpSData[0] );

	//繧ｵ繧ｦ繝ｳ繝峨け繝ｩ繧ｹ菴懈�.
	m_ppSe = new clsSound*[m_iSeMax];
	for( int i=0; i<m_iSeMax; i++ ){
		m_ppSe[i] = new clsSound;
		//迴ｾ髻ｳ驥丞�譛溷喧.
		m_ppSe[i]->SetVolume( 0 );
		//蜷榊燕.
		char cAliasName[STR_BUFF_MAX] = "";
		strcat_s( cAliasName, sizeof( cAliasName ), tmpSData[i].sAlias );
		//菴懈�.
		m_ppSe[i]->Open( tmpSData[i].sPath, cAliasName, hWnd );
		//譛螟ｧ髻ｳ驥剰ｨｭ螳.
		m_ppSe[i]->SetMaxVolume( tmpSData[i].iMaxVolume );
	}
	//----- SE 邨ゆｺ -----//

	//繧ｨ繝輔ぉ繧ｯ繝.
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

//謠冗判.
void clsGoalMgr::Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
	D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye )
{
	if( m_pFloor == nullptr || m_pTreasurer == nullptr ) return;

	//床.
	m_pFloor->Render( mView, mProj, vLight, vEye );
	//邂ｱ.
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

	//蟄仙�.
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

	//繧ｨ繝輔ぉ繧ｯ繝.
	if( m_pEffect == nullptr ) return;

	if( m_bOpen ){
		//髢九￥繧ｨ繝輔ぉ繧ｯ繝医′邨ゅｏ縺｣縺ｦ繧.
		if( !m_pEffect->PlayCheck( m_ehOpen ) ){
			m_ehLoop = m_pEffect->Play( clsEffects::enEfcType_TRB_LOOP, m_pTreasurer->GetPosition() );
			m_pEffect->SetScale( m_ehLoop, vEFF_SCALE );
		}
	}
}





//============================================================
//	雹ｴ繧峨ｌ縺溘→縺.
//============================================================
void clsGoalMgr::BoxBreak()
{
	if( m_pEffect == nullptr ) return;

	m_bOpen = true;

	PlaySe( enSOUND_OPEN );

	ChangeAnimMode( enANIM_OPEN );

	//繧ｨ繝輔ぉ繧ｯ繝亥�逕.
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
//	蜉ｹ譫憺浹蜀咲函.
//============================================================
void clsGoalMgr::PlaySe( enSound enSe )
{
	if( m_ppSe == nullptr ) return;
#if 0
	//蜀咲函縺吶ｋ霍晞屬縺ｪ繧.
	int vol = ChangeVolumeDistance( m_fEarZ, m_vPos.z );
vol = 1;
	if( vol ){
		m_ppSe[enSe]->GetMaxVolRate( vol );
		m_ppSe[enSe]->SeekToStart();
		m_ppSe[enSe]->SetVolume( vol );
m_ppSe[enSe]->SetVolume( iVOL );
		m_ppSe[enSe]->Play();
	}
	//蜀咲函縺励↑縺�ｷ晞屬縺ｪ繧.
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
//	縺ゅ◆繧雁愛螳夂畑.
//==================================================
void clsGoalMgr::SetColPos( D3DXVECTOR3 vPos )
{
	ColState.vPos = vPos;
	ColState.vPos.z += fTREASURE_Z;
}

//============================================================
//	邂ｱ縺ｮ繧｢繝九Γ.
//============================================================
void clsGoalMgr::Animation()
{
	if( m_pTreasurer == nullptr ) return;
	//ループしないアニメ.
	if( m_enAnimNo == enANIM_OPEN ){
		m_dAnimTimer += m_pTreasurer->m_pModel->GetAnimSpeed();
		
		const double dRATE = 5.0;//菴募埼｣帙�縺?.

		//迴ｾ蝨ｨ縺ｮ繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧堤ｵゅ∴縺溘ｉ.
		if( m_pTreasurer->m_pModel->GetAnimPeriod( m_enAnimNo ) - ( dANIM_ONE_FRAME_OVER_SOLUTION * dRATE ) <= m_dAnimTimer ){
			//蜍輔°縺ｪ縺上↑繧.
			ChangeAnimMode( enANIM_DEAD );
		}
	}
}

//============================================================
//	繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繝｢繝ｼ繝峨ｒ螟画峩.
//============================================================
void clsGoalMgr::ChangeAnimMode( enAnimation anim )
{
	if( m_pTreasurer == nullptr ) return;
	m_enAnimNo = anim;
	m_pTreasurer->ChangeAnimSet( m_enAnimNo );//繧｢繝九Γ繧ｻ繝�ヨ.
	m_dAnimTimer = 0.0;
}
