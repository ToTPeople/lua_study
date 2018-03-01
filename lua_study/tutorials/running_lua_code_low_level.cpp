/*
 * sol::state.script or sol::state.script_file is execute and code effective
 * sol::state.load   or sol::state.load_file   is not execute, should after execute
 */
#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "tutorials_func_define.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include "assert.hpp"

int running_lua_code_low_level() {
	std::cout << "=== running lua code (low level) example ===" << std::endl;
	
	{
		std::ofstream out("a_lua_script.lua");
		out << "print('hi from a lua script file')";
	}

	sol::state lua;
	lua.open_libraries(sol::lib::base);

	// load file without execute
	sol::load_result script1 = lua.load_file("a_lua_script.lua");
	//execute
	script1();

	// load string without execute
	sol::load_result script2 = lua.load("a = 'test'");
    lua.script("a = 'script test'");
    std::string str = lua["a"];
    printf("==== before execute a[%s] ---\n", str.c_str());
	//execute
	sol::protected_function_result script2result = script2();
	// optionally, check if it worked
	if (script2result.valid()) {
		// yay!
        printf("yay, script2result valid\n");
        str = lua["a"];
        printf("==== after execute a[%s] ---\n", str.c_str());
	}
	else {
		// aww
        printf("aww, script2result not valid\n");
	}

	sol::load_result script3 = lua.load("return 24");
	// execute, get return value
	int value2 = script3();
	c_assert(value2 == 24);

	std::cout << std::endl;

	{
		std::remove("a_lua_script.lua");
	}

	return 0;
}
