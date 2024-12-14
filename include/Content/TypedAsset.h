#ifndef TYPEDASSET_H
#define TYPEDASSET_H
#include <Content/Asset.h>

template<typename T>
class TypedAsset final : public Asset {
public:
    explicit TypedAsset(const std::string &name, T &&data) : Asset(name), data(std::move(data)) {
    }

    T data;
};

#endif //TYPEDASSET_H
