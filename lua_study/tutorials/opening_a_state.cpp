#define SOL_CHECK_ARGUMENTS 1
#include "sol.hpp"
#include "tutorials_func_define.h"
#include <iostream>
#include "assert.hpp"

int opening_a_state(int, char*[]) {
	std::cout << "=== opening a state example ===" << std::endl;

	sol::state lua;
	// open some common libraries
	lua.open_libraries(sol::lib::base, sol::lib::package);
	lua.script("print('bark bark bark!')");

	std::cout << std::endl;

	return 0;
}
