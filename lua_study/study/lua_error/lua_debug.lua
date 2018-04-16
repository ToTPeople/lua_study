-----------------------
-- debug op
-- http://www.runoob.com/lua/lua-debug.html
-----------------------

function myfunction ()
    print(debug.traceback("Stack trace"))
    print(debug.getinfo(1))
    print("Stack trace end")
    return 10
end

myfunction ()
print(debug.getinfo(1))

print("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=--=-=-");

------------------------------------------
-- https://www.lua.org/pil/23.1.1.html
------------------------------------------
function newCounter ()
    local n = 0
    local k = 0
    return function ()
        k = n
        n = n + 1
        return k, n
    end
end

counter = newCounter ()
print(counter())
print(counter())

local i = 1

repeat
    name, val = debug.getupvalue(counter, i)
    if name then
        print ("index", i, name, "=", val)
        if (name == "n") then
            debug.setupvalue (counter,2,10)
        end
        i = i + 1
    end -- if
until not name

print(counter())

print("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=--=-=-");

-------------------------------------
-- https://www.lua.org/pil/23.1.html
-- `S´    selects fields source, short_src, what, and linedefined
-- `l´    selects field currentline
-------------------------------------
function traceback ()
    local level = 1
    while true do
        local info = debug.getinfo(level, "Sl")
        if not info then break end
        if info.what == "C" then   -- is a C function?
            print(level, "C function")
        else   -- a Lua function
            print(string.format("[%s]:%d",
            info.short_src, info.currentline))
        end
        level = level + 1
    end
end

traceback();

print("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=--=-=-");

-------------------------------------
-- https://www.lua.org/pil/23.2.html
-------------------------------------
debug.sethook(print, "l")

function trace (event, line)
    local s = debug.getinfo(2).short_src
    print(s .. ":" .. line)
end

debug.sethook(trace, "l")


print("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=--=-=-");

