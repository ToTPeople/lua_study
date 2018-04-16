//
//  yunf_lua_mgr_mem.cpp
//  lua_study
//
//  Created by lifushan on 2018/3/12.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include "yunf_lua_mgr_mem.hpp"
#include <stdlib.h>

#include <lua.hpp>

/*
 作者：云风
 代码来源：http://blog.codingnow.com/cloud
 https://blog.codingnow.com/2007/10/lua_c_object_reference.html
 https://blog.codingnow.com/cloud/LuaReferObject
 */

static void *dummy=0;

struct gc_object {
    void *obj;
    void (*release)(void *);
};

static int release_object(lua_State *L)
{
    struct gc_object *gco = (struct gc_object*)lua_touserdata(L,1);
    gco->release(gco->obj);
    return 0;
}

/* 模块初始化 */
void cobj_init(lua_State *L)
{
    lua_pushlightuserdata(L, &dummy);
    lua_newtable(L);
    lua_createtable(L,0,1);
    lua_pushstring(L,"v");
    lua_setfield(L,-2,"__mode");
    lua_setmetatable(L,-2);
    
    lua_createtable(L,0,1);
    lua_pushcfunction(L, release_object);
    lua_setfield(L,-2,"__gc");
    
    lua_pushlightuserdata(L, (void*)release_object);
    lua_pushvalue(L,-2);
    lua_rawset(L,-4);
    
    lua_pushlightuserdata(L, (void*)release_object);
    lua_rawset(L,-3);
    
    lua_settable(L,LUA_REGISTRYINDEX);
}

static void get_reftable(lua_State *L)
{
    lua_pushlightuserdata(L, &dummy);
    lua_gettable(L,LUA_REGISTRYINDEX);
}

/* 把 C 对象指针 obj 压入堆栈，如果不提供释放函数 release ，则以 lightuserdata 形式存放。
 如果提供 release 函数，则会在 gc 环节调用 */
void cobj_push(lua_State *L,void *obj,void (*release)(void*))
{
    if (release==0) {
        lua_pushlightuserdata(L,obj);
    }
    else {
        get_reftable(L);
        lua_pushlightuserdata(L,obj);
        lua_rawget(L,-2);
        
        if (lua_isnil(L,-1)) {
            struct gc_object *gco;
            lua_pop(L,1);
            gco=(struct gc_object *)lua_newuserdata(L,sizeof(*gco));
            gco->obj=obj;
            gco->release=release;
            
            lua_pushlightuserdata(L, (void*)release_object);
            lua_rawget(L,-3);
            lua_setmetatable(L,-2);
            
            lua_pushlightuserdata(L,obj);
            lua_pushvalue(L,-2);
            lua_rawset(L,-4);
        }
        
        lua_replace(L,-2);
    }
}

/* 将堆栈上的对象转换为 C 指针 */
void* cobj_get(lua_State *L,int idx)
{
    if (lua_islightuserdata(L,idx)) {
        return lua_touserdata(L,idx);
    }
    else {
        struct gc_object *gco=(struct gc_object *)lua_touserdata(L,idx);
        return gco->obj;
    }
}

/* 把 obj 对应在 lua 状态机中的对象引用数量加 1 ，返回新的引用次数，出错返回 -1 */
int cobj_addref(lua_State *L,void *obj)
{
    int r=-1;
    get_reftable(L);
    lua_pushlightuserdata(L,obj);
    lua_rawget(L,-2);
    if (!lua_isnil(L,-1)) {
        lua_pushvalue(L,-1);
        lua_rawget(L,-3);
        r=lua_tointeger(L,-1) + 1;
        lua_pop(L,1);
        lua_pushinteger(L,r);
        lua_rawset(L,-3);
    }
    lua_pop(L,1);
    return r;
}

/* 把 obj 对应在 lua 状态机中的对象引用数量减 1 ，返回新的引用次数，出错返回 -1 */
int cobj_release(lua_State *L,void *obj)
{
    int r=-1;
    get_reftable(L);
    lua_pushlightuserdata(L,obj);
    lua_rawget(L,-2);
    if (!lua_isnil(L,-1)) {
        lua_pushvalue(L,-1);
        lua_rawget(L,-3);
        r=lua_tointeger(L,-1) - 1;
        lua_pop(L,1);
        if (r<=0) {
            lua_pushnil(L);
        }
        else {
            lua_pushinteger(L,r);
        }
        lua_rawset(L,-3);
    }
    lua_pop(L,1);
    return r;
}

int yunf_lua_mgr_mem_test() {
    return 0;
}

