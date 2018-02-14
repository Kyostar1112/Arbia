#include "Sp2DMgrOver.h"

clsSp2dMgrOver::clsSp2dMgrOver()
{
}

clsSp2dMgrOver::~clsSp2dMgrOver()
{
}

void clsSp2dMgrOver::Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_smpPushTxt = make_unique<clsPushTxt>();
	m_smpOverTxt = make_unique<clsSp2dMgrOverTxt>();

<<<<<<< HEAD
	m_smpPushTxt->Create(pDevice11, pContext11);
=======
	m_smpPushTxt->Init(pDevice11, pContext11);
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	m_smpOverTxt->Init(pDevice11, pContext11);

}

void clsSp2dMgrOver::InitSetPos()
{
<<<<<<< HEAD
	m_smpPushTxt->Init();
=======
	m_smpPushTxt->InitSetPos();
>>>>>>> parent of c2bb3ef... Merge branch 'Deverop' into Tahara
	m_smpOverTxt->InitSetPos();
}

void clsSp2dMgrOver::Render()
{
	m_smpPushTxt->Render();
	m_smpOverTxt->Render();
}

void clsSp2dMgrOver::Release()
{
	m_smpPushTxt->Release();
	m_smpPushTxt.reset();
	m_smpPushTxt = NULL;

	m_smpOverTxt->Release();
	m_smpOverTxt.reset();
	m_smpOverTxt = NULL;
}