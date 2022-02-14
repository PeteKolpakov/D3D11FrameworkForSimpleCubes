#include "D3D.h"
#include "Utils.h"

INT D3D::init(HWND hWnd, UINT width, UINT height, BOOL isFullsScreen)
{
    // 1 - get Direct3D 9 interface (connection to the API)   
    IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

    CheckNull(pD3D, 20);


    // 2 - check fixed-function pipeline support
    D3DCAPS9 d3dCaps = {};
    UINT adapter = D3DADAPTER_DEFAULT; // graphic card adapter index
    D3DDEVTYPE devType = D3DDEVTYPE_HAL; // device type for rendering (HAL = hardware abstraction layer (Graphics card))
    HRESULT hr = pD3D->GetDeviceCaps(adapter, devType, &d3dCaps);
    CheckFailed(hr, 22);

    DWORD vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;       // fallback
    if (d3dCaps.VertexProcessingCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)  // fixedfunction pipeline support check
    {
        vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
    }

    // 3 - set up presentation parameters

    D3DPRESENT_PARAMETERS d3dpp = {};
    d3dpp.hDeviceWindow = hWnd;                 // target window
    d3dpp.Windowed = !isFullsScreen;            // set windowed mode or exclusive fullscreen
    d3dpp.BackBufferCount = 1;
    d3dpp.BackBufferWidth = width;
    d3dpp.BackBufferHeight = height;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;   // alpha, red, green, blue channels - each channel with 8 bits (32 bits total)
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;   // what happens to the front buffer after swapping (discard will delete it and clear the memory)
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; // (de-)activate vsync, default is activated 
    d3dpp.EnableAutoDepthStencil = TRUE; // enables depth buffer
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;


    // 4 - create direct3D device (connection to pipeline) 
    hr = pD3D->CreateDevice(
        adapter,
        devType,
        hWnd,
        vertexProcessing,   // optional parameters
        &d3dpp,
        &_pD3DDevice
    );
    CheckFailed(hr, 24);

    // 5 - tidy up memory
    safeRelease<IDirect3D9>(pD3D);

    return 0;
}

void D3D::beginScene(D3DCOLOR backgroundColor)
{
    // clear back buffer with a solid color
    _pD3DDevice->Clear(
        0, nullptr, // areas/regions to clear / 0 = clear all
        D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // what buffer to clear, target = back buffer
        backgroundColor, 1.0f, 0xffffffff // clear values, back buffer, depth buffer, stencil buffer
    );

    _pD3DDevice->BeginScene();
}

void D3D::endScene()
{
    _pD3DDevice->EndScene();

    // swap front buffer with back buffer
    _pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void D3D::deInit()
{
    safeRelease<IDirect3DDevice9>(_pD3DDevice);
}
