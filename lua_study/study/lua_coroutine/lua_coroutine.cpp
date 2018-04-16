//
//  lua_coroutine.cpp
//  lua_study
//
//  Created by lifushan on 2018/3/16.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include "lua_coroutine.hpp"
#include <string>

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"

int lua_coroutine()
{
    sol::state  lua;
    lua.open_libraries();
    
    
    lua.script_file("./study/lua_coroutine/lua_coroutine.lua");
    
    return 0;
}
