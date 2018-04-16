//
//  lua_mgr_mem.cpp
//  lua_study
//
//  Created by lifushan on 2018/3/9.
//  Copyright © 2018年 lifs. All rights reserved.
//

#include "lua_mgr_mem.hpp"
#include <stdlib.h>
#include <memory>
//#include <malloc/malloc.h>
#include <lua.hpp>

//#define SOL_CHECK_ARGUMENTS 1
//#include "sol.hpp"
//#include "assert.hpp"


class Packet {

public:
    Packet() : _v(10) {
        printf("  construct packet ====\n");
    }
    ~Packet() {
        printf("~Packet() ====\n");
    }
    
public:
    int _v;
    
};

//c code
int creatPacket(lua_State* L) {
    Packet* pack = (Packet*)malloc(sizeof(Packet));
    Packet** ud = (Packet**)lua_newuserdata(L, sizeof(Packet*));
    *ud = pack;
    pack->_v = 10;
    printf("------------ [creatPacket] -------\n");
    return 1;
}

int freePacket(lua_State* L) {
    printf("------------ [freePacket] -------\n");
    Packet** ud = (Packet**)lua_touserdata(L, -1);
    if( *ud ) {
        printf("-=-=-=- *ud[%p], v[%d] ====\n", *ud, (*ud)->_v);
        free(*ud);
        *ud = NULL;
    }
    return 0;
}

static const luaL_Reg packetlib[] = {
    {"creatPacket", creatPacket},
    {"freePacket", freePacket},
    {NULL, NULL}
};

int luaopen_packet(lua_State *L) {
    // https://stackoverflow.com/questions/19041215/lual-openlib-replacement-for-lua-5-2
//    luaL_register(L, packetlib);
    
//    lua_newtable(L);
//    luaL_setfuncs(L, packetlib, 0);
    lua_getglobal(L, "CP");
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        lua_newtable(L);
    }
    luaL_setfuncs(L, packetlib, 0);
    lua_setglobal(L, "CP");
    
    return 1;
}

int lua_mgr_mem_test() {
    
//    luaL_newstate()
//    lua_open()
//    lua_State *L = luaL_newstate();   /* opens Lua */
//    luaopen_base(L);             /* opens the basic library */
//    luaopen_table(L);            /* opens the table library */
//    luaopen_io(L);               /* opens the I/O library */
//    luaopen_string(L);           /* opens the string lib. */
//    luaopen_math(L);             /* opens the math lib. */
    
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    
    luaopen_packet(L);
    
//    luaL_dostring(L, "local pack = CP.creatPacket()");
    
    int r = luaL_dofile(L, "./study/lua_mgr_mem/lua_mgr_mem.lua");
    printf("------ [C] r = %d ====\n", r);
    
    lua_getglobal(L, "pack");
    Packet* p = (Packet*)lua_touserdata(L, -1);
    printf("-=-=-=- [C] p[%p] ====\n", p);
    if (NULL != p) {
//        p->_v = 20;
//        delete p;
//        p = NULL;
        freePacket(L);
    }
    
    {
        std::shared_ptr<Packet> pa;
        {
            std::shared_ptr<Packet> pc = std::make_shared<Packet>();
//            pa = pc;
            printf("---------- [C] 1 ========\n");
        }
        printf("---------- [C] 2 ========\n");
    }
    printf("---------- [C] 3 ========\n");
    
    return 0;
}
