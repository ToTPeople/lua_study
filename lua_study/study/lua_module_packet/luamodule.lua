-- 文件名为 luamodule.lua
-- 定义一个名为 module_test 的模块
module_test = {}

-- 定义变量
module_test.var = 97;

-- 定义函数
module_test.func_p1 = function()
    print("This is a public func, name[func_p1]");
end

local func_p2 = function()
    print("This is a private func, name[func_p2]");
end

module_test.func_p3 = function()
    func_p2();
end

return module_test;
