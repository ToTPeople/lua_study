----------------------------------------------
-- lua中自定义实现class包装类，模拟C++类
-- 纯lua语法
-- from cocos2dx源码
----------------------------------------------

--------
local setmetatableindex_
setmetatableindex_ = function(t, index)
    if type(t) == "userdata" then
        local peer = tolua.getpeer(t)
        if not peer then
            peer = {}
            tolua.setpeer(t, peer)
        end
        setmetatableindex_(peer, index)
    else
        local mt = getmetatable(t)
        if not mt then mt = {} end
        if not mt.__index then
            mt.__index = index
            setmetatable(t, mt)
        elseif mt.__index ~= index then
            setmetatableindex_(mt, index)
        end
    end
end
setmetatableindex = setmetatableindex_
--------

function class(classname, ...)
local cls = {__cname = classname}

local supers = {...}
for _, super in ipairs(supers) do
local superType = type(super)
assert(superType == "nil" or superType == "table" or superType == "function",
string.format("class() - create class \"%s\" with invalid super class type \"%s\"",
classname, superType))

if superType == "function" then
assert(cls.__create == nil,
string.format("class() - create class \"%s\" with more than one creating function",
classname));
-- if super is function, set it to __create
cls.__create = super
elseif superType == "table" then
if super[".isclass"] then
-- super is native class
assert(cls.__create == nil,
string.format("class() - create class \"%s\" with more than one creating function or native class",
classname));
cls.__create = function() return super:create() end
else
-- super is pure lua class
cls.__supers = cls.__supers or {}
cls.__supers[#cls.__supers + 1] = super
if not cls.super then
-- set first super pure lua class as class.super
cls.super = super
end
end
else
error(string.format("class() - create class \"%s\" with invalid super type",
classname), 0)
end
end

cls.__index = cls
if not cls.__supers or #cls.__supers == 1 then
setmetatable(cls, {__index = cls.super})
else
setmetatable(cls, {__index = function(_, key)
local supers = cls.__supers
for i = 1, #supers do
local super = supers[i]
if super[key] then return super[key] end
end
end})
end

if not cls.ctor then
-- add default constructor
cls.ctor = function() end
end
cls.new = function(...)
local instance
if cls.__create then
instance = cls.__create(...)
else
instance = {}
end
setmetatableindex(instance, cls)
instance.class = cls
instance:ctor(...)
return instance
end
cls.create = function(_, ...)
return cls.new(...)
end

return cls
end



--==============================================

--[[

function clone(object)--clone函数
local lookup_table = {}--新建table用于记录
local function _copy(object)--_copy(object)函数用于实现复制
if type(object) ~= "table" then
return object   ---如果内容不是table 直接返回object(例如如果是数字\字符串直接返回该数字\该字符串)
elseif lookup_table[object] then
return lookup_table[object]--这里是用于递归滴时候的,如果这个table已经复制过了,就直接返回
end
local new_table = {}
lookup_table[object] = new_table--新建new_table记录需要复制的二级子表,并放到lookup_table[object]中.
for key, value in pairs(object) do
new_table[_copy(key)] = _copy(value)--遍历object和递归_copy(value)把每一个表中的数据都复制出来
end
return setmetatable(new_table, getmetatable(object))--每一次完成遍历后,就对指定table设置metatable键值
end
return _copy(object)--返回clone出来的object表指针/地址
end
--[[
clone  深度克隆一个值。
格式：value = clone(值)
用法示例：
-- 下面的代码，t2 是 t1 的引用，修改 t2 的属性时，t1 的内容也会发生变化
local t1 = {a = 1, b = 2}
local t2 = t1
t2.b = 3    -- t1 = {a = 1, b = 3} <-- t1.b 发生变化

-- clone() 返回 t1 的副本，修改 t2 不会影响 t1
local t1 = {a = 1, b = 2}
local t2 = clone(t1)
t2.b = 3    -- t1 = {a = 1, b = 2} <-- t1.b 不受影响
--]]

--[[
-- Create an class.

function class(classname, super)

local superType = type(super)
local cls

if superType ~= "function" and superType ~= "table" then
superType = nil
super = nil
end

if superType == "function" or (super and super.__ctype == 1) then
-- inherited from native C++ Object
cls = {}

if superType == "table" then
-- copy fields from super
for k,v in pairs(super) do cls[k] = v end

cls.__create = super.__create
cls.super    = super
print("------------------ [lfs] super is table --------")
else
cls.__create = super
print("------------------ [lfs] super not table --------")
end
print(super)

cls.ctor    = function() end
cls.__cname = classname
cls.__ctype = 1

function cls.new(...)
local instance = cls.__create(...)
-- copy fields from class to native object
for k,v in pairs(cls) do instance[k] = v end
instance.class = cls
instance:ctor(...)
return instance
end

else
-- inherited from Lua Object
if super then
cls = clone(super)
cls.super = super
else
cls = {ctor = function() end}
end

cls.__cname = classname
cls.__ctype = 2 -- lua
cls.__index = cls

function cls.new(...)
local instance = setmetatable({}, cls)
instance.class = cls
instance:ctor(...)
return instance
end
end

return cls
end

]]

----------------------------------------------------------------------------------
----------------------------------------------
-- 基类定义、测试
----------------------------------------------
print("------------******** 基类测试 *******---------------")
Hero = class("Hero");

function Hero:ctor()
self.name = "llllllll";
self.age = 23;
end

hero = Hero.new();

print(hero.name)
print(hero.age)

Inherit = class("Inherit", function()
return Hero.new();
end
)

function Inherit:ctor()
self.walkAction = nil;
self.runAction = nil;
end

inherit = Inherit.new();

print(inherit.name)
print(inherit.age)

print("----------------***********************------------------")

----------------------------------------------------------------------------------


print("-=-=-=-=-=-=-=-=-=- 继承类测试 -=-=-=-=-=-=-=-=-=-=-=-");

Hero = class("Hero")

-- 基类 Hero 构造函数
function Hero:ctor()
    self.name = "llllllll";
    self.age = 23;
end

Inherit = class("Inherit",
    function()
        return Hero.new();
    end
)
Inherit.__index = Inherit

-- 继承类 Inherit 构造函数
function Inherit:ctor()
    self.walkAction = 1313;
    self.runAction = "hahahahahhah";
end

inherit = Inherit.new();

print(inherit.name)
print(inherit.age)


print("----------------***********************----------------")


