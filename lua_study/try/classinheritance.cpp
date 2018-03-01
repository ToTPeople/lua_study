//
//  classinheritance.cpp
//  lua_study
//
//  Created by lifushan on 2018/3/1.
//  Copyright © 2018年 lifs. All rights reserved.
//
/*
 * 1､C/C++ class(include multi-inherite) to lua, 设置'sol::base_classes, sol::bases<B>()'时，lua子类有调用到哪层父类方法，需要把继承关系设置进来
 *
 *
 */


#include "classinheritance.hpp"
#include <stdio.h>

#include "cclassnamespace.hpp"
#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"

namespace {
//#define C_TO_LUA
    
    class TT {
    public:
        TT() : tt(11) {}
        
    private:
        int tt;
    };
    
    class A {
    public:
        A() : a(10) {}
        
        void only_parent_has() {
            printf("[A::only_parent_has] just a test.\n");
        }
        
        virtual int call() {
            printf("[A::call] a[%d]\n", a);
            return a;
        }
        
    public:
        int a;
    };
    
    class B : public A {
    public:
        B() : A(), b(20) {
            pTT = new TT();
        }
        
        ~B() {
            if (NULL != pTT) {
                delete pTT;
            }
        }
        
        void only_b_has() {
            printf("[B::only_b_has] only B has....\n");
        }
        
        virtual int call() {
            A::call();
            printf("[B::call] b[%d]\n", b);
            return b;
        }
        
    public:
        int b;
        TT* pTT;
    };
    
    class ZZ {
    public:
        ZZ() : zz(100) {}
        virtual void deal() {
            printf("[ZZ::deal] zz[%d] \n", zz);
        }
        
    private:
        int zz;
    };
    
    class C : public B, public ZZ {
    public:
        C() : B(), c(30) {}
        
        virtual int call() {
            printf("[C::call] c[%d]\n", c);
            return c;
        }
        
        
        
    public:
        int c;
    };
}

int class_inheritance() {
    sol::state lua;
    lua.open_libraries();
    
    // c/c++ class to lua
    lua.new_usertype<A>("A"
                        , "call", &A::call
                        , "only_parent_has", &A::only_parent_has);
    
    lua.new_usertype<B>("B"
                        , "call", &B::call
                        , "only_b_has", &B::only_b_has
                        , "only_parent_has", &A::only_parent_has
                        , sol::base_classes, sol::bases<A>()
                        );
    
    lua.new_usertype<C>("C"
                        , "call", &C::call
                        , "deal", &C::deal
                        , sol::base_classes, sol::bases<B, A>()
                        );
    
    // c/c++ class with namespace to lua
    lua.new_usertype<CPP_NP::CObjecWithNamespace>("CObjecWithNamespace", sol::constructors<sol::types<int>>()
                                                  , "show", &CPP_NP::CObjecWithNamespace::Show
                                                  );
    
#ifdef C_TO_LUA
    lua.script_file("./try/classuseinlua.lua");
#else
    lua.script_file("./try/luaclassinheritance.lua");
    
    sol::object car = lua["cc"];
    sol::object suv = lua["dd"];
    sol::type t2 = car.get_type();
    sol::type::function;
    printf("------ car type[%d] ===\n", t2);
//    c_assert(t2 == sol::type::function);
//    car["getBrand"]();
//    car["getInfo"](car);
    
    sol::object tmp_car = lua["Car"];
//    int a_price = lua["Car"]["_price"];
//    int price = tmp_car["getPrice"](car);
//    printf("------ getInfo type[%d] ===\n", t2);
    
    lua["cc"]["getInfo"](car);
    lua["dd"]["getInfo"](car);
    
    lua["cc"]["getInfo"](suv);
    lua["dd"]["getInfo"](suv);
    
    // a small script using 'self' syntax
//    lua.script(R"(
//               some_table = { some_val = 100 }
//               
//               function some_table:add_to_some_val(value)
//               self.some_val = self.some_val + value
//               end
//               
//               function print_some_val()
//               print("some_table.some_val = " .. some_table.some_val)
//               end
//               )");
    
    // do some printing
    lua["print_some_val"]();
    // 100
    
    sol::table oo = lua["some_table"];
    oo["add_to_some_val"](oo, 10);
    
#endif
    
    return 0;
}
