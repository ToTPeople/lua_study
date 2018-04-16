//
//  lua_inherite_c_class.cpp
//  lua_study
//
//  Created by lifushan on 2018/4/16.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include <stdio.h>

#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"


int lua_inherite_c_class()
{
    sol::state lua;
    lua.open_libraries();
    
    lua.script_file("./study/lua_inherite_c_class.lua");
    
    return 0;
}
