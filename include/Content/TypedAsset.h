#ifndef TYPEDASSET_H
#define TYPEDASSET_H
#include "Asset.h"

template<typename T>
class TypedAsset final : public Asset {
public:
    T data;
};

#endif //TYPEDASSET_H
