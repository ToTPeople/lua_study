//
//  module_packet_test.cpp
//  lua_study
//
//  Created by lifushan on 2018/3/8.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include "module_packet_test.hpp"

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"

int module_packet_test() {
    sol::state lua;
    lua.open_libraries();
    
    lua.script_file("./study/lua_module_packet/module_test.lua");
    
    
    return 0;
}
