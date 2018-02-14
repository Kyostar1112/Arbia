#include "Resource.h"
#include "CoverManager.h"


//髻ｳ.
//霆九∩.
#define ALIAS_NAME_VIB "CoverVib"
#define FILE_PATH_VIB "SE\\300Trap\\310CoverVib.wav"
const int iVOL_VIB = 1000;

//縺ｱ縺九▲.
#define ALIAS_NAME_OPEN "CoverOpen"
#define FILE_PATH_OPEN "SE\\300Trap\\300Cover.wav"
const int iVOL_OPEN = 1000;




//螂･陦後・髟ｷ縺包ｼ磯浹縺ｮ逋ｺ逕滉ｽ咲ｽｮ繧偵←逵溘ｓ荳ｭ縺ｫ縺吶ｋ縺溘ａ縺ｫ蠢・ｦ・ｼ・
const float fOBJ_Z_LONG = 12.0f;

//繧ｹ繝・・繧ｸ縺ｮ荳ｭ蠢・°繧峨←繧後□縺代★繧峨☆縺句所縺ｳ縺昴・縺溘ａ縺ｮ遞ｮ.
const float fSTAGE_WIDHT = 10.0f;
const float fOFFSET_X = fSTAGE_WIDHT / 2.0f;

const float fSPD_OPEN = 0.125f;		//髢九￥縺ｨ縺阪・騾溷ｺｦ.
const float fSPD_CLOSE = 0.1875f;	//髢峨§繧九→縺阪・騾溷ｺｦ.

const int iVIB_DISTANCE = 8;	//髢九″縺九￠譎ゅ√御ｽ輔ヵ繝ｬ繝ｼ繝縺ｫ荳蝗槭崎ｧ貞ｺｦ繧貞虚縺九☆?.
const int iVIB_TIME = 60 * 1.75;//髢九″縺九￠譎る俣.
const int iHOLL_TIME = 90;	//遨ｴ縺ｨ縺励※縺ｮ譎る俣.

const float fOPEN_THETA = (float)( M_PI_2 - ( M_PI_4 / 16.0) );//荳豌励↓髢九￥隗貞ｺｦ縺ｯ縺薙％縺ｾ縺ｧ.
const float fVIB_THETA = (float)( M_PI_4 / 128.0 );//繧・▲縺上ｊ髢九￥隗貞ｺｦ縺ｯ縺薙％縺ｾ縺ｧ.


//Se逋ｺ菫｡邂・園縺ｮ謨ｰ.
const char cSE_NUM_MAX = 2;


clsCoverMgr::clsCoverMgr()
{
	m_ppCover = nullptr;
	m_pppSe = nullptr;
}

clsCoverMgr::~clsCoverMgr()
{
	Release();
}

void clsCoverMgr::CreateCover( HWND hWnd, int iNo )
{

	if( m_ppCover != nullptr ) return; 

	//----- 繝｢繝・Ν -----//
	//蜈ｨ菴・
	m_ppCover = new clsCharaStatic*[cCOVER_MAX];
	//蟾ｦ.
	m_ppCover[0] = new clsCharaStatic;
	m_ppCover[0]->AttachModel(
		clsResource::GetInstance()->GetStaticModels(
			clsResource::enST_MODEL_COVER_L ) );
	//蜿ｳ.
	m_ppCover[1] = new clsCharaStatic;
	m_ppCover[1]->AttachModel(
		clsResource::GetInstance()->GetStaticModels(
			clsResource::enST_MODEL_COVER_R ) );
	//----- 繝｢繝・Ν 邨ゆｺ・-----//




	if( m_pppSe != nullptr ) return;

	//----- SE -----//
	//繧ｵ繧ｦ繝ｳ繝画ｧ矩菴・
	clsSound::SOUND_DATA tmpSData[enSOUND_MAX] =
	{
		{ ALIAS_NAME_VIB,	FILE_PATH_VIB,	iVOL_VIB	},
		{ ALIAS_NAME_OPEN,	FILE_PATH_OPEN,	iVOL_OPEN	},
	};

	//繧ｵ繧ｦ繝ｳ繝峨け繝ｩ繧ｹ菴懈・.
	m_pppSe = new clsSound**[enSOUND_MAX];
	for( int i=0; i<enSOUND_MAX; i++ ){
		m_pppSe[i] = new clsSound*[enSOUND_MAX];//SE縺ｮ謨ｰ蛻・ｽ懊ｋ.
		for( int j=0; j<cSE_NUM_MAX; j++ ){
			m_pppSe[i][j] = new clsSound;//SE繧剃ｺ後▽縺ｫ蛻・ｺｫ.
			//迴ｾ髻ｳ驥丞・譛溷喧.
			m_pppSe[i][j]->SetVolume( 0 );
			//蜷榊燕.
			char cAliasName[STR_BUFF_MAX] = "";
			strcat_s( cAliasName, sizeof( cAliasName ), tmpSData[i].sAlias );
			//逡ｪ蜿ｷ.
			char cNumber[] = "  ";
			_itoa_s( iNo, cNumber, 10 );
			//蜷榊燕縺ｨ逡ｪ蜿ｷ蜷井ｽ・
			strcat_s( cAliasName, sizeof( cAliasName ), cNumber );
			//逋ｺ菫｡邂・園逡ｪ蜿ｷ.
			char cSeNumber[] = "  ";
			_itoa_s( j, cSeNumber, 10 );
			//蜷榊燕縺ｨ逡ｪ蜿ｷ蜷井ｽ・
			strcat_s( cAliasName, sizeof( cAliasName ), cSeNumber );
			//菴懈・.
			m_pppSe[i][j]->Open( tmpSData[i].sPath, cAliasName, hWnd );
			//譛螟ｧ髻ｳ驥剰ｨｭ螳・
			m_pppSe[i][j]->SetMaxVolume( tmpSData[i].iMaxVolume );
		}
	}
	//----- SE 邨ゆｺ・-----//



	Init();
}

void clsCoverMgr::Init()
{
	if( m_ppCover == nullptr ) return;

	m_enMove = enCM_FLOOR;
	m_iTimer = 0;
	for( char i=0; i<cCOVER_MAX; i++ ){
		m_ppCover[i]->SetPosition( m_vPos );
		m_ppCover[i]->SetRotationZ( 0.0f );
	}
	m_ppCover[0]->AddPositionX(-fOFFSET_X );
	m_ppCover[1]->AddPositionX( fOFFSET_X );
}




void clsCoverMgr::Release()
{
	if( m_pppSe != nullptr ){
		for( int i=0; i<enSOUND_MAX; i++ ){
			for( int j=0; j<cSE_NUM_MAX; j++ ){
				m_pppSe[i][j]->Stop();
				m_pppSe[i][j]->Close();
				delete m_pppSe[i][j];
				m_pppSe[i][j] = nullptr;
			}
			delete[] m_pppSe[i];
			m_pppSe[i] = nullptr;
		}
		delete[] m_pppSe;
		m_pppSe = nullptr;
	}

	if( m_ppCover != nullptr ){
		for( char i=0; i<cCOVER_MAX; i++ ){
			m_ppCover[i]->DetatchModel();
			delete m_ppCover[i];
			m_ppCover[i] = nullptr;
		}
		delete[] m_ppCover;
		m_ppCover = nullptr;
	}
}



//蜍輔″.
void clsCoverMgr::Update( float fEarZ )
{
	if( m_ppCover == nullptr ||  m_pppSe == nullptr ) return;
	switch( m_enMove )
	{
	case enCM_FLOOR:
		break;
	case enCM_VIB:
		m_iTimer ++;
		//蠕舌・↓髢九￥.
		if( m_iTimer % iVIB_DISTANCE == 0 ){
			m_ppCover[0]->AddRotationZ( -fVIB_THETA );
			m_ppCover[1]->AddRotationZ(  fVIB_THETA );
		}
		//髢九￥.
		if( m_iTimer > iVIB_TIME ){
			m_iTimer = 0;
			m_enMove = enCM_OPEN;
			//縺弱＠縺弱＠繧ｹ繝医ャ繝・
			for( int j=0; j<cSE_NUM_MAX; j++ ){
				m_pppSe[enSOUND_VIB][j]->Stop();
			}
			PlaySe( enSOUND_OPEN, fEarZ );
		}
		break;
	case enCM_OPEN:
		m_ppCover[0]->AddRotationZ(-fSPD_OPEN );
		m_ppCover[1]->AddRotationZ( fSPD_OPEN );
		if( m_ppCover[1]->GetRotationZ() >  fOPEN_THETA )
		{
			m_ppCover[0]->SetRotationZ( -fOPEN_THETA );
			m_ppCover[1]->SetRotationZ(  fOPEN_THETA );
			m_enMove = enCM_HOLL;
		}
		break;
	case enCM_HOLL:
		m_iTimer ++;
		if( m_iTimer > iHOLL_TIME ){
			m_iTimer = 0;
			m_enMove = enCM_CLOSE;
			PlaySe( enSOUND_OPEN, fEarZ );
		}
		break;
	case enCM_CLOSE:
		m_ppCover[0]->AddRotationZ( fSPD_CLOSE );
		m_ppCover[1]->AddRotationZ(-fSPD_CLOSE );
		if( m_ppCover[1]->GetRotationZ() > (float)M_PI )
		{
			m_ppCover[0]->SetRotationZ( 0.0f );
			m_ppCover[1]->SetRotationZ( 0.0f );
			m_enMove = enCM_FLOOR;
		}
		break;
	default:
		Init();
		break;
	}
}

//雕上・.
void clsCoverMgr::StmpCovor( float fEarZ )
{
	if( m_enMove == enCM_FLOOR ){
		m_iTimer = 0;
		m_enMove = enCM_VIB;
		PlaySe( enSOUND_VIB, fEarZ );
	}
}

//蠑ｷ縺剰ｸ上・.
void clsCoverMgr::StmpCovorStrong( float fEarZ )
{
	if( m_pppSe == nullptr ) return;

	if( m_enMove == enCM_FLOOR ||
		m_enMove == enCM_VIB ){
		m_iTimer = 0;
		m_enMove = enCM_OPEN;
		//縺弱＠縺弱＠繧ｹ繝医ャ繝・
		for( int j=0; j<cSE_NUM_MAX; j++ ){
			m_pppSe[enSOUND_VIB][j]->Stop();
		}
		PlaySe( enSOUND_OPEN, fEarZ );
	}
}

void clsCoverMgr::Render( D3DXMATRIX &mView, D3DXMATRIX &mProj,
	D3DXVECTOR3 &vLight, D3DXVECTOR3 &vEye )
{
	if( m_ppCover == nullptr ) return;

	for( char i=0; i<cCOVER_MAX; i++ ){
		m_ppCover[i]->Render( mView, mProj, vLight, vEye );
	}


}


//============================================================
//	蜉ｹ譫憺浹.
//============================================================
void clsCoverMgr::PlaySe( enSound enSe, float fEarZ )
{
	if( m_pppSe == nullptr ) return;
	//閠ｳ繧呈焔蜑阪→縺励※閠・∴縺輔○繧・縺ｩ逵溘ｓ荳ｭ縺九ｉ髻ｳ繧貞・縺・.
//	fEarZ -= OBJ_Z_LONG / 2.0f;

	for( int j=0; j<cSE_NUM_MAX; j++ ){
		//髻ｳ縺碁ｳｴ繧玖ｷ晞屬縺句凄縺・
		int vol = ChangeVolumeDistance( fEarZ, m_vPos.z );
		//蜀咲函縺吶ｋ霍晞屬縺ｪ繧・
		if( vol ){
			m_pppSe[enSe][j]->GetMaxVolRate( vol );
			m_pppSe[enSe][j]->SeekToStart();
			m_pppSe[enSe][j]->SetVolume( vol );
			m_pppSe[enSe][j]->Play();
		}
		//蜀咲函縺励↑縺・ｷ晞屬縺ｪ繧・
		else{
			m_pppSe[enSe][j]->SetVolume( 0 );
		}

		//0縺ｯ謇句燕縲・縺ｯ螂･.
		fEarZ -= fOBJ_Z_LONG;
	}
}
