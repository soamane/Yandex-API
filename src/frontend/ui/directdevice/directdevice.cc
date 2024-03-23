#include "directdevice.hpp"

bool DirectDevice::CreateDevice(HWND hwnd) {
    DXGI_SWAP_CHAIN_DESC desc = {};
    desc.BufferCount = 2;
    desc.BufferDesc.Width = 0;
    desc.BufferDesc.Height = 0;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.OutputWindow = hwnd;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Windowed = TRUE;
    desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT deviceFlags = 0;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
    HRESULT hResult = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, deviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &desc, &pSwapChain, &pDevice, &featureLevel, &pContext);
    if (hResult == DXGI_ERROR_UNSUPPORTED) {
        hResult = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, deviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &desc, &pSwapChain, &pDevice, &featureLevel, &pContext);
    }

    if (FAILED(hResult)) {
        return false;
    }

    CreateRenderTarget();
    return true;
}

void DirectDevice::CleanupDevice() {
    CleanupRenderTarget();
    if (pSwapChain) {
        pSwapChain->Release();
        pSwapChain = nullptr;
    }

    if (pContext) {
        pContext->Release();
        pContext = nullptr;
    }

    if (pDevice) {
        pDevice->Release();
        pDevice = nullptr;
    }
}

void DirectDevice::CreateRenderTarget() {
    ID3D11Texture2D* pBuffer;
    pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBuffer));
    pDevice->CreateRenderTargetView(pBuffer, nullptr, &pTargetView);
    pBuffer->Release();
}

void DirectDevice::CleanupRenderTarget() {
    if (pTargetView) {
        pTargetView->Release();
        pTargetView = nullptr;
    }
}