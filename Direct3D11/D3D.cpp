#include "D3D.h"
#include "Utils.h"
#include <xutility>

INT D3D::init(HWND hWnd, UINT width, UINT height, BOOL isFullScreen)
{
    HRESULT hr;

    // 1 - set up creation process
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.Windowed = !isFullScreen;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // default for state of the art pipelines
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.SampleDesc.Count = 1; // this MSAA count have to be at least 1



    // 2 - create direct3D 11 device, device context, and swap chain 
    D3D_FEATURE_LEVEL supportedFeatureLevels[] = {
        D3D_FEATURE_LEVEL_12_1,
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0
    };

    D3D_FEATURE_LEVEL chosenFeatureLevel = {};
    
    hr = D3D11CreateDeviceAndSwapChain(
        nullptr, // primary graphic card
        D3D_DRIVER_TYPE_HARDWARE, nullptr,
        0, // flags
        supportedFeatureLevels, std::size(supportedFeatureLevels), // which D3D versions are supported by the application
        D3D11_SDK_VERSION,
        &swapChainDesc, &_pDXGISwapChain, &_pD3DDevice, &chosenFeatureLevel, &_pD3DDeviceContext
    );
    CheckFailed(hr, 20);

    // 3 - create render target view
    ID3D11Texture2D* pBackBufferTexture = nullptr;
    //hr = _pDXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBufferTexture));
    hr = _pDXGISwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBufferTexture));
    CheckFailed(hr, 22);

    hr = _pD3DDevice->CreateRenderTargetView(pBackBufferTexture, nullptr, &_pRenderTargetView);
    CheckFailed(hr, 24);

    _pD3DDeviceContext->OMSetRenderTargets(1, &_pRenderTargetView, nullptr);

    safeRelease<ID3D11Texture2D>(pBackBufferTexture);
    return 0;
}

void D3D::beginScene(FLOAT red, FLOAT green, FLOAT blue)
{
    // clear back buffer
    FLOAT backgroundColor[] = { red, green, blue, 1.0f };
    _pD3DDeviceContext->ClearRenderTargetView(_pRenderTargetView, backgroundColor);

    //// clear back buffer with a solid color
    //_pD3DDevice->Clear(
    //    0, nullptr, // areas/regions to clear / 0 = clear all
    //    D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // what buffer to clear, target = back buffer
    //    backgroundColor, 1.0f, 0xffffffff // clear values, back buffer, depth buffer, stencil buffer
    //);
}

void D3D::endScene()
{
    // swap front buffer with back buffer
    _pDXGISwapChain->Present(0, 0);
}

void D3D::deInit()
{
    safeRelease<ID3D11RenderTargetView>(_pRenderTargetView);
    safeRelease<ID3D11Device>(_pD3DDevice);
    safeRelease<ID3D11DeviceContext>(_pD3DDeviceContext);
    safeRelease<IDXGISwapChain>(_pDXGISwapChain);
}
