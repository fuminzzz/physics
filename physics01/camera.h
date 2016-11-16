#pragma once
/**----------------------------------------------------------------------------//
  @file   : camera.h
  @par    : ����
			2016/09/20 ver 0.00 Created by Fumi Konishi<br>
								�V�K�쐬<br>
//-----------------------------------------------------------------------------*/
#ifndef _CAMERA_H_
#define	_CAMERA_H_

/**----- include file ---------------------------------------------------------*/
#include <d3d10.h>
#include <d3dx10.h>

//---------------------------------------------------------------------------
/**
 *	@class  : Camera
 *	@par    : ����
 *	2016/09/20 ver 0.00 Created by Fumi Konishi<br>
 *						�V�K�쐬<br>
 **/
class Camera
{
private:
	struct CAMERADATA{
		D3DXVECTOR3 vPosition;	// �ʒu
		D3DXVECTOR3 vLookat;	// �����_
		float       fRad;		// ����
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
	 *	������
	 */
	void initialize( ID3D10EffectMatrixVariable* i_pWorldVariable, ID3D10EffectMatrixVariable* i_pProjectionVariable );

	/*
	 *	�j��
	 */
	void terminate();

	/*
	 *	�X�V
	 */
	void update();
};
#endif	_CAMERA_H_