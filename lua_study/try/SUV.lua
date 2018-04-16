-------------------
-- SUV
-------------------
require "./try/Car"

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
-- SUV table/class test
-------------------
print('------------------------- SUV.lua test st -------------------')
local suv = SUV.new("Suzuki",150,true)
-- call inherited method
print(suv:getBrand())
-- call the overridden method
print(suv:getInfo())
suv:only_test()

print(type(SUV), type(suv));
print('------------------------- SUV.lua test en -------------------')

-- so that the SUV can be imported by other classes via 'require "car.SUV"'
return SUV;
