//
//  cobjecttolua.hpp
//  lua_study
//
//  Created by lifushan on 2018/3/5.
//  Copyright © 2018年 lifs. All rights reserved.
//

#ifndef cobjecttolua_hpp
#define cobjecttolua_hpp

#include <stdio.h>

struct lua_State;

int script_pushobject(lua_State* L, void* object);

void* script_toobject(lua_State* L, int index);

void script_deleteobject(lua_State* L, void* object);

#endif /* cobjecttolua_hpp */
