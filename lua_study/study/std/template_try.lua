------------------------------------------
-- 测试 通过C端模板传递类型、变量
------------------------------------------

print("-------------------------- lua test st ---------------")
print(c_str);

ct = CTestClass.new();
ct:ShowValue();
ct._v = 97;
ct:ShowValue();
ct:SetValue(101);
ct:ShowValue();


print("-------------------------- lua test en ---------------")
