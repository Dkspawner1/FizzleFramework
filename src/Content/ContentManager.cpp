#include <Content/ContentManager.h>
#include <Content/TypedAsset.h>

#include "Graphics/Font.h"

template<typename T>
std::future<T*> ContentManager::ClaimAssetAsync(const std::string& assetName) {
    return std::async(std::launch::async, [this, assetName]() {
        return ClaimAsset<T>(assetName);
    });
}

template<typename T>
T* ContentManager::ClaimAsset(const std::string& assetName) {
    if (const auto it = m_assets.find(assetName); it == m_assets.end()) {
        std::unique_ptr<T> asset;
        if constexpr (std::is_same_v<T, Font>) {
            asset = std::make_unique<T>(assetName, GetAssetPath(assetName), 24); // Use appropriate font size
        } else {
            asset = std::make_unique<T>(assetName, GetAssetPath(assetName));
        }
        T* rawPtr = asset.get();
        m_assets[assetName] = std::make_pair(std::move(asset), 1);
        return rawPtr;
    } else {
        it->second.second++;
        return dynamic_cast<T*>(it->second.first.get());
    }
}


void ContentManager::ReleaseAsset(const std::string& assetName) {
    if (const auto it = m_assets.find(assetName); it != m_assets.end()) {
        it->second.second--;
        if (it->second.second == 0) {
            m_assets.erase(it);
        }
    }
}

template<typename T>
T* ContentManager::Get(const std::string& assetName) {
    if (const auto it = m_assets.find(assetName); it != m_assets.end()) {
        return dynamic_cast<T*>(it->second.first.get());
    }
    return nullptr;
}

void ContentManager::UnloadAll() {
    m_assets.clear();
}

// Explicit template instantiations
template std::future<Texture*> ContentManager::ClaimAssetAsync<Texture>(const std::string&);
template Texture* ContentManager::ClaimAsset<Texture>(const std::string&);
template Texture* ContentManager::Get<Texture>(const std::string&);
template std::future<Font*> ContentManager::ClaimAssetAsync<Font>(const std::string&);
template Font* ContentManager::ClaimAsset<Font>(const std::string&);
template Font* ContentManager::Get<Font>(const std::string&);