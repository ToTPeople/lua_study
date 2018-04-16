//
//  c_destruct_by_lua_test.cpp
//  lua_study
//
//  Created by lifushan on 2018/3/9.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include "c_destruct_by_lua_test.hpp"
#include <unistd.h>

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"


namespace {
    class CA {
    public:
        CA() : _value(0) {}
        CA(int v) : _value(v) {}
        virtual ~CA() {
            printf("************** [~A] value = %d ======\n", _value);
        }
        
    public:
        void ShowValue() {
            printf("\nvalue = %d\n", _value);
        }
        void SetValue(int value) {
            _value = value;
        }
        
    private:
        int _value;
    };
}

void free_test() {
    static int cnt = 0;
    printf("------- [c free_test] time %d free !!!\n", cnt++);
}

int Cal(int a, int b)
{
    return (a + b);
}

typedef int (*pCal)(int, int);

class SA
{
public:
    void SetFunc(void* func)
    {
        pCal pc = (pCal)func;
        if (NULL != pc) {
            printf("---------- run pc = %d -------\n", (*pc)(10, 20));
        }
    }
};

int c_destruct_by_lua_test() {
    sol::state lua;
    lua.open_libraries();
    
    // ----------------------------
    lua.new_usertype<SA>("SA"
                         , "SetFunc", &SA::SetFunc
                         );
    lua["Cal"] = &Cal;
    // ----------------------------
    
    lua.new_usertype<CA>("CA", sol::constructors<CA(), CA(int)>()
//                         , sol::destructor_wrapper<void free_test>()
//                         , sol::destructor_wrapper<<#typename Function#>>
                         , "ShowValue", &CA::ShowValue
                         , "SetValue", &CA::SetValue
                         );
    // 引用 或 复制 传递给lua
//    CA ca;
//    lua["ca"] =
//    ca;
//    &ca;
//    std::ref(ca);
    
    //
//    CA* pa = new CA();
//    lua["ca"] = pa;
////    *pa = NULL;
//    printf("--- c: p[%p], *p[%p] ==\n", pa, (void*)(&(*pa)) );
//    delete pa;
    
    lua.script_file("./try/c_destruct_by_lua/c_destruct_by_lua.lua");
    
    CA* p = lua.get<CA*>("ca");
    if (NULL != p) {
        printf("-------------- ");
        p->ShowValue();
    }
    p = NULL;
    
//    CA a = lua.get<CA>("ca");
//    a.ShowValue();
    
//    SA sa = lua["ss"];
//    sa.SetFunc((void*)Cal);
    

    printf("-=-=-=-=--=-=--=- C end -=-=-=-=-=\n");
    
    return 0;
}
