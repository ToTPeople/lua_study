print("--- A class ---");
a = A.new();
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
