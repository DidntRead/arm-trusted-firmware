/*
 * Copyright (c) 2021, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <mtk_console.h>
#include <mt6750_def.h>

static console_t console;

void bl2_el3_plat_arch_setup(void)
{
	/* Stub */
}

void bl2_el3_early_platform_setup(u_register_t arg1, u_register_t arg2,
				  u_register_t arg3, u_register_t arg4)
{
	/* Initialize the console to provide early debug support */
	console_mtk_register(UART0_BASE, UART_CLOCK,
			       UART_BAUDRATE, &console);

	console_set_scope(&console, CONSOLE_FLAG_BOOT |
				CONSOLE_FLAG_RUNTIME | CONSOLE_FLAG_CRASH);
}

void bl2_platform_setup(void)
{
	/* Stub */
}
