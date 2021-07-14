/*
 * Copyright (c) 2021, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MT6750_DEF_H
#define MT6750_DEF_H

/* IO Base */
#define IO_BASE			0x10000000

/* UART */
#define UART0_BASE		(IO_BASE + 0x1002000)
#define UART1_BASE		(IO_BASE + 0x1003000)
#define UART2_BASE		(IO_BASE + 0x1004000)
#define UART3_BASE		(IO_BASE + 0x1005000)

#define UART_BAUDRATE   	921600
#define UART_CLOCK 		26000000

/* Crash console */
#define CRASH_CONSOLE_BASE 	UART0_BASE
#define CRASH_CONSOLE_CLOCK 	UART_CLOCK
#define CRASH_CONSOLE_BAUDRATE 	UART_BAUDRATE

/* Timer */
#define SYS_COUNTER_FREQ_IN_TICKS 	13000000
#define SYS_COUNTER_FREQ_IN_MHZ		(SYS_COUNTER_FREQ_IN_TICKS/1000000)

#endif /* MT6750_DEF_H */
