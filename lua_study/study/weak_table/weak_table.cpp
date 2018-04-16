//
//  weak_table.cpp
//  lua_study
//
//  Created by lifushan on 2018/3/8.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include "weak_table.hpp"

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"

namespace {
    class Packet {
        
    public:
        Packet() : _v(10) {
            printf("  construct packet ====\n");
        }
        ~Packet() {
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
    
}

static void method_2_gc(Packet* p)
{
    printf("~~~~~ method_2_gc() p[%p] =====\n", p);
}

Packet* create_packet()
{
    printf("------------------------ [create_packet] --------------\n");
    Packet* p = new Packet();
    return p;
}


int weak_table_test() {
    
    {
        {
            sol::state lua;
            lua.open_libraries();
            
            lua.new_usertype<Packet>("Packet"
                                     , "ShowValue", &Packet::ShowValue
                                     , "SetValue", &Packet::SetValue
                                     , "v", sol::readonly(&Packet::_v)
                                     // 两种方式自定义设置 类析构 时调用哪个方法回收资源
                                     , "__gc", sol::destructor(method_2_gc)
//                                     , sol::meta_function::garbage_collect, sol::destructor(method_2_gc)
                                     );
            
            // 若key和之前传递的相同，则覆盖之前类型
//            lua.new_usertype<Packet>("Packet"//, sol::constructor_wrapper<<#typename Functions#>>//, sol::constructors<Packet()>()
//                                     //                                     , "v", &Packet::_v
//                                     , "ShowValue", &Packet::ShowValue
//                                     , "SetValue", &Packet::SetValue
//                                     , "v", sol::readonly(&Packet::_v)
//                                     );
            
            printf("-=-=-=-=-=-=-=----------------- 0 =============================\n");
            
            {
                {
                    Packet* pQ = new Packet();
                    std::shared_ptr<Packet> pc = std::shared_ptr<Packet>(pQ);
                    
                    lua.set("pps", pc);
                    lua.script_file("./study/weak_table/lua_weak_table.lua");
//                    lua.collect_garbage();
                    printf("---------- 1 ========\n");
                }
                printf("---------- 2 ========\n");
//                lua.script_file("./study/weak_table/lua_weak_table.lua");
                printf("---------- 2.5 ========\n");
            }
            printf("---------- 3 ========\n");
        }
        printf("---------- 4 ========\n");
    }
    printf("---------- 5 ========\n");
    
    return 0;
}
