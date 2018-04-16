------------------------------------------
-- 函数指针 通过std::function传递测试
------------------------------------------


print(bezierfunction(13131.01), bbb, aaa);

aaa:f();
--aaa:set_func(bezierfunction);

vv = VB.new();
vv:f();
vv:set_func(bezierfunction);

print("-----------------------------------------");

print(test_bool(3.14, true));

cvv = CVA.new();
-- lua端转失败
-- cvv:lua_wrap_set_func(bezierfunction);


print("------------------ lua end -----------------------");

