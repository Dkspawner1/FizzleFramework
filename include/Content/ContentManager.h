#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H
#include <future>
#include <memory>
#include <string>
#include <unordered_map>
#include <Content/Asset.h>
#include <Content/Texture.h>

class ContentManager {
public:
    ContentManager() = default;
    ~ContentManager() { UnloadAll(); }

    template<typename T>
    std::future<T*> ClaimAssetAsync(const std::string& assetName);

    template<typename T>
    T* ClaimAsset(const std::string& assetName);

    void ReleaseAsset(const std::string& assetName);

    template<typename T>
    T* Get(const std::string& assetName);

    void UnloadAll();

    static std::string GetAssetPath(const std::string& assetName) {
        return "../assets/" + assetName;
    }

private:
    std::unordered_map<std::string, std::pair<std::unique_ptr<Asset>, int>> m_assets;
};

#endif //CONTENTMANAGER_H
