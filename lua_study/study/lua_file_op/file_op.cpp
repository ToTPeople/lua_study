//
//  file_op.cpp
//  lua_study
//
//  Created by lifushan on 2018/3/8.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include "file_op.hpp"

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"

int file_op_test() {
    
    sol::state lua;
    lua.open_libraries();
    
    lua.script_file("./study/lua_file_op/lua_file_op.lua");
    
    return 0;
}
