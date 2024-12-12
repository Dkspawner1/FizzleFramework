#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H
#include <memory>
#include <string>
#include <unordered_map>
#include <Content/Asset.h>

class ContentManager {
public:
    ContentManager();

    ~ContentManager();

    template<typename T>
    T *Load(const std::string &assetName);

    void Unload(const std::string &assetName);

    void UnloadAll();

private:
    std::unordered_map<std::string, std::unique_ptr<Asset>> m_assets;
};
#endif //CONTENTMANAGER_H
