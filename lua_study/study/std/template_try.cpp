//
//  template_try.cpp
//  lua_study
//  测试：
//      -- 不定参模板解析
//      -- sol通过不定参模板传递类型、变量到lua
//  Created by lifushan on 2018/4/16.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include <stdio.h>
#include <string>

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"

class CTestClass {
    
public:
    CTestClass() : _v(10) {
        printf("  construct packet ====\n");
    }
    ~CTestClass() {
        printf("~Packet() ====\n");
    }
    
    void ShowValue() {
        printf("--------- [Packet] value = %d -------\n", _v);
    }
    
    void SetValue(int v) {
        _v = v;
    }
    
public:
    int _v;
private:
    double  _f;
};

// sol包装类
class CSolClass
{
public:
    CSolClass() { lua.open_libraries(); }
    ~CSolClass() {}
    
    // 不定参模板 传递 C++类型到lua
    template <typename Class, typename... Args>
    bool new_usertype(const std::string& name, Args&&... args) {
        printf("##################### name[%s], num[%lu] ---------\n", name.c_str(), sizeof...(args));
        lua.new_usertype<Class>(name, args ...);
        return true;
    }
    
    // 模板 传递 C++变量到lua
    template <typename F>
    void set(std::string&& n, F&& f) {
        lua.set(n, f);
    }
    
    // 执行lua文件
    void do_script_file(const char* file) {
        lua.script_file(file);
    }
    
    // 获取lua函数
    sol::function get_lua_func(const char* key) {
        if (NULL == key) {
            printf("[] error: key is null!!!\n");
            return lua.get<sol::function>("");
        }
        
        return lua.get<sol::function>(key);
    }
    
    // 不定参模板 根据key执行lua函数
    template <typename... Args>
    bool do_lua_func(const char* key, Args&&... args) {
        sol::optional<sol::function> func = get_lua_func(key);
        if (sol::nullopt == func) {
            return false;
        }
        sol::function ff = func.value();
        
        ff(std::forward<Args>(args)...);
        
        return true;
    }
    
private:
    sol::state  lua;
};

// 不定参模板
// 处理每个类型的实际函数
void handleValue(int value) { std::cout << "Integer: " << value << std::endl; }
void handleValue(double value) { std::cout << "Double: " << value << std::endl; }
void handleValue(std::string value) { std::cout << "String: " << value << std::endl; }

// 用于终止迭代的基函数
template<typename T>
void processValues(T arg)
{
    handleValue(arg);
}

// 可变参数函数模板
template<typename T, typename ... Ts>
void processValues(T arg, Ts ... args)
{
    handleValue(arg);
    processValues(args ...); // 解包，然后递归
}

int template_try()
{
    CSolClass sol_class;
    
    sol_class.new_usertype<CTestClass>("CTestClass"
                                       , "ShowValue", &CTestClass::ShowValue
                                       , "SetValue", &CTestClass::SetValue
                                       , "_v", &CTestClass::_v
                                       );
    
    std::string str_test("Hello World!");
    
    sol_class.set("c_str", str_test);
    sol_class.do_script_file("./study/std/template_try.lua");
    
    printf("\n");
    // 不定参模板 测试
    processValues(1, 2.5, "test", 3.1415926);
    
    return 0;
}
