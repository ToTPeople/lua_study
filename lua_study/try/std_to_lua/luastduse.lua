



function f (x)
    print("container has:")
    for k=1,#x do
        local v = x[k]
        print("\t", k, v:ShowValue())
        --print("\t", k, v)
    end
    print()
end

-- 类对象 vector测试

f(vecTest);

--vecT = CTestVec.new();
local vecT = CTestVec.new();
vecT:SetValue(1010);
local newA = A.new(777);
vecT:AddA(newA);

vecTest:add(vecT);

f(vecTest)

vecTest:erase(1);
--vecTest:clear();
f(vecTest)


testa = CTestVec.GetAIns();
testa:ShowValue();

tt = CTestVec.GetAIns(10);
tt:ShowValue();
print("----------------------------------- lua file test end --------------------------------------");


--[[        环境变量测试
for n in pairs(_G) do
    print(n)
end
]]
-------------------------------------------------------------------------

--[[        闭包测试
-- closure
function Create(n)
local function foo1()
print(n)
end
local function foo2()
n = n + 10
end
return foo1,foo2
end

f1,f2 = Create(2015)
f1() -- 打印2015

f2()
f1() -- 打印2025

f3, f4 = Create(2015)
f3()
f4()
f3()

f2()
f1() -- 打印2035
]]
-------------------------------------------------------------------------

--[[    int vector对象测试

arr:add(1010);
f(arr);

arr:erase(2);
f(arr);

]]
-------------------------------------------------------------------------
