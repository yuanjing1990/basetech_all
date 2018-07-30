#!/bin/bash
PROJECT_ROOT=Goni
${PROJECT_ROOT}/out/host/linux-x86/bin/emulator-arm -kernel ${PROJECT_ROOT}/prebuilts/qemu-kernel/arm/kernel-qemu-armv7 -system ${PROJECT_ROOT}/out/target/product/generic/system.img -ramdisk ${PROJECT_ROOT}/out/target/product/generic/ramdisk.img -nocache -show-kernel -shell


