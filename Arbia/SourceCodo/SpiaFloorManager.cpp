#include "Resource.h"
#include "SpiaFloorManager.h"


//髻ｳ.
//謖ｯ蜍.
#define ALIAS_NAME_VIB "SpiaFloorVib"
#define FILE_PATH_VIB "SE\\300Trap\\100SpiaVib.wav"
const int iVOL_VIB = 1000;

//荳翫′繧.
#define ALIAS_NAME_UP "SpiaFloorTop"
#define FILE_PATH_UP "SE\\300Trap\\110SpiaTop.wav"					
const int iVOL_UP = 1000;

//荳九′繧.
#define ALIAS_NAME_DOWN "SpiaFloorDown"
#define FILE_PATH_DOWN "SE\\300Trap\\130SpiaClose.wav"					
const int iVOL_DOWN = 1000;



//ステージ横幅.
const float STAGE_WIDHT = 10.0f;
//壁が槍の先端からどれだけずらすか.
const float WALL_OFFSET_Y = 0.4375f;

const int iFLOOR_MAX = 20;	//床槍の数.
const float fFLOOR_W_OFFSET = 0.5f;		//槍と槍の横の間隔.
const float fFLOOR_H_OFFSET = 0.0625f;		//奇数番目を床からどれだけ上げるか.
const float fFLOOR_H_OFFSET_SECOND = 0.25f;	//偶数番目を床からどれだけ上げるか.

clsSpiaFlorMgr::clsSpiaFlorMgr()
{
	m_iSpiaMax = 0;

	m_ppSpia = nullptr;
	m_pSpiaWall = nullptr;

	m_ppSe = nullptr;
}

clsSpiaFlorMgr::~clsSpiaFlorMgr()
{
	Release();
}

void clsSpiaFlorMgr::Release()
{
	//音.
	if( m_ppSe != nullptr ){
		for( int i=0; i<clsSpiaFloor::enSOUND_MAX; i++ ){
			m_ppSe[i]->Stop();
			m_ppSe[i]->Close();
			delete m_ppSe[i];
			m_ppSe[i] = nullptr;
		}
		delete[] m_ppSe;
		m_ppSe = nullptr;
	}
	//オブジェクト.
	if( m_ppSpia != nullptr ){
		for( int i=0; i<m_iSpiaMax; i++ ){
			m_ppSpia[i]->DetatchModel();
			delete m_ppSpia[i];
			m_ppSpia[i] = nullptr;
		}
		delete[] m_ppSpia;
		m_ppSpia = nullptr;
		m_iSpiaMax = 0;
	}
	if( m_pSpiaWall != nullptr ){
		delete m_pSpiaWall;
		m_pSpiaWall = nullptr;
	}
}


void clsSpiaFlorMgr::CreateSpia( HWND hWnd, int iNo )
{
	if( m_ppSpia != nullptr || m_iSpiaMax ) return;
	if( m_pSpiaWall != nullptr ) return;
	if( m_ppSe != nullptr ) return;


	//----- モデル -----//
	//槍.
	m_iSpiaMax = iFLOOR_MAX;
	m_ppSpia = new clsSpiaFloor*[m_iSpiaMax];
	for( int i=0; i<m_iSpiaMax; i++ ){
		m_ppSpia[i] = new clsSpiaFloor;

		m_ppSpia[i]->AttachModel( 
			clsResource::GetInstance()->GetStaticModels( 
				clsResource::enST_MODEL_SPIA ) );
	}

	//讒榊｣.
	if( m_pSpiaWall != nullptr ) return;
	m_pSpiaWall = new clsCharaStatic;
	m_pSpiaWall->AttachModel(
		clsResource::GetInstance()->GetStaticModels( 
			clsResource::enST_MODEL_SPIA_WALL ) );
	//----- 繝｢繝�Ν 邨ゆｺ -----//


	if( m_ppSe != nullptr ) return;
	//----- SE -----//
	//繧ｵ繧ｦ繝ｳ繝画ｧ矩菴.
	clsSound::SOUND_DATA tmpSData[clsSpiaFloor::enSOUND_MAX] =
	{
		{ ALIAS_NAME_VIB,	FILE_PATH_VIB,	iVOL_VIB	},
		{ ALIAS_NAME_UP,	FILE_PATH_UP,	iVOL_UP		},
		{ ALIAS_NAME_DOWN,	FILE_PATH_DOWN,	iVOL_DOWN	},
	};

	//繧ｵ繧ｦ繝ｳ繝峨け繝ｩ繧ｹ菴懈�.
	m_ppSe = new clsSound*[clsSpiaFloor::enSOUND_MAX];
	for( int i=0; i<clsSpiaFloor::enSOUND_MAX; i++ ){
		m_ppSe[i] = new clsSound;
		//迴ｾ髻ｳ驥丞�譛溷喧.
		m_ppSe[i]->SetVolume( 0 );
		//蜷榊燕.
		char cAliasName[STR_BUFF_MAX] = "";
		strcat_s( cAliasName, sizeof( cAliasName ), tmpSData[i].sAlias );
		//逡ｪ蜿ｷ.
		char cNumber[] = "  ";
		_itoa_s( iNo, cNumber, 10 );
		//蜷榊燕縺ｨ逡ｪ蜿ｷ蜷井ｽ.
		strcat_s( cAliasName, sizeof( cAliasName ), cNumber );
		//菴懈�.
		m_ppSe[i]->Open( tmpSData[i].sPath, cAliasName, hWnd );
		//譛螟ｧ髻ｳ驥剰ｨｭ螳.
		m_ppSe[i]->SetMaxVolume( tmpSData[i].iMaxVolume );
	}
	//----- SE 邨ゆｺ -----//


	Init();
}

void clsSpiaFlorMgr::Init()
{
	if( m_ppSpia == nullptr ) return;

	//槍.
	for( int i=0; i<m_iSpiaMax; i++ ){
		float fOffset = fFLOOR_H_OFFSET;
		bool bFlg = false;
		if( i % 2 != 0 ){
			//鬮倥＞繧�▽.
			fOffset = fFLOOR_H_OFFSET_SECOND;
			bFlg = true;
		}

		m_ppSpia[i]->SetPosition( 
		D3DXVECTOR3( 
			GetPositionX() - STAGE_WIDHT/2.0f + (float)i * fFLOOR_W_OFFSET + fFLOOR_W_OFFSET / 2.0f,
			GetPositionY() + fOffset, 
			GetPositionZ() ) );
		m_ppSpia[i]->Init( bFlg );
	}

	if( m_pSpiaWall == nullptr ) return;
	//槍壁座標.
	m_pSpiaWall->SetPosition( GetPosition() );
	m_pSpiaWall->AddPositionY( WALL_OFFSET_Y );
	m_pSpiaWall->AddPositionX( -STAGE_WIDHT / 2.0f );
}


void clsSpiaFlorMgr::Update( float fEarZ )
{
	if( m_ppSpia == nullptr || m_ppSe == nullptr || m_pSpiaWall == nullptr ) return;

	//どの音を鳴らすかのフラグ.
	clsSpiaFloor::enSound enSoundFlg;

	//蜍輔″.
	for( int i=0; i<m_iSpiaMax; i++ ){
		//動きに合わせてフラグを更新.
		enSoundFlg = m_ppSpia[i]->Update();
	}

	//蜉ｹ譫憺浹蜀咲函��AX縺ｯSpiaFloor蜀��蛻晄悄蛹紋ｽｿ縺｣縺ｦ縺�ｋ縺ｮ縺ｧ縺昴ｌ莉･荳翫〒縺ｯ魑ｴ繧峨＆縺ｪ縺�ｼ.
	if( enSoundFlg < clsSpiaFloor::enSOUND_MAX ){
		//鬟帙�蜃ｺ縺励◆繧峨℃縺励℃縺鈴浹繧呈ｭ｢繧√ｋ.
		if( enSoundFlg == clsSpiaFloor::enSOUND_UP ){
			m_ppSe[clsSpiaFloor::enSOUND_VIB]->Stop();
		}
		//蜀咲函.
		PlaySe( enSoundFlg, fEarZ );
	}

	//讒榊｣∝ｺｧ讓.
	m_pSpiaWall->SetPositionY( m_ppSpia[0]->GetPositionY() );
	//荳翫′縺｣縺ｦ繧区凾縺ｯ.蛻ｺ縺輔ｊ繧�☆縺
	//荳九′縺｣縺ｦ縺�ｋ譎ゅ�蛻ｺ縺輔ｊ縺ｫ縺上￥.
	if( m_ppSpia[0]->GetMode() == clsSpiaFloor::enSFM_UNDER ||
		m_ppSpia[0]->GetMode() == clsSpiaFloor::enSFM_DOWN ){
		m_pSpiaWall->AddPositionY( WALL_OFFSET_Y );
	}
	
}



void clsSpiaFlorMgr::Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
				 D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye )
{
	if( m_ppSpia == nullptr ) return;

	for( int i=0; i<m_iSpiaMax; i++ ){
		m_ppSpia[i]->Render( mView, mProj, vLight, vEye );
	}

//	//螢.
//	m_pSpiaWall->Render( mView, mProj, vLight, vEye );

}

void clsSpiaFlorMgr::SetPosition( D3DXVECTOR3 vPos )
{
	if( m_ppSpia == nullptr || m_pSpiaWall == nullptr ) return;

	m_vPos = vPos;

	//蟄仙�縺ｮ蠎ｧ讓.
	for( int i=0; i<m_iSpiaMax; i++ ){
		m_ppSpia[i]->SetPosition( 
			D3DXVECTOR3( 
				GetPositionX() - STAGE_WIDHT/2.0f + (float)i * fFLOOR_W_OFFSET,
				GetPositionY(), 
				GetPositionZ() ) );
	}

	//讒榊｣∝ｺｧ讓.
	m_pSpiaWall->SetPosition( GetPosition() );
	m_pSpiaWall->AddPositionY( WALL_OFFSET_Y );
	m_pSpiaWall->AddPositionX( -STAGE_WIDHT / 2.0f );
}

//讒阪�縺ゅ◆繧雁愛螳壽ュ蝣ｱ霑斐☆.
COL_STATE* clsSpiaFlorMgr::GetPointerSpiaCol( int i )
{
	if( m_ppSpia == nullptr ) return nullptr;
	return m_ppSpia[i]->GetPointerCol();
}

//讒阪�譛螟ｧ謨ｰ.
int clsSpiaFlorMgr::GetSpiaMax()
{
	return m_iSpiaMax;
}

clsCharaStatic*	clsSpiaFlorMgr::GetWallPointer()
{
	return m_pSpiaWall;
}


//============================================================
//	蜉ｹ譫憺浹.
//============================================================
void clsSpiaFlorMgr::PlaySe( clsSpiaFloor::enSound enSe, float fEarZ )
{
	if( m_ppSe == nullptr ) return;

  //再生する距離なら.
	int vol = ChangeVolumeDistance( fEarZ, m_vPos.z );
	if( vol ){
		m_ppSe[enSe]->GetMaxVolRate( vol );
		m_ppSe[enSe]->SeekToStart();
		m_ppSe[enSe]->SetVolume( vol );
		m_ppSe[enSe]->Play();
	}
	//蜀咲函縺励↑縺�ｷ晞屬縺ｪ繧.
	else{
		m_ppSe[enSe]->SetVolume( 0 );
	}
}

