/**----------------------------------------------------------------------------//
  @file   : camera.cpp
  @par    : 履歴
			2016/09/20 ver 0.00 Created by Fumi Konishi<br>
								新規作成<br>
//-----------------------------------------------------------------------------*/
/*---- Include File -----------------------------------------------------------*/
#include "stdafx.h"
#include "camera.h"

/*---- Function Declaration ---------------------------------------------------*/
Camera* Camera::s_pInstance = NULL;

//---- Prototype Declaration --------------------------------------------------
#define LOOKATRANGE 5.0f

//---------------------------------------------------------------------------
/*---------------------------------------------------------------------------
	コンストラクタ
	---------------------------------------------------------------------------*/
Camera::Camera()
	: m_CameraData()
	, m_pWorldVariable()
	, m_ProjectionVariable()
{
	// 初期化
	m_CameraData.fRad			= 0.0f;
	m_CameraData.vPosition.x	= 0.0f;
	m_CameraData.vPosition.y	= 4.0f;
	m_CameraData.vPosition.z	= 0.0f - 10.0f;
	m_CameraData.vLookat.x		= m_CameraData.vPosition.x + ( sin( m_CameraData.fRad ) * LOOKATRANGE );
	m_CameraData.vLookat.y		= 0.0f;
	m_CameraData.vLookat.z		= m_CameraData.vPosition.z + ( cos( m_CameraData.fRad ) * LOOKATRANGE );
}

/*---------------------------------------------------------------------------
	デストラクタ
	---------------------------------------------------------------------------*/
Camera::~Camera()
{
	terminate();
}

/*---------------------------------------------------------------------------
	初期化
	----------------------------------------------------------------------------*/
void Camera::initialize( ID3D10EffectMatrixVariable* i_pWorldVariable, ID3D10EffectMatrixVariable* i_pProjectionVariable )
{
	m_pWorldVariable		= i_pWorldVariable;
	m_ProjectionVariable	= i_pProjectionVariable;
}

/*---------------------------------------------------------------------------
	破棄
	----------------------------------------------------------------------------*/
void Camera::terminate()
{
}

/*---------------------------------------------------------------------------
	更新
	----------------------------------------------------------------------------*/
void Camera::update()
{
	if( m_pWorldVariable && m_ProjectionVariable )
	{
		D3DXMATRIXA16 matWorld, matView, matProj;
		D3DXVECTOR3 vEyePt, vLookatPt, vUpVec;

		// World Matrix.
		D3DXMatrixIdentity( &matWorld );
		m_pWorldVariable->SetMatrix( (float*)&matWorld );

		// Camera.
		vEyePt.x    = m_CameraData.vPosition.x;
		vEyePt.y    = m_CameraData.vPosition.y;
		vEyePt.z    = m_CameraData.vPosition.z;
		vLookatPt.x = m_CameraData.vLookat.x;
		vLookatPt.y = m_CameraData.vLookat.y;
		vLookatPt.z = m_CameraData.vLookat.z;
		vUpVec.x    = 0.0f;
		vUpVec.y    = 1.0f;
		vUpVec.z    = 0.0f;
		D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );

		// Projection Matrix.
		D3DXMatrixPerspectiveFovLH( &matProj, (float)D3DX_PI * 0.25f, 640.f / 480.f, 0.1f, 100.0f );
		m_ProjectionVariable->SetMatrix( (float*)&matProj );
	}
}