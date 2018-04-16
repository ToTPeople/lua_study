
print("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");

-----------------------
-- table_taxn函数
-- 计算表中最大值，table.maxn在Lua5.2以上版本中已无法使用
-- 自定义计算表中最大键值函数 table_maxn，即计算表的元素个数
-----------------------
function table_maxn(t)
    local tot = 0;
    for cnt, v in pairs(t) do
        tot = cnt;
    end
    return tot;
end

-----------------------
-- __index、元表测试
--
-----------------------
local mymeta = { meta_var = 13 }
local mytable = { my_var = 99 }
setmetatable(mytable, { __index = mymeta }) -- not setmetatable(mytable, mymeta)
print(mytable.my_var, mytable.meta_var, mytable.everything)

print("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");

-----------------------
-- __newindex测试
-- 新增元素
-----------------------
mytable = setmetatable( {key1 = "v1"}, { __newindex = mymeta } )
print("proto is: " .. mytable.key1, mytable.meta_var);
mytable.key1 = "new v1"
mytable.new_key = "new key"
print("now is: " .. mytable.key1, mytable.meta_var, mytable.new_key, " /mymeta table is: ", mymeta.new_key)

print("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");

-----------------------
-- __add
--
-----------------------
--[[    非数值table.insert调用出错
mytable = setmetatable( {key1 = "v1"}, {

    __add = function(mytable, newtable)
        for cnt, v in pairs(newtable) do
            table.insert(mytable, table_taxn(mytable)+1, v);
        end
        return mytable;
    end
})
]]
-- 两表相加操作
mytable = setmetatable({ 1, 2, 3 }, {
    __add = function(mytable, newtable)
        for i = 1, table_maxn(newtable) do
            table.insert(mytable, table_maxn(mytable)+1,newtable[i])
        end
        return mytable
    end
})

secondtable = {4,5,6}

print("proto is:");
for k, v in pairs(mytable) do
    print(k, v);
end

mytable = mytable + secondtable;
-- mytable = mytable + mymeta;

print("now is:");
for k, v in pairs(mytable) do
    print(k, v);
end

print("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");

-----------------------
-- __call
--
-----------------------
-- 两表数值相加求和操作
mytable = setmetatable({ 1, 2, 3 }, {
    __call = function(mytable, newtable)
        local sum = 0;
        local tot = table_maxn(mytable);
        for i = 1, tot do
            sum = sum + mytable[i];
        end

        tot = table_maxn(newtable);
        for i = 1, tot do
            sum = sum + newtable[i];
        end

        return sum;
    end
})

newtable = {10,20,30}
print(mytable(newtable))
print(mytable)

print("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");

-----------------------
-- __tostring
--
-----------------------
mytable = setmetatable({ 10, 20, 30 }, {
    __tostring = function(mytable)
        local sum = 0
        for k, v in pairs(mytable) do
            sum = sum + v
        end
        return "表所有元素的和为 " .. sum
    end
})

print(mytable)

print("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");

-----------------------
--
--
-----------------------

print("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");

-----------------------
--
--
-----------------------
