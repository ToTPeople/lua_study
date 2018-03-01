#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "tutorials_func_define.h"
#include "assert.hpp"

int set_and_get_variables_exists() {
	sol::state lua;
	lua.open_libraries(sol::lib::base);

	lua.script("exists = 250");

	int first_try = lua.get_or("exists", 322);
	c_assert(first_try == 250);

	lua.set("exists", sol::lua_nil);
	int second_try = lua.get_or("exists", 322);
	c_assert(second_try == 322);

	return 0;
}
