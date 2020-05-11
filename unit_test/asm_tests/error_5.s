.name "Batman"
.comment "This city needs me"
#illegal label reference

sti r1, %:yoink, %1
live %0
ld %0, r2
zjmp %-19
