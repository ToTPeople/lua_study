//
//  lua_collect_garbage.cpp
//  lua_study
//
//  Created by lifushan on 2018/3/27.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include <stdio.h>
#include <vector>

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"

namespace {
    class A;
//    A* g_pA = NULL;
    std::vector<A*> vec;
    
    void BindA(A* pA)
    {
//        g_pA = pA;
        vec.push_back(pA);
//        printf("----------- [BindA] g_pA[%p], pA[%p] -------\n", g_pA, pA);
        printf("----------- [BindA] g_pA[%p], pA[%p] -------\n", vec[0], pA);
    }

    class A
    {
    public:
        A() : _v(10) {}
        ~A() { printf("-------- ~A --------\n"); }
        
        void show_value() {
            printf("------------ [A::show_value] value[%d] --------\n", _v);
        }
        
    public:
        int _v;
    };
}


int lua_collect_garbage()
{
    
{
    sol::state lua;
    lua.open_libraries();
    
//    if (NULL == g_pA) {
//        printf("---------- g_pA == NULL ----------\n");
//    }
    
    lua["BindA"] = &BindA;
    lua.new_usertype<A>("A"
                        , "v", &A::_v
                        , "show_value", &A::show_value
                        );
    
    lua.script_file("./study/lua_collect_garbage.lua");
    lua.collect_garbage();
    
    for (int i=0; i<999999999; ++i) {
        int jj = 0;
    }
    
}
    
    if (NULL != vec[0]) {
        vec[0]->show_value();
        printf("---------- vec[%p] ----------\n", vec[0]);
    }
    
    return 0;
}
