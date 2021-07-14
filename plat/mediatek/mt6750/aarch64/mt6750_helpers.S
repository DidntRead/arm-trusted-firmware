/*
 * Copyright (c) 2021, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <asm_macros.S>
#include <mt6750_def.h>

	.globl	platform_mem_init
	.globl	plat_is_my_cpu_primary
	.globl	plat_my_core_pos
	.globl	plat_crash_console_init
	.globl	plat_crash_console_putc
	.globl	plat_crash_console_flush

	/* -----------------------------------------------------
	 * void platform_mem_init(void);
	 *
	 * We don't need to carry out any memory initialization
	 * -----------------------------------------------------
	 */
func platform_mem_init
	ret
endfunc platform_mem_init

func plat_is_my_cpu_primary
	mrs x0, mpidr_el1
	and x0, x0, #(MPIDR_CLUSTER_MASK | MPIDR_CPU_MASK)
	cmp x0, #0
	cset x0, eq
	ret
endfunc plat_is_my_cpu_primary

	/* -----------------------------------------------------
	 *  unsigned int plat_my_core_pos(void)
	 *  This function uses the plat_mediatek_calc_core_pos()
	 *  definition to get the index of the calling CPU.
	 * -----------------------------------------------------
	 */
	/* -----------------------------------------------------
	 * unsigned int plat_my_core_pos(void);
	 *
	 * result: CorePos = CoreId + (ClusterId << 2)
	 * -----------------------------------------------------
	 */
func plat_my_core_pos
	mrs     x0, mpidr_el1
	and     x1, x0, #MPIDR_CPU_MASK
	and     x0, x0, #MPIDR_CLUSTER_MASK
	add     x0, x1, x0, LSR #6
	ret
endfunc plat_my_core_pos

	/* ---------------------------------------------
	 * int plat_crash_console_init(void)
	 * Function to initialize the crash console
	 * without a C Runtime to print crash report.
	 * Clobber list : x0, x1, x2
	 * ---------------------------------------------
	 */
func plat_crash_console_init
	mov_imm	x0, CRASH_CONSOLE_BASE
	mov_imm	x1, CRASH_CONSOLE_CLOCK
	mov_imm	x2, CRASH_CONSOLE_BAUDRATE
	b	console_mtk_core_init
endfunc plat_crash_console_init

	/* ---------------------------------------------
	 * int plat_crash_console_putc(int c)
	 * Function to print a character on the crash
	 * console without a C Runtime.
	 * Clobber list : x1, x2
	 * ---------------------------------------------
	 */
func plat_crash_console_putc
	mov_imm	x1, CRASH_CONSOLE_BASE
	b	console_mtk_core_putc
endfunc plat_crash_console_putc

	/* ---------------------------------------------
	 * void plat_crash_console_flush()
	 * Function to force a write of all buffered
	 * data that hasn't been output.
	 * Out : void.
	 * Clobber list : x0, x1
	 * ---------------------------------------------
	 */
func plat_crash_console_flush
	mov_imm	x0, CRASH_CONSOLE_BASE
	b	console_mtk_core_flush
endfunc plat_crash_console_flush
