------------------------------------------
-- C/C++传递类（构造、析构）到lua，lua变量结束时调用
-- 纯lua语法
------------------------------------------

print("--------------------------- lua test st ----------------")

pack = CP.creatPacket()
CP.freePacket(pack)   --要主动调用函数销毁对象


print("--------------------------- lua test end ----------------")