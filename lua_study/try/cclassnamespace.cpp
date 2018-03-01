//
//  cclassnamespace.cpp
//  lua_study
//
//  Created by lifushan on 2018/3/1.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include "cclassnamespace.hpp"

CPP_NP::CObjecWithNamespace::CObjecWithNamespace(int num)
: _num(num)
{
    //
}

CPP_NP::CObjecWithNamespace::~CObjecWithNamespace()
{
    
}

void CPP_NP::CObjecWithNamespace::Show()
{
    printf("=== this[%p], num[%d] ===\n", this, _num);
}

CObj::CObj(int num)
: _num(num)
{
    //
}

CObj::~CObj()
{
    //
}

void CObj::Show()
{
    printf("=== this[%p], num[%d] ===\n", this, _num);
}
