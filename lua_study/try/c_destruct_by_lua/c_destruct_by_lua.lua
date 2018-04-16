-----------------------
-- lua destruct test
--
-----------------------

--local ca = CA.new(10)
ca = CA.new(60);

ca:ShowValue();
ca:SetValue(30);
ca:ShowValue();

--ca = nil;
collectgarbage();

print(Cal(3, 10));

ss = SA.new();

--tolua.cast(Cal, "number");
--ss:SetFunc(Cal);

