#!/bin/bash
ssh -p 6000 root@www.liucheng68.top   "killall a.out"

GCC=/root/rk3328/sdk/prebuilts/gcc/linux-x86/aarch64/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc

$GCC main.c
scp -P 8002  a.out root@www.liucheng68.top:/root/
#ssh -p 6000 root@www.liucheng68.top   /root/a.out
