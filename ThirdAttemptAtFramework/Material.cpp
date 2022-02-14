#include "Material.h"
#include "WICTextureLoader.h"
#include "Utils.h"

using namespace DirectX;

INT Material::init(IDirect3DDevice9* pD3DDevice, LPCTSTR textureName)
{
    HRESULT hr = CreateWICTextureFromFile(pD3DDevice, textureName, &_pTexture, 0, WIC_LOADER_MIP_AUTOGEN);
    CheckFailed(hr, 60);

    _material.Ambient = {1.0f, 1.0f, 1.0f, 1.0f};
    _material.Diffuse = {1.0f, 1.0f, 1.0f, 1.0f};
    _material.Specular = { 1.0f, 1.0f, 1.0f, 1.0f };
    _material.Power = 1024.0f; // sharpness of specular light (the higher the vlaue the shrper the highlights)
    _material.Emissive = { 0.0f, 0.0f, 0.0f, 0.0f }; // self ilumination, does not need light


    return 0;
}

void Material::render(IDirect3DDevice9* pD3DDevice)
{
    // set texture
    pD3DDevice->SetTexture(0, _pTexture);

    // set up sampler state
    pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP); // Default setting is Wrap
    pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP); // Default setting is Wrap
    pD3DDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_XRGB(255, 0, 255)); // creates magenta border (default is 0xff000000)
    pD3DDevice->SetSamplerState(0, D3DSAMP_MAXMIPLEVEL, 0); // default 0
    pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR); // default: NONE
    pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); // default is POINT 
    pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); // default is POINT 
    pD3DDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 16); // used for anisotropic filtering only

    // set material
    pD3DDevice->SetMaterial(&_material);
}

void Material::deInit()
{
    safeRelease<IDirect3DTexture9>(_pTexture);
}
