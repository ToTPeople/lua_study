//
//  cclassnamespace.hpp
//  lua_study
//
//  Created by lifushan on 2018/3/1.
//  Copyright © 2018年 lifs. All rights reserved.
//

#ifndef cclassnamespace_hpp
#define cclassnamespace_hpp

#include <stdio.h>

namespace CPP_NP {
    class CObjecWithNamespace {
    public:
        CObjecWithNamespace(int num);
        ~CObjecWithNamespace();
        
        void Show();
        
    private:
        int         _num;
    };
}

class CObj {
public:
    CObj(int num);
    ~CObj();
    
    void Show();
    
private:
    int     _num;
};

#endif /* cclassnamespace_hpp */
