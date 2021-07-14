/*
 * Copyright (c) 2021, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLAT_PRIVATE_H
#define PLAT_PRIVATE_H

/*******************************************************************************
 * Platform binary types for linking
 ******************************************************************************/
#define PLATFORM_LINKER_FORMAT "elf64-littleaarch64"
#define PLATFORM_LINKER_ARCH aarch64

#define FIRMWARE_WELCOME_STR "Booting Trusted Firmware\n"
#define PLAT_MAX_PWR_LVL U(2) /* MPIDR_AFFLVL2 */

#define PLAT_MAX_RET_STATE U(1)
#define PLAT_MAX_OFF_STATE U(2)

#define PLATFORM_CLUSTER0_CORE_COUNT U(4)
#define PLATFORM_CLUSTER1_CORE_COUNT U(4)
#define PLATFORM_CORE_COUNT (PLATFORM_CLUSTER1_CORE_COUNT + PLATFORM_CLUSTER0_CORE_COUNT)

#define CACHE_WRITEBACK_SHIFT 6
#define CACHE_WRITEBACK_GRANULE (1 << CACHE_WRITEBACK_SHIFT)

#define MAX_IO_DEVICES 1
#define MAX_IO_BLOCK_DEVICES 1
#define MAX_IO_HANDLES 1

#define PLATFORM_STACK_SIZE 0x400

#define BL2_BASE 0x00201000
#define BL2_LIMIT (BL2_BASE + 0x10000)

#endif /* PLAT_PRIVATE_H */
