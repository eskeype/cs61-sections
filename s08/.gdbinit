init-if-undefined $loaded = 0
if $loaded == 0
    set $loaded = 1
    set arch i386:x86-64
    file obj/kernel.full
    add-symbol-file obj/bootsector-gdb.full 0x7c00
    add-symbol-file obj/p-quotes.full 0x100000
    target remote localhost:1234
    source build/functions.gdb
    display/5i $pc

    # Your initialization commands here (if you want)
end

define bootc
    set *((int*) 0x10000) = 61
end
