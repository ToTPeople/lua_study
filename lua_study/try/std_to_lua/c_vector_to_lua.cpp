//
//  c_vector_to_lua.cpp
//  lua_study
//
//  Created by lifushan on 2018/3/6.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include "c_vector_to_lua.hpp"
#include <vector>
#include <iostream>

#include "cclassnamespace.hpp"
#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"


namespace {
    class A {
    public:
        A() : _value(0) {}
        A(int v) : _value(v) {}
        
        void ShowValue() {
            int ccc = 1010;
            printf("\nvalue = %d, ccc = %d\n", _value, ccc);
        }
        
    private:
        int _value;
    };
    
    class CInOther {
    public:
        CInOther() : pA(NULL) {}
        
    public:
        A*      pA;
    } vvc;
    
    //
    class CTestVec {
        
    public:
        static A* GetAIns() { A* pA = new A(); return pA; }
        static A* GetAIns(int v) { A* pA = new A(v); return pA; }
        
    public:
        CTestVec() : a(0) {}
        
        void SetValue(int value) { a = value; }
        void SetValue() { a = 123; }
        void ShowValue() { printf("value=%d", a); }
        void AddA(A* p) {
            vvc.pA = p;
        }
        
    private:
        int a;
    };
    
#define CUSTOME_VECTOR_TYPE
}

int c_vector_to_lua() {
    std::cout << "=== containers example ===" << std::endl;
    
    sol::state lua;
    lua.open_libraries();
    
#ifdef CUSTOME_VECTOR_TYPE
    
    std::vector<CTestVec> vecTest;
    for (int i = 0; i < 5; ++i) {
        CTestVec vecT;
        vecT.SetValue(i*10);
        vecTest.push_back(vecT);
    }
    // Set a global variable called
    // "vecTest" to be a vector of 5 lements
    lua["vecTest"] = std::ref(vecTest);//&vecTest;
//    lua.set("vecTest", &vecTest);
    
    lua.new_usertype<A>("A", sol::constructors<A(), A(int)>(),
                        "ShowValue", &A::ShowValue);
    
    lua.new_usertype<CTestVec>("CTestVec", sol::constructors<CTestVec()>(),
                               "SetValue", sol::overload(sol::resolve<void(int)>(&CTestVec::SetValue),
                                                         sol::resolve<void()>(&CTestVec::SetValue) ),
                               "GetAIns", sol::overload(sol::resolve<A* ()> (&CTestVec::GetAIns),
                                                        sol::resolve<A* (int)> (&CTestVec::GetAIns) ),
                               "ShowValue", &CTestVec::ShowValue,
                               "AddA", &CTestVec::AddA
                               );
    
    lua.script_file("./try/std_to_lua/luastduse.lua");
    
//    pI.ShowValue();
    printf("--- pI ----- ===\n");
    
    int nSize = vecTest.size();
    printf("---- size = %d =====\n", nSize);
    for (int i = 0; i < nSize; ++i) {
        vecTest[i].ShowValue();
    }
    sol::object ob = lua["vecT"];
    sol::type::function;
    printf("--- ob type %d ===\n", ob.get_type());
    
    printf("######## 1 st #########\n");
    if (vvc.pA != NULL) {
        vvc.pA->ShowValue();
    }
    printf("######## 1 en #########\n");
    
#else
    
    // Set a global variable called
    // "arr" to be a vector of 5 lements
    lua["arr"] = std::vector<int>{ 2, 4, 6, 8, 10 };
    
    // Mess with it in C++
    // Containers are stored as userdata, unless you
    // use `sol::as_table()` and `sol::as_table_t`.
    std::vector<int>& reference_to_arr = lua["arr"];
    reference_to_arr.push_back(12);

    printf("------ 1 st -----\n");
    for (int i = 0; i < reference_to_arr.size(); ++i) {
        printf("i = %d\tvalue = %d\n", i, reference_to_arr[i]);
    }
    printf("------ 1 en -----\n");
    
    lua.script_file("./try/std_to_lua/luastduse.lua");
    
    printf("------ 2 st -----\n");
    for (int i = 0; i < reference_to_arr.size(); ++i) {
        printf("i = %d\tvalue = %d\n", i, reference_to_arr[i]);
    }
    printf("------ 2 en -----\n");
    
    std::cout << std::endl;
    
#endif
    
    return 0;
}
