#include "Common.h"

clsCommon::clsCommon()
{
	m_pDevice11 = nullptr;
	m_pDeviceContext11 = nullptr;
	m_pBlendState = nullptr;
};
clsCommon::~clsCommon()
{
	if( m_pBlendState != nullptr ){
		m_pBlendState->Release();
		m_pBlendState = nullptr;
	}

	//ここでは開放しない.
	m_pDeviceContext11 = nullptr;
	m_pDevice11 = nullptr;
};
clsCommon::clsCommon()
{
	m_pDevice11 = nullptr;
	m_pDeviceContext11 = nullptr;
	m_pBlendState = nullptr;
}


//============================================================
//透過(ｱﾙﾌｧﾌﾞﾚﾝﾄﾞ)設定の切り替え.
//============================================================
void clsCommon::SetBlend( bool flg )
{
	//ｱﾙﾌｧﾌﾞﾚﾝﾄﾞ用ﾌﾞﾚﾝﾄﾞｽﾃｰﾄ構造体.
	//pngﾌｧｲﾙ内にｱﾙﾌｧ情報があるので、
	//透過するようにﾌﾞﾚﾝﾄﾞｽﾃｰﾄを設定する.
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory( &blendDesc, sizeof( D3D11_BLEND_DESC ) );//初期化.

	blendDesc.IndependentBlendEnable
		= false;//false:RenderTarget[0]のﾒﾝﾊﾞｰのみが使用する.
				//true :RenderTarget[0～7]が使用できる.
				//      (ﾚﾝﾀﾞｰﾀｰｹﾞｯﾄ毎に独立したﾌﾞﾚﾝﾄﾞ処理)
	blendDesc.AlphaToCoverageEnable
		= false;//true :ｱﾙﾌｧﾄｩｶﾊﾞﾚｯｼﾞを使用する.
	blendDesc.RenderTarget[0].BlendEnable
		= flg;	//true :ｱﾙﾌｧﾌﾞﾚﾝﾄﾞを使用する.
	blendDesc.RenderTarget[0].SrcBlend	//元素材に対する設定.
		= D3D11_BLEND_SRC_ALPHA;		//	ｱﾙﾌｧﾌﾞﾚﾝﾄﾞを指定.
	blendDesc.RenderTarget[0].DestBlend	//重ねる素材に対する設定.
		= D3D11_BLEND_INV_SRC_ALPHA;	//	ｱﾙﾌｧﾌﾞﾚﾝﾄﾞの反転を指定.

	blendDesc.RenderTarget[0].BlendOp	//ﾌﾞﾚﾝﾄﾞｵﾌﾟｼｮﾝ.
		= D3D11_BLEND_OP_ADD;			//	ADD:加算合成.

	blendDesc.RenderTarget[0].SrcBlendAlpha	//元素材のｱﾙﾌｧに対する設定.
		= D3D11_BLEND_ONE;					//	そのまま使用.
	blendDesc.RenderTarget[0].DestBlendAlpha//重ねる素材のｱﾙﾌｧに対する設定.
		= D3D11_BLEND_ZERO;					//	何もしない.

	blendDesc.RenderTarget[0].BlendOpAlpha	//ｱﾙﾌｧのﾌﾞﾚﾝﾄﾞｵﾌﾟｼｮﾝ.
		= D3D11_BLEND_OP_ADD;				//	ADD:加算合成.

	blendDesc.RenderTarget[0].RenderTargetWriteMask	//ﾋﾟｸｾﾙ毎の書き込みﾏｽｸ.
		= D3D11_COLOR_WRITE_ENABLE_ALL;				//	全ての成分(RGBA)へのﾃﾞｰﾀの格納を許可する.

	//ﾌﾞﾚﾝﾄﾞｽﾃｰﾄ作成.
	if( FAILED(
		m_pDevice11->CreateBlendState(
			&blendDesc, &m_pBlendState ) ) )
	{
		MessageBox( NULL, "ﾌﾞﾚﾝﾄﾞｽﾃｰﾄ作成失敗", "clsCommon::SetBlend", MB_OK );
	}

	//ﾌﾞﾚﾝﾄﾞｽﾃｰﾄの設定.
	UINT mask = 0xffffffff;	//ﾏｽｸ値.
	m_pDeviceContext11->OMSetBlendState(
		m_pBlendState, NULL, mask );

}






