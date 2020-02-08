.name "NEW"
.comment "TESTING"

live:
ld %123, r5
xor r5, r5, r13
live %1
zjmp %:live
