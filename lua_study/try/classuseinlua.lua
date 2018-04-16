local snapshot = require "snapshot"
local S1 = snapshot()

print("--- A class ---");
a = A.new();
print(a);
a = A.new();
print(a);
a:call();
a:only_parent_has();

print("\n--- B class ---");
b = B.new();
b:call();
b:only_parent_has();
b:only_b_has();

print("\n--- C class ---");
c = C.new();
-- c:only_parent_has();
c:only_b_has();
c:call();
c:deal();

print("\n--- CObjecWithNamespace class ---")
obj = CObjecWithNamespace.new(1010);
obj:show();

print(' lll = ' .. lll);
lll = 999988887777666;
print(' new lll = ' .. lll);

print("\n--- pc class ---");
cu:call();
-- pc = nil;
if pc == nil then
    print("pc == nil");
    print(pc);
end

-- compare with "nil"
if pc == "nil" then
    print("pc == nil");
    print(pc);
end
collectgarbage();
-- cu:call();
print("\n--- cu class end ===")

-- a = nil;
-- b.delete();

print("\n------------------------- lua memory check print ===================")
-- lua memory check
local S2 = snapshot()

for k,v in pairs(S2) do
    if S1[k] == nil then
       print(k,v)
    end
end

print("\n------------------------- lua memory check print end ===================\n")
