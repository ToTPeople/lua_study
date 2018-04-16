//
//  main.cpp
//  lua_study
//
//  Created by lifushan on 2018/2/28.
//  Copyright © 2018年 lifs. All rights reserved.
//

#define SOL_CHECK_ARGUMENTS 1
#include <iostream>

#include "tutorials_func_define.h"
#include "classinheritance.hpp"
#include "c_vector_to_lua.hpp"
#include "c_destruct_by_lua_test.hpp"
#include "module_packet_test.hpp"
#include "metatable_method_test.hpp"
#include "file_op.hpp"
#include "deal_error.hpp"
#include "weak_table.hpp"
#include "lua_mgr_mem.hpp"
#include "lua_coroutine.hpp"

#include "common_std_header.h"
#include "study_header.h"

int main(int, char*[]) {
    // study test
//    return lua_collect_garbage();
//    return lua_inherite_c_class();
    
    // common std
//    return function_test();
//    return template_try();
    
//    return lua_coroutine();
//    return functions_all();
//    return lua_mgr_mem_test();
//    return weak_table_test();
    return deal_error_test();

    // try
    return c_destruct_by_lua_test();
    class_inheritance();

    return 0;
}


