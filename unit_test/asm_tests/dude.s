.name "The dude"



.comment "hey dude check hoe laat het is"



start:
live:
    live %1
    ld %57672192, r16
    st r16, 0
    fork %500
    sti r1, %:live, %1
    ld %0, r16
    zjmp %:live
