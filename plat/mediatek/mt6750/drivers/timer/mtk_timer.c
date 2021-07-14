/*
 * Copyright (c) 2021, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <drivers/delay_timer.h>
#include <lib/mmio.h>
#include <mt6750_def.h>
#include <mtk_timer.h>

#define GPT4_CTRL	(mtk_base_addr + 0x40)
#define GPT4_CLK	(mtk_base_addr + 0x44)
#define GPT4_COUNT	(mtk_base_addr + 0x48)

#define GPT_FREERUN	GENMASK(5, 4)
#define GPT_CLEAR 	BIT(1)
#define GPT_EN		BIT(0)

static uintptr_t mtk_base_addr;

uint32_t mtk_gpt_get_value(void)
{
	return ~mmio_read_32(GPT4_COUNT);
}

static const timer_ops_t mtk_gpt_ops = {
	.get_timer_value	= mtk_gpt_get_value,
	.clk_mult		= 1,
	.clk_div		= SYS_COUNTER_FREQ_IN_MHZ,
};

void mtk_gpt_ops_init(uintptr_t base_addr)
{
	assert(base_addr != 0);

	mtk_base_addr = base_addr;

	/* clear GPT */
	mmio_write_32(GPT4_CTRL, GPT_CLEAR);

	/* run from system clock */
	mmio_write_32(GPT4_CLK, 0);

	/* start GPT */
	mmio_write_32(GPT4_CTRL, GPT_FREERUN | GPT_EN);

	timer_init(&mtk_gpt_ops);
}
