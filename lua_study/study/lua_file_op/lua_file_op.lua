-----------------------
-- io file op
-- http://www.runoob.com/lua/lua-file-io.html
-----------------------

local name = "./study/lua_file_op/test_file";
local file, error = io.open(name, "r");

if not file then
    print(error);
end

io.input(file);

local line;

while (true)
do
    line = io.read();
    if (nil == line) then
        break;
    end

    print(line);

end

io.close(file);

-- write
file = io.open(name, "a");

io.output(file);

io.write("This is new add to file tail throud lua io op!!!\n");

io.close(file);

-----------------------
-- 完全模式 file op
-- http://www.runoob.com/lua/lua-file-io.html
-----------------------

-- read
file = io.open(name, "r");

while (true)
do
    line = file:read();
    if (nil == line) then
        break;
    end

    print(line);
end

file:close();

-- write
file = io.open(name, "a");

file:write("other lua file op add to file tail...\n");

file:close();

