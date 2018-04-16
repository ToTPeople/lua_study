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
-- Car table/class test
-------------------
print('------------------------- Car.lua test st -------------------')
local c = Car.new("Honda",100)
c:getInfo();
print('------------------------- Car.lua test en -------------------')

-- so that the Car can be imported by other classes via 'require "car.Car"'
return Car

