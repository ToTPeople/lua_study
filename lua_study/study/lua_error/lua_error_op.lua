--------------------------------------------------------------------------------------------
-- error op
---- syntax error
--------------------------------------------------------------------------------------------

-- local a == 2
-- result in:
-- libc++abi.dylib: terminating with uncaught exception of type sol::error: sol: syntax error: ./study/lua_error/lua_error_op.lua:6: unexpected symbol near '=='

-- for less do,,, it should be    for , , , do ... end
--[[
for i = 1, 10
    print(i);
end
]]
-- result in:
-- libc++abi.dylib: terminating with uncaught exception of type sol::error: sol: syntax error: ./study/lua_error/lua_error_op.lua:11: 'do' expected near 'print'

-------------------------------------------------------------------------------------------
-- error op
---- runtime error
-- https://www.lua.org/pil/8.4.html
-- https://www.lua.org/pil/8.5.html
-- http://www.runoob.com/lua/lua-error-handling.html
-------------------------------------------------------------------------------------------

function add(a,b)
    --assert(type(a) == "number", "a 不是一个数字");
    --assert(type(b) == "number", "b 不是一个数字");

    return a+b;
end

-- less one param, and lua use nil instead
-- add(10);
-- result in:
--[[
    libc++abi.dylib: terminating with uncaught exception of type sol::error: sol: runtime error: ./study/lua_error/lua_error_op.lua:25: attempt to perform arithmetic on a nil value (local 'b')
    stack traceback:
    ./study/lua_error/lua_error_op.lua:25: in function 'add'
    ./study/lua_error/lua_error_op.lua:28: in main chunk
]]

function myfunction ()
    n = n/nil
end

function myerrorhandler( err )
    print( "ERROR:", err )
end

status = xpcall( myfunction, myerrorhandler )
print( status)
--print(debug.traceback());
--[[    输出
ERROR:    ./study/lua_error/lua_error_op.lua:42: attempt to perform arithmetic on a nil value (global 'n')
false
Program ended with exit code: 0
]]

local status, error = pcall(myfunction);
if not status then
    print(error);
end
--[[    输出
./study/lua_error/lua_error_op.lua:42: attempt to perform arithmetic on a nil value (global 'n')
Program ended with exit code: 0
]]

--
local status, err = pcall(function () a = 'a'+1 end)
print(err)
--> stdin:1: attempt to perform arithmetic on a string value

local status, err = pcall(function () error("my error") end)
print(err)
--> stdin:1: my error

