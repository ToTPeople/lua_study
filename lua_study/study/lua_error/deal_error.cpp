//
//  deal_error.cpp
//  lua_study
//
//  Created by lifushan on 2018/3/8.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include "deal_error.hpp"

/*
 http://sol2.readthedocs.io/en/latest/functions.html#function-argument-handling
 You can have functions here and on usertypes check to definitely make sure that the types passed to C++ functions are what they’re supposed to be by adding a #define SOL_CHECK_ARGUMENTS before including Sol, or passing it on the command line. Otherwise, for speed reasons, these checks are only used where absolutely necessary (like discriminating between overloads). See safety for more information.
 */
#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "assert.hpp"

namespace {
//#define TEST_ERROR
}

int deal_error_test() {
    
    sol::state lua;
    lua.open_libraries();
    
#ifdef TEST_ERROR
    lua.script_file("./study/lua_error/lua_error_op.lua");
#else
    lua.script_file("./study/lua_error/lua_debug.lua");
#endif
    
    return 0;
}
