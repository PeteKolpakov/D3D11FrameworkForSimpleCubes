#include "Camera.h"
#include <DirectXMath.h>

using namespace DirectX;


INT Camera::init(UINT screenwidth, UINT screenheight)
{
    // view matrix
    XMMATRIX viewMatrix = XMMatrixLookToLH(
        XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f), // cam position
        XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f),  // cam forward vector
        XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)   // cam up vector
    );
    XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&_viewMatrix), viewMatrix);

    // projection matrix
    XMMATRIX projectionMatrix = XMMatrixPerspectiveFovLH(
        XM_PI * 0.33333333f, // field of view in radians
        static_cast<FLOAT>(screenwidth) / static_cast<FLOAT>(screenheight), // aspect ratio
        0.3f, 1000.0f // near and far clipping planes
    );
    XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&_projectionMatrix), projectionMatrix);

    return 0;
}

void Camera::render(IDirect3DDevice9* pD3DDevice)
{
    pD3DDevice->SetTransform(D3DTS_VIEW, &_viewMatrix);
    pD3DDevice->SetTransform(D3DTS_PROJECTION, &_projectionMatrix);
}

void Camera::deInit()
{
}
