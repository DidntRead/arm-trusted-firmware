#
# Copyright (c) 2021, ARM Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

MTK_PLAT		:=	plat/mediatek
MTK_PLAT_SOC		:=	${MTK_PLAT}/${PLAT}
MTK_DRIVERS_SOC		:=	${MTK_PLAT_SOC}/drivers

PLAT_INCLUDES		:=	-I${MTK_PLAT_SOC}/include/			\
				-I${MTK_DRIVERS_SOC}/console			\
				-I${MTK_DRIVERS_SOC}/timer			\
				-I${MTK_DRIVERS_SOC}/pll

PLAT_BL_COMMON_SOURCES	+=	drivers/io/io_storage.c				\
				drivers/delay_timer/delay_timer.c		\
				${MTK_PLAT_SOC}/aarch64/mt6750_helpers.S	\
				${MTK_DRIVERS_SOC}/console/mtk_console.S 	\
				${MTK_DRIVERS_SOC}/timer/mtk_timer.c		\
				${MTK_DRIVERS_SOC}/pll/mtk_pll.c		\
				${MTK_PLAT_SOC}/mt6750_io_storage.c		\
				${MT6750_GIC_SOURCES}

BL2_SOURCES		+=	common/desc_image_load.c			\
				lib/cpus/aarch64/cortex_a53.S			\
				${MTK_PLAT_SOC}/mt6750_bl2_el3_setup.c		\
				${MTK_PLAT_SOC}/mt6750_mem_params_desc.c	\
				${MTK_PLAT_SOC}/mt6750_image_load.c

# indicate the reset vector address can be programmed
PROGRAMMABLE_RESET_ADDRESS	:=	1

# only primary cpu reaches bl2
COLD_BOOT_SINGLE_CPU := 1

# BL2 at EL3
BL2_AT_EL3 := 1
