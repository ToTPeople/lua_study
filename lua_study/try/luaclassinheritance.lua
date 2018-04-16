require "./try/Car"
require "./try/SUV"
require "./try/YY"
require "./try/tmp_test"



-------------------
-- tmp test
-------------------
some_table = {} -- { some_val = 100 }
some_table.__index = some_table

function some_table.new(val)
    local inst = {
        some_val = val
    }

    setmetatable(inst, some_table)
    return inst
end

function some_table:add_to_some_val(value)
    self.some_val = self.some_val + value
    print("self.some_val = " .. self.some_val)
end

function print_some_val()
    print("some_table.some_val = " .. some_table.some_val)
end

-------------------
-- main program
-------------------


local a = A.new();
a:call();
a:only_parent_has();


print("-=-=-=-=-=--=-=-")

local test = some_table.new(30)
test:add_to_some_val(20)

ts = some_table.new(50)

print("lua end--------")
print(type(A), type(B), type(C), type(a));

cc = Car.new("BMW", 100000);
dd = SUV.new("Ben", 200000, true);
