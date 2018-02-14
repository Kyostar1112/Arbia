#include "Resource.h"
#include "DoorManager.h"


const float fMODEL_SCALE = 1.0f;
const double fANIM_SPD = 0.01;


//----- 髻ｳ -----//.
const char sALIAS_NAME[] = "DoorBreak";
const char sFILE_PATH[] = "SE\\300Trap\\900GateBreak.wav";
const int iVOL = 600;


//----- 雹ｴ繧峨ｌ蛻､螳夂畑 -----//.
const float fCOL_RANGE = 1.5f;
const float fCOL_HEIGHT = 3.0f;

//----- 螢√�隱ｿ謨ｴ -----//.
const float fSTAGE_WIDTH = 10.0f;
const float fSTAGE_WIDTH_HARF = fSTAGE_WIDTH / 2.0f;
const float fWALL_HEIGHT = 6.0f;
const float fWALL_Z = -0.75f;

const D3DXVECTOR3 vWALL_OFFSET = { -fSTAGE_WIDTH_HARF, fWALL_HEIGHT, fWALL_Z };

//蠕ｩ豢ｻ譎ゅ←繧後□縺第焔蜑阪↓縺�ｋ縺技.
const float fRE_SPAWN_POS_Z = 1.5f;

//----- 騾城℃ ------//
//騾城℃蠅�阜邱啝.
const float fALPHA_BORDER_Z = 0.5f;

//騾城℃騾溷ｺｦ.
const float fALPHA_SPD = 1.0f / 16.0f;
//騾城℃繧呈綾縺咎溷ｺｦ.
const float fALPHA_SPD_BACK = 1.0f / 32.0f;

//荳逡ｪ阮�￥縺励※繧.
const float fALPHA_LIMIT = 0.375f;
//荳逡ｪ豼�￥縺励※繧.
const float fALPHA_LIMIT_MAX = 2.0f;



//繧ｨ繝輔ぉ繧ｯ繝.
const float fEFFECT_Z_OFFSET = 12.0f;//謇峨�逹蝨ｰ菴咲ｽｮ.
const float fEFFECT_SCALE = 0.5f;
const D3DXVECTOR3 vEFFECT_SCALE = { fEFFECT_SCALE, fEFFECT_SCALE, fEFFECT_SCALE };
const float fEFFECT_SPD = 1.0f;
const int iEFFECT_PLAY_RAG = 20;//雹ｴ縺｣縺ｦ縺九ｉ逋ｺ逕溘☆繧九∪縺ｧ縺ｮ繝ｩ繧ｰ.




clsDoorMgr::clsDoorMgr()
{
	m_pGate = nullptr;
	m_pDoor = nullptr;
	m_pColWall = nullptr;
	m_pSe = nullptr;
	m_pEffect = nullptr;
}

clsDoorMgr::~clsDoorMgr()
{
	Release();
}



void clsDoorMgr::Create( HWND hWnd, ID3D11Device* pDevice, ID3D11DeviceContext* pContext, int iNo )
{
	if( m_pGate != nullptr ||
		m_pDoor != nullptr ||
		m_pColWall != nullptr ||
		m_pSe != nullptr ||
		m_pEffect != nullptr )
	{
	return;
	}


	//門.
	m_pGate = new clsCharaStatic;
	m_pGate->AttachModel(
		clsResource::GetInstance()->GetStaticModels(
			clsResource::enST_MODEL_MON ) );

	//謇.
	m_pDoor = new clsCharaSkin;

	CD3DXSKINMESH_INIT si;//skin_Init.
	si.hWnd = hWnd;
	si.pDevice = pDevice;
	si.pDeviceContext = pContext;

	m_pDoor->m_pModel = new clsD3DXSKINMESH;
	m_pDoor->m_pModel->Init( &si );

	m_pDoor->AttachModel(
		clsResource::GetInstance()->GetSkinModels(
			clsResource::enSK_MODEL_DOOR ) );

	m_pDoor->SetScale( fMODEL_SCALE );
	m_pDoor->SetAnimSpeed( fANIM_SPD );

	//螢∝愛螳.
	m_pColWall = new clsCharaStatic;
	m_pColWall->AttachModel(
		clsResource::GetInstance()->GetStaticModels(
			clsResource::enST_MODEL_SPIA_WALL ) );

	//雹ｴ繧峨ｌ蛻､螳夂畑.
	ColState.fRange = fCOL_RANGE;
	ColState.fHeight = fCOL_HEIGHT;

	//蜉ｹ譫憺浹.
	m_pSe = new clsSound;
	m_pSe->SetVolume( 0 );
	//蜷榊燕.
	char cAliasName[STR_BUFF_MAX] = "";
	strcat_s( cAliasName, sizeof( cAliasName ), sALIAS_NAME );
	//逡ｪ蜿ｷ.
	char cNumber[] = "  ";
	_itoa_s( iNo, cNumber, 10 );
	//蜷榊燕縺ｨ逡ｪ蜿ｷ蜷井ｽ.
	strcat_s( cAliasName, sizeof( cAliasName ), cNumber );
	//菴懈�.
	m_pSe->Open( sFILE_PATH, cAliasName, hWnd );
	//譛螟ｧ髻ｳ驥剰ｨｭ螳.
	m_pSe->SetMaxVolume( iVOL );


	m_pEffect = clsEffects::GetInstance();
	PlayEff();
	m_pEffect->Stop( m_ehDust );

	Init();
}

void clsDoorMgr::Init()
{
	ReStart();
	m_bBreak = false;
	SetColPos( m_vPos );
	m_dAnimTimer = 0.0;
	ChangeAnimMode( enANIM_IDLE );

}
//蠕ｩ豢ｻ譎ゅ�蛻晄悄蛹.
void clsDoorMgr::ReStart()
{
	m_fAlpha = fALPHA_LIMIT_MAX;
	m_bAlpha = false;
	m_bAlphaChange = false;

	m_iEffTimer = 0;
	m_bEffTimer = false;
}


void clsDoorMgr::Release()
{
	m_pEffect = nullptr;

	if( m_pSe != nullptr ){
		delete m_pSe;
		m_pSe = nullptr;
	}

	if( m_pColWall!= nullptr ){
		delete m_pColWall;
		m_pColWall = nullptr;
	}

	if( m_pDoor != nullptr ){
		delete m_pDoor;
		m_pDoor = nullptr;
	}

	if( m_pGate != nullptr ){
		delete m_pGate;
		m_pGate = nullptr;
	}
}

//謠冗判.
void clsDoorMgr::Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
	D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye )
{
	if( m_pDoor == nullptr || m_pGate == nullptr ) return;
	//.
//	m_pColWall->Render( mView, mProj, vLight, vEye );

	if( m_pDoor != nullptr ){
		//謇.
		m_pDoor->Render( mView, mProj, vLight, vEye );
	}
	if( m_pGate != nullptr ){
		//髢.
		m_pGate->Render( mView, mProj, vLight, vEye,
			D3DXVECTOR4( 1.0f, 1.0f, 1.0f, m_fAlpha ), m_bAlpha );
	}
}


void clsDoorMgr::SetPosition( D3DXVECTOR3 vPos )
{
	if( m_pDoor == nullptr ||
		m_pGate == nullptr ||
		m_pColWall == nullptr ){
		return;
	}

	m_vPos = vPos;

	//蟄仙�.
	if( m_pGate != nullptr )	m_pGate->SetPosition( m_vPos );
	if( m_pDoor != nullptr )	m_pDoor->SetPosition( m_vPos );

	if( m_pColWall != nullptr ){
		m_pColWall->SetPosition( m_vPos );
		m_pColWall->AddPosition( vWALL_OFFSET );
	}

	Init();
}


void clsDoorMgr::Update( float fEarZ )
{
	m_fEarZ = fEarZ;
	Animation();
	SetAlpha();


	//エフェクト再生.
	if( m_bEffTimer ){
		m_iEffTimer ++;
		if( m_iEffTimer >= iEFFECT_PLAY_RAG ){
			m_iEffTimer = 0;
			m_bEffTimer = false;
			PlayEff();
		}
	}
}



//============================================================
//	騾城℃蛟､縺ｮ險ｭ螳.
//============================================================
void clsDoorMgr::SetAlphaFlg( float fPlayerZ )
{
	//騾城℃荳ｭ.
	if( m_bAlphaChange ){
		//騾城℃繝輔Λ繧ｰON.
		m_bAlpha = true;
		//繝励Ξ繧､繝､繝ｼ縺悟･･縺ｫ縺�ｋ縺ｪ繧.
		if( fPlayerZ > m_vPos.z + fALPHA_BORDER_Z ){
			return;
		}
		//螳滉ｽ灘喧髢句ｧ.
		m_bAlphaChange = false;
	}
	//騾城℃荳ｭ縺ｧ縺ｯ縺ｪ縺.
	else{
		//繝励Ξ繧､繝､繝ｼ縺梧焔蜑阪↓縺�ｋ縺ｪ繧.
		if( fPlayerZ < m_vPos.z + fALPHA_BORDER_Z ){
			return;
		}
		//騾城℃髢句ｧ.
		m_bAlphaChange = true;
	}
}

//============================================================
//	騾城℃蛟､縺ｮ險ｭ螳.
//============================================================
void clsDoorMgr::SetAlpha()
{
	//騾城℃荳ｭ.
	if( m_bAlphaChange ){
		m_fAlpha -= fALPHA_SPD;
		if( m_fAlpha < fALPHA_LIMIT ){
			m_fAlpha = fALPHA_LIMIT;
		}
	}
	//螳滉ｽ灘喧荳ｭ.
	else{
		m_fAlpha += fALPHA_SPD_BACK;
		if( m_fAlpha > fALPHA_LIMIT_MAX ){
			m_fAlpha = fALPHA_LIMIT_MAX;
			m_bAlpha = false;
		}
	}
}


//============================================================
//	雹ｴ繧峨ｌ縺溘→縺.
//============================================================
D3DXVECTOR3 clsDoorMgr::DoorBreak()
{
	m_bBreak = true;

	PlaySe();

	D3DXVECTOR3 vReSpawnPos = m_vPos;
	vReSpawnPos.z -= fRE_SPAWN_POS_Z;

	ChangeAnimMode( enANIM_BREAK );

	m_bEffTimer = true;

	return vReSpawnPos;
}

//==================================================
//	縺ゅ◆繧雁愛螳夂畑.
//==================================================
void clsDoorMgr::SetColPos( D3DXVECTOR3 vPos )
{
	ColState.vPos = vPos;
}


//==================================================
//	蜉ｹ譫憺浹蜀咲函.
//==================================================
void clsDoorMgr::PlaySe(/* enSound enSe*/ )
{
	if( m_pSe == nullptr ) return;

	m_pSe->SeekToStart();
	m_pSe->SetVolume( iVOL );
	m_pSe->Play();
}

//============================================================
//	繝峨い縺ｮ繧｢繝九Γ.
//============================================================
void clsDoorMgr::Animation()
{
	if( m_pDoor == nullptr ) return;


	//ループしないアニメ.
	if( m_enAnimNo == enANIM_BREAK ){
		m_dAnimTimer += m_pDoor->m_pModel->GetAnimSpeed();
		
		const double dRATE = 5.0;//菴募埼｣帙�縺?.

		//迴ｾ蝨ｨ縺ｮ繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧堤ｵゅ∴縺溘ｉ.
		if( m_pDoor->m_pModel->GetAnimPeriod( m_enAnimNo ) - ( dANIM_ONE_FRAME_OVER_SOLUTION * dRATE ) <= m_dAnimTimer ){
			//蜍輔°縺ｪ縺上↑繧.
			ChangeAnimMode( enANIM_DEAD );
		}
	}
}

//============================================================
//	繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繝｢繝ｼ繝峨ｒ螟画峩.
//============================================================
void clsDoorMgr::ChangeAnimMode( enAnimation anim )
{
	if( m_pDoor == nullptr ) return;

	m_enAnimNo = anim;
	m_pDoor->ChangeAnimSet( m_enAnimNo );//繧｢繝九Γ繧ｻ繝�ヨ.
	m_dAnimTimer = 0.0;
}


//繧ｨ繝輔ぉ繧ｯ繝亥�逕.
void clsDoorMgr::PlayEff()
{
	if( m_pEffect == nullptr ) return;

	if( !m_pEffect->PlayCheck( m_ehDust ) ){
			D3DXVECTOR3 vEffPos = m_vPos;
			vEffPos.z += fEFFECT_Z_OFFSET;

		m_ehDust = m_pEffect->Play( clsEffects::enEfcType_DOOR_DUST, vEffPos );
		m_pEffect->SetSpd( m_ehDust, fEFFECT_SPD );
		m_pEffect->SetScale( m_ehDust, vEFFECT_SCALE );
	}
}
