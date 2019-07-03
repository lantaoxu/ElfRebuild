/* 
 * File:   EncRodataShellcode.h
 * Author: Angeltoms
 *
 */

#ifndef ENCRODATASHELLCODE_H
#define	ENCRODATASHELLCODE_H

#include "../ExElf.h"
#include "../QupLog.h"

#ifdef	__cplusplus
extern "C" {
#endif

    //#ifdef __LP64__
    //#else
    //#ifdef __x86__
    //#endif
    //
    //#endif
    //#ifdef __arm__
#ifdef DEBUG_TEST
    char enc_rodata_shellcode [] = {
        0xE0, 0x47, 0x2D, 0xE9,
        /////////////NOP///////
        0x00, 0xF0, 0x20, 0xE3,
        0x00, 0xF0, 0x20, 0xE3,
        0x00, 0xF0, 0x20, 0xE3,
        0x00, 0xF0, 0x20, 0xE3,
        0x00, 0xF0, 0x20, 0xE3,
        0x00, 0xF0, 0x20, 0xE3,
        0x00, 0xF0, 0x20, 0xE3,
        0x00, 0xF0, 0x20, 0xE3,
        0x00, 0xF0, 0x20, 0xE3,
        0x00, 0xF0, 0x20, 0xE3,
        0x00, 0xF0, 0x20, 0xE3,
        0x00, 0xF0, 0x20, 0xE3,
        0x00, 0xF0, 0x20, 0xE3,
        0x00, 0xF0, 0x20, 0xE3,
        0x00, 0xF0, 0x20, 0xE3,
        0x00, 0xF0, 0x20, 0xE3,
        0x00, 0xF0, 0x20, 0xE3,
        0x00, 0xF0, 0x20, 0xE3,
        0x00, 0xF0, 0x20, 0xE3,
        //////////////NOP///////
        0xE0, 0x87, 0xBD, 0xE8,
    };
#else

    //不带flush cache的解密rodata 节，异或解密，异或因子0x12
    //1 push {lr, r5, r6, r7, r8 , r9, r10}
    //2 sub r10, pc , #12   @ fp addr
    //3 ldr r9, [pc ,#0x58] @ shellcodeaddr
    //4 sub r10, r10 , r9   @ base = fp - shellcodeaddr
    //5 ldr r9, [pc, #0x54] @ rodataaddr
    //6 ldr r8, [pc, #0x54] @ rodatalen
    //7 ldr r7, [pc, #0x44] @ __ARM_NR_cacheflush
    //8 add r9, r9, r10     @ roddataaddr = base + vaddr
    //9 mov r0, r9          @ rodata addr
    //10 mov r1, r0          @ p = rodataaddr
    //11 mov r2, r8          @ len
    //12 mov r3, #0          @ i
    //13 mov r6, #0          @ tmp
    //14 ldrb r6 , [r0, +r3] @ tmp = rodata + i
    //15 eor r5, r6, #0x12   @ xor tmp
    //16 strb r5, [r1, +r3]  @ p = rodataaddr + i = tmp
    //17 add r3, r3, #1      @ i++
    //18 cmp r3 , r2         @ compare i , rodatalen
    //19 blt F8FFFFFF        @ blx -8
    //20 nop          
    //21 nop     
    //22 nop       
    //23 nop
    //24 nop
    //25 pop {r10, r9, r8, r7, r6, r5, pc}
    //data
    //26 @__ARM_NR_cacheflush
    //add tail
    //27 @shellcodeaddr
    //28 @rodataaddr
    //29 @rodatalen
//    char enc_rodata_shellcode [] = {
//        0xE0, 0x47, 0x2D, 0xE9,
//        0x0C, 0xA0, 0x4F, 0xE2,
//        0x58, 0x90, 0x9F, 0xE5,
//        0x09, 0xA0, 0x4A, 0xE0,
//        0x54, 0x90, 0x9F, 0xE5,
//        0x54, 0x80, 0x9F, 0xE5,
//        0x44, 0x70, 0x9F, 0xE5,
//        0x0A, 0x90, 0x89, 0xE0,
//        0x09, 0x00, 0xA0, 0xE1,
//        0x00, 0x10, 0xA0, 0xE1,
//        0x08, 0x20, 0xA0, 0xE1,
//        0x00, 0x30, 0xA0, 0xE3,
//        0x00, 0x60, 0xA0, 0xE3,
//        0x03, 0x60, 0xD0, 0xE7,
//        0x12, 0x50, 0x26, 0xE2,
//        0x03, 0x50, 0xC1, 0xE7,
//        0x01, 0x30, 0x83, 0xE2,
//        0x02, 0x00, 0x53, 0xE1,
//        0xF8, 0xFF, 0xFF, 0xBA,
//        /////nop
//        0x00, 0xF0, 0x20, 0xE3,
//        0x00, 0xF0, 0x20, 0xE3,
//        0x00, 0xF0, 0x20, 0xE3,
//        0x00, 0xF0, 0x20, 0xE3,
//        0x00, 0xF0, 0x20, 0xE3,
//        /////nop
//        0xE0, 0x87, 0xBD, 0xE8,
//        0x02, 0x00, 0x0f, 0x00, //__ARM_NR_cacheflush
//    };

    //带flush cache的解密rodata 节，异或解密，异或因子0x12
    //1 push {lr, r5, r6, r7, r8 , r9, r10}
    //2 sub r10, pc , #12   @ fp addr
    //3 ldr r9, [pc ,#0x58] @ shellcodeaddr
    //4 sub r10, r10 , r9   @ base = fp - shellcodeaddr
    //5 ldr r9, [pc, #0x54] @ rodataaddr
    //6 ldr r8, [pc, #0x54] @ rodatalen
    //7 ldr r7, [pc, #0x44] @ __ARM_NR_cacheflush
    //8 add r9, r9, r10     @ roddataaddr = base + vaddr
    //9 mov r0, r9          @ rodata addr
    //10 mov r1, r0          @ p = rodataaddr
    //11 mov r2, r8          @ len
    //12 mov r3, #0          @ i
    //13 mov r6, #0          @ tmp
    //14 ldrb r6 , [r0, +r3] @ tmp = rodata + i
    //15 eor r5, r6, #0x12   @ xor tmp
    //16 strb r5, [r1, +r3]  @ p = rodataaddr + i = tmp
    //17 add r3, r3, #1      @ i++
    //18 cmp r3 , r2         @ compare i , rodatalen
    //19 blt F8FFFFFF        @ blx -8
    //20 mov r0, r9          @ clear cache, begin
    //21 add r10, r9, r8     @ end = begin + len
    //22 mov r1 , r10        @ r1 = end
    //23 mov r2 , #0x0
    //24 svc 0x00000000
    //25 pop {r10, r9, r8, r7, r6, r5, pc}
    //data
    //26 @__ARM_NR_cacheflush
    //add tail
    //27 @shellcodeaddr
    //28 @rodataaddr
    //29 @rodatalen
    char enc_rodata_shellcode [] = {
        0xE0, 0x47, 0x2D, 0xE9,
        0x0C, 0xA0, 0x4F, 0xE2,
        0x58, 0x90, 0x9F, 0xE5,
        0x09, 0xA0, 0x4A, 0xE0,
        0x54, 0x90, 0x9F, 0xE5,
        0x54, 0x80, 0x9F, 0xE5,
        0x44, 0x70, 0x9F, 0xE5,
        0x0A, 0x90, 0x89, 0xE0,
        0x09, 0x00, 0xA0, 0xE1,
        0x00, 0x10, 0xA0, 0xE1,
        0x08, 0x20, 0xA0, 0xE1,
        0x00, 0x30, 0xA0, 0xE3,
        0x00, 0x60, 0xA0, 0xE3,
        0x03, 0x60, 0xD0, 0xE7,
        0x12, 0x50, 0x26, 0xE2,
        0x03, 0x50, 0xC1, 0xE7,
        0x01, 0x30, 0x83, 0xE2,
        0x02, 0x00, 0x53, 0xE1,
        0xF8, 0xFF, 0xFF, 0xBA,
        /////clear cache
        0x09, 0x00, 0xA0, 0xE1,
        0x08, 0xA0, 0x89, 0xE0,
        0x0A, 0x10, 0xA0, 0xE1,
        0x00, 0x20, 0xA0, 0xE3,
        0x00, 0x00, 0x00, 0xEF,
        /////clear cache
        0xE0, 0x87, 0xBD, 0xE8,
        0x02, 0x00, 0x0f, 0x00, //__ARM_NR_cacheflush
    };

#endif
    //#endif

    __inline__ int scrodataSZ() {
        int sz = sizeof (enc_rodata_shellcode);
        QUP_LOGI("[+] shell code size = %d", sz);
        return sz;
    }



#ifdef	__cplusplus
}
#endif

#endif	/* ENCRODATASHELLCODE_H */
