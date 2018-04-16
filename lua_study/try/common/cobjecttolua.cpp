//
//  cobjecttolua.cpp
//  lua_study
//
//  Created by lifushan on 2018/3/5.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include "cobjecttolua.hpp"
#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"


int script_pushobject(lua_State* L, void* object)
{
    void** ud;
    if (luaL_newmetatable(L, "script")) {
        // 在注册表中创建一个表存放所有的 object 指针到 userdata 的关系。
        // 这个表应该是一个 weak table ，当 Lua 中不再存在对 C 对象的引用会删除对应的记录。
        lua_newtable(L);
        lua_pushliteral(L, "kv");
        lua_setfield(L, -2, "__mode");
        lua_setmetatable(L, -2);
    }
    lua_rawgetp(L, -1, object);
    if (lua_type(L, -1) == LUA_TUSERDATA) {
        ud = (void**)lua_touserdata(L, -1);
        if (*ud == object) {
            lua_replace(L, -2);
            return 0;
        }
        // C 对象指针被释放后，有可能地址被重用。
        // 这个时候，可能取到曾经保存起来的 userdata ，里面的指针必然为空。
        assert(*ud == NULL);
    }
    
    ud = (void**)lua_newuserdata(L, sizeof(void*));
    *ud = object;
    lua_pushvalue(L, -1);
    lua_rawsetp(L, -4, object);
    lua_replace(L, -3);
    lua_pop(L, 1);
    return 1;
}

void* script_toobject(lua_State* L, int index)
{
    void** ud = (void**)lua_touserdata(L, index);
    if (NULL == ud) {
        return NULL;
    }
    
    // 如果 object 已在 C 代码中销毁，*ud 为 NULL 。
    return *ud;
}

void script_deleteobject(lua_State* L, void* object)
{
    luaL_getmetatable(L, "script");
    if (lua_istable(L, -1)) {
        lua_rawgetp(L, -1, object);
        if (lua_type(L, -1) == LUA_TUSERDATA) {
            void** ud = (void**)lua_touserdata(L, -1);
            // 这个 assert 防止 deleteobject 被重复调用。
            assert(*ud == object);
            // 销毁一个被 Lua 引用住的对象，只需要把 *ud 置为 NULL 。
            *ud = NULL;
        }
        lua_pop(L, 2);
    } else {
        // 有可能从未调用过 pushobject ，此时注册表中 script 项尚未建立。
        lua_pop(L, 1);
    }
}
