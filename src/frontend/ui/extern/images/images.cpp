#include "images.hpp"

#include <filesystem>

void Images::InitSourceIcons() {
    std::string folderPath = "C:\\Users\\admin\\Desktop\\Yandex-API\\Assets\\icons\\";
    AddImageFromFile(folderPath + "logo.png", "logo");
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        std::filesystem::path filePath = entry.path();
        std::filesystem::path fileName = filePath.filename();
        std::filesystem::path fullFilePath = filePath; 
        AddImageFromFile(fullFilePath.string(), fileName.stem().string());
    }
}

void Images::AddImageFromFile(const std::string& path, const std::string& name) {
    D3DX11_IMAGE_LOAD_INFO loadInfo;
    ID3DX11ThreadPump* threadPump{ nullptr };

    ID3D11ShaderResourceView* image = nullptr;
    D3DX11CreateShaderResourceViewFromFileA(DirectDevice::pDevice, path.c_str(), &loadInfo, threadPump, &image, 0);
    if (image != nullptr) {
        this->images[name] = image;
    }
}

void Images::AddImageFromMemory(std::vector<unsigned char>& data, const std::string& name) {
    D3DX11_IMAGE_LOAD_INFO loadInfo;
    ID3DX11ThreadPump* threadPump{ nullptr };

    ID3D11ShaderResourceView* image = nullptr;
    D3DX11CreateShaderResourceViewFromMemory(DirectDevice::pDevice, data.data(), data.size(), &loadInfo, threadPump, &image, 0);
    if (image != nullptr) {
        this->images[name] = image;
    }
}

ID3D11ShaderResourceView* Images::GetImage(const std::string& image) {
    auto it = this->images.find(image);
    if (it != this->images.end()) {
        return it->second;
    }
    return nullptr;
}
