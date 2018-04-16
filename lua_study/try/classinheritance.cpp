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
#include <iostream>
#include <vector>

#include "cobjecttolua.hpp"
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
    protected:
        int pta;
    private:
        int pva;
    };
    
    class B : public A {
    public:
        B() : A(), b(20) {
            pTT = new TT();
        }
        
        ~B() {
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
                        , "only_parent_has", &A::only_parent_has
                        , "a", &A::a
                        );
    
    lua.new_usertype<B>("B"
                        , "call", &B::call
                        , "only_b_has", &B::only_b_has
                        , "only_parent_has", &A::only_parent_has
                        , sol::base_classes, sol::bases<A>()
                        );
    
    lua.new_usertype<C>("C"
                        , "c", &C::c
                        , "call", &C::call
                        , "deal", &C::deal
                        , sol::base_classes, sol::bases<B, A>()
                        );
    
    // c/c++ class with namespace to lua
    lua.new_usertype<CPP_NP::CObjecWithNamespace>("CObjecWithNamespace", sol::constructors<sol::types<int>>()
                                                  , "show", &CPP_NP::CObjecWithNamespace::Show
                                                  );
    
#define REFREF
#ifdef REFREF
    C* pC = new C();
    pC->c = 500;
    pC->call();
//    lua["pc"] = pC;//std::ref(pC);
    
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    //int rt = script_pushobject(L, (void*)pC);
    //printf("============ rt = %d ----------\n", rt);
    lua["pc"] = pC;
    
    lua.script("pc = nil");
    free(pC);
    pC = NULL;
#else
    C pC;
    pC.c = 500;
    pC.call();
    lua["pc"] = pC;//std::ref(pC);//std::make_shared<C>();
#endif // end REFREF
    
    long long a = 100000010, b = 100000001;
    long long lvalue = a*b;
    std::cout << lvalue << std::endl;
    printf("lvalue = %lld\n", lvalue);
    lua["lll"] = lvalue;
    
//    C cu;
    {
        C cu;
        cu.c = 500;
        lua["cu"] = std::ref(cu);
    }
    
//    lua.script(R"(
//               snapshot = require "snapshot"
//               S1 = snapshot()
//               )");
    
#ifdef C_TO_LUA
    lua.script_file("./try/classuseinlua.lua");
    
    double ff = lua.get<double>("lll");
    lvalue = lua.get<long long>("lll");
    sol::type::function;
    printf("lvalue = %lld, pC[%p] ff[%lf] \n", lvalue, &pC, ff);
    
    printf("----- cu : =====\n");
//    cu.call();
    printf("-------------\n");
    
#ifdef REFREF
//    pC->call();
#else
    pC.call();
#endif // end REFREF
    
//    sol::object bc = lua["b"];
//    sol::object bd = lua.get<sol::object>("b");
//    sol::type::function;
//    printf("------ type bc[%d], bd[%d] ===\n", bc.get_type(), bd.get_type());
    
//    lua.script("b = nil");
    
//    lua.script(R"(
//               print("\n------------------------- lua memory check print ===================")
//               S2 = snapshot()
//
//               for k,v in pairs(S2) do
//                   if S1[k] == nil then
//                        print(k,v)
//                   end
//               end
//               print("\n------------------------- lua memory check print end ===================")
//               )");
    
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
    
    printf("============ test st ==============\n");
    // do some printing
//    lua["print_some_val"]();
    // 100
    
    sol::table oo = lua["some_table"];
//    sol::table hh = lua["some_table"]["new"];
//    printf("---- type hh[%d] ===\n", hh.get_type());
//    oo["new"](40);
//    oo["add_to_some_val"](oo, 10);
//    oo["add_to_some_val"](10);
    sol::table ct = lua["ts"];
    
    lua["some_table"]["add_to_some_val"](oo, 10);
    lua["some_table"]["add_to_some_val"](ct, 10);
//    lua["print_some_val"]();
    
    printf("============ test en ==============\n");
    
#endif
    
    return 0;
}
