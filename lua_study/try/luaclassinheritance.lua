-- A.__index = A

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

-- method definitions
function YY:test()
    print("YY:test -=-=-=-=")
    print("")
end

-------------------
-- tmp test
-------------------
some_table = { some_val = 100 }

function some_table:add_to_some_val(value)
    self.some_val = self.some_val + value
end

function print_some_val()
    print("some_table.some_val = " .. some_table.some_val)
end

-------------------
-- Car table/class
-- http://masputih.com/2012/04/easy-inheritance-modularity-in-lua
-------------------
Car = {}
Car.__index = Car

-- constructor
function Car.new(brand,price)
    local instance = {
        _brand = brand,
        _price = price
    }

    -- set Car as prototype for the new instance
    setmetatable(instance, Car)
    return instance
end

-- method definitions
function Car:getBrand()
    return self._brand;
end

function Car:getPrice()
    return self._price;
end

function Car:only_test()
    print("Car:only Car has =======")
end

function Car:getInfo()
    print("Brand",self:getBrand(),"price:",self:getPrice())
end


-------------------
-- SUV
-------------------
SUV = {};
-- constructor
SUV.__index = SUV
function SUV.new(brand,price,is4WD)
    local instance = {
        _is4WD = is4WD,
        _price = price,
        _brand = brand,
    }

    -- set SUV as prototype for instance
    setmetatable(instance,SUV)
    return instance
end

-- set up inheritance by making Car as prototype for SUV. Now SUV can access & override Car's methods
setmetatable(SUV,{__index = Car})
-- setmetatable(SUV, Car)

-- instance method
function SUV:get4WD()
    return self._is4WD;
end
-- override
function SUV:getInfo()
    print("SUV Brand",self:getBrand(),", price:",self:getPrice(),", 4WD",self:get4WD())
end

-------------------
-- main program
-------------------
local c = Car.new("Honda",100)
c:getInfo();

local suv = SUV.new("Suzuki",150,true)
-- call inherited method
print(suv:getBrand())
-- call the overridden method
print(suv:getInfo())
suv:only_test()


local a = A.new();
a:call();
a:only_parent_has();

-- local yy = A.new()
yy = YY.new()
-- yy:only_parent_has()
-- yy:call()
yy:test()

--local a = A.new();
--a:call();
--a:only_parent_has();

print("lua end--------")

cc = Car.new("BMW", 100000);
dd = SUV.new("Ben", 200000, true);
