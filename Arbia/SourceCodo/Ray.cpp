#include "Ray.h"

//�ｼ�ｪ�ｰ��橸ｾ鯉ｽｧ�ｲ�吝錐(��ｾ橸ｽｨ�夲ｽｸ��ｾ倥ｂ蜷ｫ繧)(\\).
const char SHADER_NAME[] = "Shader\\Ray.hlsl";
//�ｴ�晢ｾ�ｾ假ｽｰ�趣ｾ滂ｽｲ�晢ｾ�錐(��ｾ橸ｽｨ�夲ｽｸ��ｾ倥ｂ蜷ｫ繧)(\\).
const char ENT_VER_NAME[] = "VS";
const char ENT_PIX_NAME[] = "PS";

clsRay::clsRay()
{
//	ZeroMemory( this, sizeof( clsRay ) );
	m_pVertexShader = nullptr;	
	m_pVertexLayout = nullptr;	
	m_pPixelShader = nullptr;		
	m_pConstantBuffer = nullptr;	
	m_pVertexBuffer = nullptr;	
}

clsRay::~clsRay()
{
	SAFE_RELEASE( m_pVertexBuffer );
	SAFE_RELEASE( m_pConstantBuffer );
	SAFE_RELEASE( m_pPixelShader );
	SAFE_RELEASE( m_pVertexLayout );
	SAFE_RELEASE( m_pVertexShader );
}


//============================================================
//	蛻晄悄蛹.
//============================================================
HRESULT clsRay::Init( ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 )
{
	m_pDevice11 = pDevice11;
	m_pDeviceContext11 = pContext11;

	if( FAILED( InitShader() ) ){
		return E_FAIL;
	}
	if( FAILED( InitModel() ) ){
		return E_FAIL;
	}

	return S_OK;
}


//============================================================
//謠冗判.
//============================================================
void clsRay::Render( D3DXMATRIX& mView, D3DXMATRIX& mProj )
{
	//�懶ｽｰ�呻ｾ�ｾ櫁｡悟�.
	D3DXMATRIX	mWorld;

	//蝗櫁ｻ｢陦悟�縲∫ｧｻ蜍戊｡悟�.
	D3DXMATRIX mRot, mTran;

	//回転行列作成(ｹﾞｰﾑ、ｽﾃｰｼﾞ次第).
	D3DXMatrixRotationY( &mRot, m_Ray.fYaw );


	//蟷ｳ陦檎ｧｻ蜍穂ｽ懈�.
	D3DXMatrixTranslation( &mTran,
		m_Ray.vPos.x, m_Ray.vPos.y, m_Ray.vPos.z );

	//�懶ｽｰ�呻ｾ�ｾ櫁｡悟�菴懈�.
	mWorld = mRot * mTran;

	//菴ｿ逕ｨ縺吶ｋ�ｼ�ｪ�ｰ��槭�逋ｻ骭ｲ.
	m_pDeviceContext11->VSSetShader( m_pVertexShader, NULL, 0 );
	m_pDeviceContext11->PSSetShader( m_pPixelShader,  NULL, 0 );


	//�ｼ�ｪ�ｰ��槭��ｺ�晢ｽｽ��晢ｾ�ｾ奇ｾ橸ｽｯ�鯉ｽｧ縺ｫ蜷�ｨｮ��ｾ橸ｽｰ�繧呈ｸ｡縺.
	D3D11_MAPPED_SUBRESOURCE pData;
	SHADER_CONSTANT_BUFFER cd;	//�ｺ�晢ｽｽ��晢ｾ�ｾ奇ｾ橸ｽｯ�鯉ｽｧ.
	//�奇ｾ橸ｽｯ�鯉ｽｧ蜀����ｾ橸ｽｰ�縺ｮ譖ｸ縺肴婿髢句ｧ区凾縺ｫmap.
	if( SUCCEEDED(
		m_pDeviceContext11->Map(
			m_pConstantBuffer, 0,
			D3D11_MAP_WRITE_DISCARD, 0, &pData ) ) )
	{
		//�懶ｽｰ�呻ｾ�ｾ,�ｶ�抵ｾ,�鯉ｾ滂ｾ幢ｽｼ�橸ｽｪ�ｸ�ｼ�ｮ�晁｡悟�繧呈ｸ｡縺.
		D3DXMATRIX m = mWorld * mView * mProj;
		D3DXMatrixTranspose( &m, &m );	//陦悟�繧定ｻ｢鄂ｮ縺吶ｋ.
					//陦悟�縺ｮ險育ｮ玲婿豕輔′DirectX縺ｨGPU縺ｧ逡ｰ縺ｪ繧九◆繧.
		cd.mWVP = m;

		//�ｶ�暦ｽｰ.
		cd.vColor = D3DXVECTOR4 ( 1.0f, 0.0f, 1.0f, 1.0f );



		memcpy_s( pData.pData, pData.RowPitch,
			(void*)( &cd ), sizeof( cd ) );

		m_pDeviceContext11->Unmap( m_pConstantBuffer, 0 );
	}

	//縺薙��ｺ�晢ｽｽ��晢ｾ�ｾ奇ｾ橸ｽｯ�鯉ｽｧ繧偵←縺ｮ�ｼ�ｪ�ｰ��槭〒菴ｿ縺�°?.
	m_pDeviceContext11->VSSetConstantBuffers(
		0, 1, &m_pConstantBuffer );
	m_pDeviceContext11->PSSetConstantBuffers(
		0, 1, &m_pConstantBuffer );

	//鬆らせ�奇ｾ橸ｽｯ�鯉ｽｧ繧抵ｽｾ�ｯ�.
	UINT stride = sizeof( MODEL_VERTEX );	//��ｾ橸ｽｰ�縺ｮ髢馴囈.
	UINT offset = 0;
	m_pDeviceContext11->IASetVertexBuffers(
		0, 1, &m_pVertexBuffer, &stride, &offset );

	//鬆らせ�ｲ�晢ｾ鯉ｾ滂ｽｯ��ｾ夲ｽｲ�ｱ�ｳ��ｒ�ｾ�ｯ�.
	m_pDeviceContext11->IASetInputLayout( m_pVertexLayout );

	//�鯉ｾ滂ｾ假ｾ撰ｾ�ｽｨ�鯉ｾ槭���ｾ趣ｾ滂ｾ幢ｽｼ�橸ｽｰ繧抵ｽｾ�ｯ�.
	m_pDeviceContext11->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_LINELIST );

	//�鯉ｾ滂ｾ假ｾ撰ｾ�ｽｨ�鯉ｾ槭ｒ�夲ｾ晢ｾ�橸ｾ假ｾ晢ｽｸ�.
	m_pDeviceContext11->Draw( 2, 0 );

}


//============================================================
//	HLSL�鯉ｽｧ�ｲ�吶ｒ隱ｭ縺ｿ霎ｼ縺ｿ�ｼ�ｪ�ｰ��槭ｒ菴懈�縺吶ｋ.
//	HLSL:HIGE-LEVEL-SHADER-LANGUAGE.
//============================================================
HRESULT clsRay::InitShader()
{
	ID3DBlob* pCompiledShader = nullptr;
	ID3DBlob* pErrors = nullptr;

	UINT uCompileFlag = 0;

#ifdef _DEBUG
	uCompileFlag
		= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION; 
#endif//#ifdef _DEBUG


	//HLSL縺九ｉ�奇ｾ橸ｽｰ��ｽｯ�ｸ�ｽ�ｼ�ｪ�ｰ��槭��鯉ｾ橸ｾ幢ｾ鯉ｾ槭ｒ菴懈�.
	if( FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,	//�ｼ�ｪ�ｰ��橸ｾ鯉ｽｧ�ｲ�吝錐(HLSL�鯉ｽｧ�ｲ�).
			NULL,			//�擾ｽｸ�帛ｮ夂ｾｩ縺ｮ驟榊�縺ｸ縺ｮ�趣ｾ滂ｽｲ�晢ｾ(譛ｪ菴ｿ逕ｨ).
			NULL,			//�ｲ�晢ｽｸ�呻ｽｰ��ｾ橸ｾ鯉ｽｧ�ｲ�吶ｒ謇ｱ縺�ｽｲ�晢ｾ�ｰ�鯉ｽｪ�ｰ�ｽ縺ｸ縺ｮ�趣ｾ滂ｽｲ�晢ｾ(譛ｪ菴ｿ逕ｨ).
			ENT_VER_NAME,		//�ｼ�ｪ�ｰ��橸ｽｴ�晢ｾ�ｾ假ｽｰ�趣ｾ滂ｽｲ�晢ｾ�未謨ｰ縺ｮ蜷榊燕.
			"vs_5_0",		//�ｼ�ｪ�ｰ��槭��難ｾ�ｾ橸ｾ吶ｒ謖�ｮ壹☆繧区枚蟄怜�(�鯉ｾ滂ｾ幢ｾ鯉ｽｧ�ｲ�).
			uCompileFlag,	//�ｼ�ｪ�ｰ��橸ｽｺ�晢ｾ奇ｾ滂ｽｲ�呻ｾ鯉ｾ暦ｽｸ�.
			0,				//�ｴ�鯉ｽｪ�ｸ��ｽｺ�晢ｾ奇ｾ滂ｽｲ�呻ｾ鯉ｾ暦ｽｸ�(譛ｪ菴ｿ逕ｨ).
			NULL,			//�ｽ�夲ｽｯ��ｾ橸ｾ趣ｾ滂ｾ晢ｾ鯉ｾ滂ｽｲ�晢ｾ�ｰ�鯉ｽｪ�ｰ�ｽ縺ｸ縺ｮ�趣ｾ滂ｽｲ�晢ｾ(譛ｪ菴ｿ逕ｨ).
			&pCompiledShader,//�鯉ｾ橸ｾ幢ｾ鯉ｾ槭ｒ譬ｼ邏阪☆繧具ｾ抵ｾ難ｾ倥∈縺ｮ�趣ｾ滂ｽｲ�晢ｾ.
			&pErrors,		//�ｴ�暦ｽｰ縺ｨ隴ｦ蜻贋ｸ隕ｧ繧呈ｼ邏阪☆繧具ｾ抵ｾ難ｾ倥∈縺ｮ�趣ｾ滂ｽｲ�晢ｾ.
			NULL ) ) )		//謌ｻ繧雁､縺ｸ縺ｮ�趣ｾ滂ｽｲ�晢ｾ(譛ｪ菴ｿ逕ｨ).
	{
		MessageBox( NULL, "hlsl(vs)読み込み失敗", "clsRay::InitShader", MB_OK );

		return E_FAIL;
	}
	SAFE_RELEASE( pErrors );

	//荳願ｨ倥〒菴懈�縺励◆�鯉ｾ橸ｾ幢ｾ鯉ｾ槭°繧峨鯉ｾ奇ｾ橸ｽｰ��ｽｯ�ｸ�ｽ�ｼ�ｪ�ｰ��槭阪ｒ菴懈�.
	if( FAILED(
		m_pDevice11->CreateVertexShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			NULL,
			&m_pVertexShader) ) )//(out)�奇ｾ橸ｽｰ��ｽｯ�ｸ�ｽ�ｼ�ｪ�ｰ��.
	{
		MessageBox( NULL, "vs菴懈�螟ｱ謨", "clsRay::InitShader", MB_OK );
		return E_FAIL;
	}

	//鬆らせ�ｲ�晢ｾ鯉ｾ滂ｽｯ��ｾ夲ｽｲ�ｱ�ｳ��ｒ螳夂ｾｩ.
	D3D11_INPUT_ELEMENT_DESC layout[] = 
	{
		{
			"POSITION",						//菴咲ｽｮ.
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,	//DXGI縺ｮ�鯉ｽｫ�ｰ�擾ｽｯ�(32bit float蝙*3).
			0,
			0,								//��ｾ橸ｽｰ�縺ｮ髢句ｧ倶ｽ咲ｽｮ.
			D3D11_INPUT_PER_VERTEX_DATA, 0
		},
	};
	//鬆らせ�ｲ�晢ｾ鯉ｾ滂ｽｯ��ｾ夲ｽｲ�ｱ�ｳ���驟榊�隕∫ｴ謨ｰ繧堤ｮ怜�.
	UINT numElements = sizeof( layout ) / sizeof( layout[0] );//.

	//鬆らせ�ｲ�晢ｾ鯉ｾ滂ｽｯ��ｾ夲ｽｲ�ｱ�ｳ���菴懈�.
	if( FAILED(
		m_pDevice11->CreateInputLayout(
			layout,
			numElements,
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			&m_pVertexLayout ) ) )//(out)鬆らせ�ｲ�晢ｾ鯉ｾ滂ｽｯ��ｾ夲ｽｲ�ｱ�ｳ�.
	{
		MessageBox( NULL, "頂点ｲﾝﾌﾟｯﾄﾚｲｱｳﾄ作成失敗", "clsRay::InitShader", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pCompiledShader );



	//HLSL縺九ｉ�具ｾ滂ｽｸ�ｾ�呻ｽｼ�ｪ�ｰ��槭��鯉ｾ橸ｾ幢ｾ鯉ｾ槭ｒ菴懈�.
	if( FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,	//�ｼ�ｪ�ｰ��橸ｾ鯉ｽｧ�ｲ�吝錐(HLSL�鯉ｽｧ�ｲ�).
			NULL,
			NULL,
			ENT_PIX_NAME,		//�ｼ�ｪ�ｰ��橸ｽｴ�晢ｾ�ｾ假ｽｰ�趣ｾ滂ｽｲ�晢ｾ�未謨ｰ縺ｮ蜷榊燕.
			"ps_5_0",		//�ｼ�ｪ�ｰ��槭��難ｾ�ｾ橸ｾ吶ｒ謖�ｮ壹☆繧区枚蟄怜�(�鯉ｾ滂ｾ幢ｾ鯉ｽｧ�ｲ�).
			uCompileFlag,	//�ｼ�ｪ�ｰ��橸ｽｺ�晢ｾ奇ｾ滂ｽｲ�呻ｾ鯉ｾ暦ｽｸ�.
			0,
			NULL,
			&pCompiledShader,//�鯉ｾ橸ｾ幢ｾ鯉ｾ槭ｒ譬ｼ邏阪☆繧具ｾ抵ｾ難ｾ倥∈縺ｮ�趣ｾ滂ｽｲ�晢ｾ.
			&pErrors,
			NULL ) ) )
	{
		MessageBox( NULL, "hlsl(ps)隱ｭ縺ｿ霎ｼ縺ｿ螟ｱ謨", "clsRay::InitShader", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pErrors );

	//荳願ｨ倥〒菴懈�縺励◆�鯉ｾ橸ｾ幢ｾ鯉ｾ槭°繧峨鯉ｾ具ｾ滂ｽｸ�ｾ�呻ｽｼ�ｪ�ｰ��槭阪ｒ菴懈�.
	if( FAILED(
		m_pDevice11->CreatePixelShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			NULL,
			&m_pPixelShader ) ) )//(out)�具ｾ滂ｽｸ�ｾ�呻ｽｼ�ｪ�ｰ��.
	{
		MessageBox( NULL, "ps菴懈�螟ｱ謨", "clsRay::InitShader", MB_OK );
		return E_FAIL;
	}
	SAFE_RELEASE( pCompiledShader );//�鯉ｾ橸ｾ幢ｾ鯉ｾ櫁ｧ｣謾ｾ.


	//�ｺ�晢ｽｽ��晢ｾ�ｾ奇ｾ橸ｽｯ�鯉ｽｧ(螳壽焚)�奇ｾ橸ｽｯ�鯉ｽｧ菴懈�縲�ｼ�ｪ�ｰ��槭↓迚ｹ螳壹�謨ｰ蛟､繧帝√ｋ�奇ｾ橸ｽｯ�鯉ｽｧ.
	//縺薙％縺ｧ縺ｯ螟画鋤陦悟�貂｡縺礼畑.
	//�ｼ�ｪ�ｰ��槭↓World,View,Projection陦悟�繧呈ｸ｡縺.
	D3D11_BUFFER_DESC cb;
	cb.BindFlags	= D3D11_BIND_CONSTANT_BUFFER;;			//�ｺ�晢ｽｽ��ｾ奇ｾ橸ｽｯ�鯉ｽｧ繧呈欠螳.
	cb.ByteWidth	= sizeof( SHADER_CONSTANT_BUFFER );//�ｺ�晢ｽｽ��晢ｾ�ｾ奇ｾ橸ｽｯ�鯉ｽｧ縺ｮ�ｻ�ｲ�ｽ�.
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;				//譖ｸ縺崎ｾｼ縺ｿ縺ｧ�ｱ�ｸ�ｾ�ｽ.
	cb.MiscFlags	= 0;					//縺昴�莉悶��鯉ｾ暦ｽｸ�(譛ｪ菴ｿ逕ｨ).
	cb.StructureByteStride	= 0;			//讒矩菴薙��ｻ�ｲ�ｽ�(譛ｪ菴ｿ逕ｨ)
	cb.Usage		= D3D11_USAGE_DYNAMIC;	//菴ｿ逕ｨ譁ｹ豕:逶ｴ謗･譖ｸ縺崎ｾｼ縺ｿ.

	//�ｺ�晢ｽｽ��晢ｾ�ｾ奇ｾ橸ｽｯ�鯉ｽｧ菴懈�.
	if( FAILED(
		m_pDevice11->CreateBuffer(
			&cb,
			NULL,
			&m_pConstantBuffer ) ) )
	{
		MessageBox( NULL, "�ｺ�晢ｽｽ��晢ｾ�ｾ奇ｾ橸ｽｯ�鯉ｽｧ菴懈�螟ｱ謨", "clsRay::InitShader", MB_OK );
		return E_FAIL;
	}


	return S_OK;
}


//============================================================
//	�夲ｽｲ蛻晄悄蛹.
//============================================================
HRESULT clsRay::InitModel()
{
	//�夲ｽｲ縺ｮ�奇ｾ橸ｽｰ��ｽｯ�ｸ�ｽ�奇ｾ橸ｽｯ�鯉ｽｧ菴懈�.
	D3D11_BUFFER_DESC	bd;
	ZeroMemory( &bd, sizeof( bd ) );
	bd.Usage		= D3D11_USAGE_DEFAULT;
	bd.ByteWidth	= sizeof( MODEL_VERTEX ) * 2;//2轤ｹ蛻.
	bd.BindFlags	= D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags	= 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = m_Ray.vPoint;//�夲ｽｲ縺ｮ蠎ｧ讓吶ｒ�ｾ�ｯ�.
	if( FAILED(
		m_pDevice11->CreateBuffer(
			&bd, &InitData, &m_pVertexBuffer ) ) )
	{
		ERR_MSG( "鬆らせ�奇ｾ橸ｽｯ�鯉ｽｧ菴懈�螟ｱ謨", "clsRay::InitLine" );
		return E_FAIL;
	}


	return S_OK;
}



