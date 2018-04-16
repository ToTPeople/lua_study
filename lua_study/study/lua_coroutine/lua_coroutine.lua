------------------------------------------
-- lua coroutine学习，resume与yield配合使用
-- 纯lua语法
------------------------------------------

print("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= lua coroutine test st -=-=-=-=--=-=-=-=-=-=-=-=-=-=--=-=-");
-- http://www.runoob.com/lua/lua-coroutine.html
-- http://blog.csdn.net/wzzfeitian/article/details/8832017

-- <!-- lang: lua -->
function foo(a)
    print("foo", a)
    return coroutine.yield(2 * a)
end


co = coroutine.create(function ( a, b )
        print("co-body", a, b)
        local r = foo(a + 1)
        print("co-body", r)
        local r, s = coroutine.yield(a + b, a - b)
        print("co-body", r, s)

        return b, "end"
    end
)

print(coroutine.status(co))

print("main", coroutine.resume(co, 1, 10))
print(coroutine.status(co))
print("main", coroutine.resume(co, "r"))
print("main", coroutine.resume(co, "x", "y"))
print(coroutine.status(co))
print("main", coroutine.resume(co, "x", "y"))

print("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= lua coroutine test en -=-=-=-=--=-=-=-=-=-=-=-=-=-=--=-=-");


