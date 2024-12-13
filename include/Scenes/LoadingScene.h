#ifndef LOADINGSCENE_H
#define LOADINGSCENE_H
#include <iostream>
#include <ostream>

class LoadingScene {
public:
    void Show() {
        std::cout<<"Loading assets, please wait..."<<std::endl;
    }
    void Update()
    {}
};

#endif //LOADINGSCENE_H
