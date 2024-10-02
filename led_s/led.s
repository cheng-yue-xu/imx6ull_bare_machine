.global _start   @全局标号

_start:
    @enable clk
    ldr r0,=0x020c4068
    ldr r1,=0xffffffff
    str r1,[r0]
    str r1,[r0,#4]
    str r1,[r0,#8]
    str r1,[r0,#12]
    str r1,[r0,#16]
    str r1,[r0,#20]

    @iomux config
    ldr r0,=0x020e0068
    ldr r1,=0x5
    str r1,[r0]

    @io gpio1_io3 config
    ldr r0,=0x020e02f4
    ldr r1,=0x10b0
    str r1,[r0]

    @gpio config
    ldr r0,=0x209c004
    ldr r1,=0x8
    str r1,[r0]

    @led control
    ldr r0,=0x0209c000
    ldr r1,=0
    str r1,[r0]

loop:
    b loop
    


