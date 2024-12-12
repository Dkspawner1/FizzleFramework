#include <Content/ContentManager.h>
#include <Content/TypedAsset.h>

ContentManager::ContentManager() = default;

ContentManager::~ContentManager() {
    UnloadAll();
}

template<typename T>
T *ContentManager::Load(const std::string &assetName) {
    if (const auto it = m_assets.find(assetName); it != m_assets.end()) {
        return &static_cast<TypedAsset<T>*>(it->second.get())->data;
    }

    auto asset = std::make_unique<TypedAsset<T>>();

    // Load asset data here...

    T* rawPtr = &asset->data;
    m_assets[assetName] = std::move(asset);
    return rawPtr;
}


void ContentManager::Unload(const std::string &assetName) {
    auto it = m_assets.find(assetName);
    if (it != m_assets.end()) {
        m_assets.erase(it);
    }
}
void ContentManager::UnloadAll() {
    m_assets.clear();
}


