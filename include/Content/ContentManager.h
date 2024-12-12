#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H
#include <memory>
#include <string>
#include <unordered_map>
#include <Content/Asset.h>

#include "Texture.h"

class ContentManager {
public:
    ContentManager();

    ~ContentManager();

    template<typename T>
    T *Load(const std::string &assetName);

    Texture* LoadTexture(const std::string &assetName);

    void Unload(const std::string &assetName);

    void UnloadAll();

    static std::string GetAssetPath(const std::string &assetName) {
        return std::move("../assets/" + assetName);
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Texture> > m_assets;
};
#endif //CONTENTMANAGER_H
