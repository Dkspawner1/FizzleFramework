#ifndef ASSET_H
#define ASSET_H
#include <string>

class Asset {
public:
    explicit Asset(const std::string& name) : m_name(std::move(name)) {}
    virtual ~Asset() = default;

    const std::string& getName() const {return m_name;}
private:
    std::string m_name;
};

#endif //ASSET_H
