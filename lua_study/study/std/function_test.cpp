//
//  function_test.cpp
//  lua_study
//
//  Created by lifushan on 2018/3/27.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include <stdio.h>
#include <iostream>
//#include <functional>
#include "common_std_header.h"

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"


typedef std::function<void ()> fp;
typedef float (*AHEasingFunction)(float);


void g_fun()
{
    std::cout<< "g_fun()" <<std::endl;
}

// 测试lua端通过std::function调用函数参数
float bezierfunction(float p)
{
    printf("-------- [bezierfunction] p[%f] ------\n", p);
    return 3.14;
}

// 测试lua端传递bool类型
bool test_bool(float p, bool bb)
{
    printf("-------- [test_bool] p[%f], bb[%d] ------\n", p, bb);
    return true;
}

class A
{
public:
    static void A_fun_static()
    {
        std::cout<< "A_fun_static()" <<std::endl;
    }
    
    void A_fun()
    {
        std::cout<< "A_fun()" <<std::endl;
    }
    void A_fun_int(int i)
    {
        std::cout<< "A_fun_int() " << i <<std::endl;
    }
    
    //非静态类成员，因为含有this指针，所以需要使用bind
    void init()
    {
        fp fp1 = std::bind(&A::A_fun, this);
        fp1();
    }
    
    void init2()
    {
        typedef std::function<void (int)> fpi;
        //对于参数要使用占位符 std::placeholders::_1
        fpi f = std::bind(&A::A_fun_int, this, std::placeholders::_1);
        f(5);
    }
};

//////////////////////////////////////////////////////////////////////////////
// C++端调用可正确转换
// 通过sol传递到lua，lua端调用出错!!!!!!!!!!
//
// 具体函数指针类型 从std::function获取函数地址
//template<typename T>
//size_t getAddress(std::function<float (T)> f) {
//    typedef float (fnType)(T);
//    fnType ** fnPointer = f.template target<fnType*>();
//    return (size_t) *fnPointer;
//}

// 模板 函数指针类型 从std::function获取函数地址
template<typename T, typename... U>
size_t getAddress(std::function<T(U...)> f) {
    typedef T(fnType)(U...);
    fnType ** fnPointer = f.template target<fnType*>();
    return (size_t) *fnPointer;
}
//////////////////////////////////////////////////////////////////////////////

class VA
{
public:
    virtual void f()
    {
        std::cout << "VA::f()" << std::endl;
    }
    
    void init()
    {
        //std::bind可以表现出多态行为
        fp f = std::bind(&VA::f,this);
        f();
    }
    
    void set_func(std::function<float(float)> pf)
    {
//        if (NULL == pf) {
//            printf("----------------- pf is null ---------\n");
//            return;
//        }
//        printf("------- pf[%p][%d] -----\n", pf, pf);
//        func = (AHEasingFunction)getAddress(pf);//pf.target<float(float)>();
        func = pf;//*pf.target<AHEasingFunction>();
        if (NULL != func)
            printf("------------- func run result [%f] ------\n", func(10.2));//(*func)(10.3));
        else {
            printf("--------- func is null ---------\n");
        }
    }
    
protected:
//    AHEasingFunction    func;
    std::function<float(float)> func;
};
class VB:public VA
{
public:
    virtual void f()
    {
        std::cout << "VB::f()" << std::endl;
    }
};

class CVA
{
public:
    virtual void f()
    {
        std::cout << "CVA::f()" << std::endl;
    }
    
    void set_func(AHEasingFunction fc)
    {
        func = fc;
    }
    
    void lua_wrap_set_func(std::function<float(float)> pf)
    {
//        if (NULL == pf) {
//            printf("----------------- pf is null ---------\n");
//            return;
//        }
//        printf("------- pf[%p][%d] -----\n", pf, pf);
//        func = (AHEasingFunction)getAddress(pf);//pf.target<float(float)>();
//        func = *pf.target<AHEasingFunction>();
        func = (AHEasingFunction)getAddress(pf);
        if (NULL != func)
            printf("------------- func run result [%f] ------\n", func(10.2));//(*func)(10.3));
        else {
            printf("--------- func is null ---------\n");
        }
    }
    
protected:
    AHEasingFunction    func;
//    std::function<float(float)> func;
};

int function_test()
{
    //绑定到全局函数
    fp f2 = fp(&g_fun);
    f2();
    
    //绑定到类静态成员函数
    fp f1 = fp(&A::A_fun_static);
    f1();
    
    A().init();
    A().init2();
    
    //////////
    std::function<float(float)> ff = std::function<float(float)>(&bezierfunction);
    ff(10);
    
    sol::state lua;
    lua.open_libraries();
    
    lua["bezierfunction"] = &bezierfunction;
    
    lua.new_usertype<VA>("VA"
                         , "f", &VA::f
                         );
    
    lua.new_usertype<VB>("VB"
                         , "f", &VB::f
                         , "set_func", &VB::set_func
                         , sol::base_classes, sol::bases<VA>()
                         );
    
    lua.new_usertype<CVA>("CVA"
                          , "lua_wrap_set_func", &CVA::lua_wrap_set_func
                          );
    
    VA* pa = new VB();
    pa->init();
    lua["aaa"] = pa;
    lua["bbb"] = 10;
    lua["test_bool"] = &test_bool;
    
    lua.script_file("./study/std/test.lua");
    
    return 0;
}

