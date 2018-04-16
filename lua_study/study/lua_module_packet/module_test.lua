
local m = require "./study/lua_module_packet/luamodule";

-- 使用module名 或 别名m
print("module var value is " .. module_test.var);

print(m:func_p1());
print(m:func_p3());

