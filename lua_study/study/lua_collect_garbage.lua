
pa = A.new();
pa.v = 31;
pa:show_value();

BindA(pa);

pa = nil;

collectgarbage();
