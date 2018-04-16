---------------------------------------------------------------------
-- lua弱表测试
-- 纯lua语法
--
-- lua垃圾回收
-- 纯lua语法
---------------------------------------------------------------------


-----------------------
-- weak table
-- https://www.lua.org/pil/17.html
-----------------------

a = { qq = 77 }
b = { hh = 99 }
setmetatable(a, b)
b.__mode = "k"                  -- now `a' has weak keys
dd = "dd"
a[dd] = 88
key = { cc = 2 }                -- creates first key
a[key] = 1
key = {}                        -- creates second key
a[key] = 2

print("before collect:")
for k, v in pairs(a) do print(v) end

collectgarbage()                -- forces a garbage collection cycle

print("after collect:")
for k, v in pairs(a) do print(v) end

print("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=--=-=-");

------------------------------------------
-- memoize function, record data
-- https://www.lua.org/pil/17.1.html
------------------------------------------
local results = {}
setmetatable(results, {__mode = "v"})  -- make values weak
function createRGB (r, g, b)
    local key = r .. "-" .. g .. "-" .. b
    if results[key] then
        return results[key]
    else
        local newcolor = {red = r, green = g, blue = b}
        results[key] = newcolor
        return newcolor
    end
end

print("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=--=-=-");

-------------------------------------
-- https://www.lua.org/pil/23.1.html
-- `S´    selects fields source, short_src, what, and linedefined
-- `l´    selects field currentline
-------------------------------------


print("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=--=-=-");

-------------------------------------
-- garbage collect
-- https://www.jianshu.com/p/8278ff0415dd
-------------------------------------
-- lua_ps = pps;
print("---- ll v " .. pps.v)
--print("---- pps: " .. pps:to_string());
pps = nil;
--collectgarbage();

print(collectgarbage("count"));

collectgarbage("setpause", 1);
--print(collectgarbage("collect"));
--print(collectgarbage("step", 1));

--ps.v = 20;
--print("ps.v = " .. ps.v);
--ps = nil;

--lua_ps = nil;
collectgarbage();

uuc = Packet.new();
--uuc.v = 31;
uuc:ShowValue();
print(uuc.v);
--print(to_string(uuc));

print("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= lua test end -=-=-=-=-=--=-=-=-=-=-=-=-=-=-=--=-=-");

