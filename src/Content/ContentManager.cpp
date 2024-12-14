#include <Content/ContentManager.h>
#include <Content/TypedAsset.h>

template<typename T>
std::future<T*> ContentManager::ClaimAssetAsync(const std::string& assetName) {
    return std::async(std::launch::async, [this, assetName]() {
        return ClaimAsset<T>(assetName);
    });
}

template<typename T>
T* ContentManager::ClaimAsset(const std::string& assetName) {
    auto it = m_assets.find(assetName);
    if (it == m_assets.end()) {
        auto asset = std::make_unique<T>(assetName, GetAssetPath(assetName));
        T* rawPtr = asset.get();
        m_assets[assetName] = std::make_pair(std::move(asset), 1);
        return rawPtr;
    } else {
        it->second.second++;
        return dynamic_cast<T*>(it->second.first.get());
    }
}

void ContentManager::ReleaseAsset(const std::string& assetName) {
    auto it = m_assets.find(assetName);
    if (it != m_assets.end()) {
        it->second.second--;
        if (it->second.second == 0) {
            m_assets.erase(it);
        }
    }
}

template<typename T>
T* ContentManager::Get(const std::string& assetName) {
    auto it = m_assets.find(assetName);
    if (it != m_assets.end()) {
        return dynamic_cast<T*>(it->second.first.get());
    }
    return nullptr;
}

void ContentManager::UnloadAll() {
    m_assets.clear();
}

// Explicit template instantiations
template std::future<Texture*> ContentManager::ClaimAssetAsync<Texture>(const std::string&);
template std::future<SpriteFont*> ContentManager::ClaimAssetAsync<SpriteFont>(const std::string&);
template Texture* ContentManager::ClaimAsset<Texture>(const std::string&);
template SpriteFont* ContentManager::ClaimAsset<SpriteFont>(const std::string&);
template Texture* ContentManager::Get<Texture>(const std::string&);
template SpriteFont* ContentManager::Get<SpriteFont>(const std::string&);
