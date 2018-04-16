
local meta = getmetatable(A.new())
meta.__index = meta
meta.call = A.call
--meta.call = A:call
-- meta.only_parent_has = A:only_parent_has


-------------------
-- YY table/class
--  lua table/class inherition
-- https://www.lua.org/pil/16.2.html
-------------------
YY = {}
YY.__index = YY

-- contructor
function YY.new()
local instance = {}

-- set YY as prototype for the new instance
setmetatable(instance, YY)
return instance
end

-- set up inheritance by making A as prototype for YY. Now YY can access & override A's methods
setmetatable(YY,{__index = A})
--setmetatable(YY, { __index = meta })

--[[ ******************
setmetatable(YY,{__index = function()
    return A;
end
})]]


-- method definitions
function YY:test()
    --self:call();
--self.call();
    print("YY:test -=-=-=-=")
    print("")
end

-------------------
-- YY table/class test
-------------------
print('------------------------- YY.lua test st -------------------')
local yy = YY.new()
--yy.only_parent_has(A.new())
--yy.call(A.new())
--yy:call(A.new())
--yy.call()
yy:test()

local a = A.new();
a:call();
a.call(a);
a:only_parent_has();

print(type(meta), type(A), type(B), type(C));
print('------------------------- YY.lua test en -------------------')


return YY;
