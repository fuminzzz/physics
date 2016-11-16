#pragma once
/**----------------------------------------------------------------------------//
  @file   : camera.h
  @par    : 履歴
			2016/09/20 ver 0.00 Created by Fumi Konishi<br>
								新規作成<br>
//-----------------------------------------------------------------------------*/
#ifndef _CAMERA_H_
#define	_CAMERA_H_

/**----- include file ---------------------------------------------------------*/
#include <d3d10.h>
#include <d3dx10.h>

//---------------------------------------------------------------------------
/**
 *	@class  : Camera
 *	@par    : 履歴
 *	2016/09/20 ver 0.00 Created by Fumi Konishi<br>
 *						新規作成<br>
 **/
class Camera
{
private:
	struct CAMERADATA{
		D3DXVECTOR3 vPosition;	// 位置
		D3DXVECTOR3 vLookat;	// 注視点
		float       fRad;		// 向き
		CAMERADATA()
			: vPosition( 0.f, 0.f, 0.f )
			, vLookat( 0.f, 0.f, 0.f )
			, fRad( 0.f )
		{
		}
	};

public:
	static Camera*				s_pInstance;

private:
	CAMERADATA					m_CameraData;
	ID3D10EffectMatrixVariable*	m_pWorldVariable;
	ID3D10EffectMatrixVariable*	m_ProjectionVariable;

public:
	Camera();
	~Camera();

private:
	Camera( const Camera& i_rRef );
	Camera& operator =( const Camera& i_rRef );

public:
	static void createInstance()
	{
		if( !s_pInstance )
			s_pInstance = new Camera();
	}

	static void disposeInstance()
	{
		delete s_pInstance;
	}

	static Camera* getInstance()
	{
		if( s_pInstance )
			return s_pInstance;
		return nullptr;
	}

public:
	/*
	 *	初期化
	 */
	void initialize( ID3D10EffectMatrixVariable* i_pWorldVariable, ID3D10EffectMatrixVariable* i_pProjectionVariable );

	/*
	 *	破棄
	 */
	void terminate();

	/*
	 *	更新
	 */
	void update();
};
#endif	_CAMERA_H_