/*
 * Copyright (c) 2021, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <lib/mmio.h>
#include <drivers/delay_timer.h>
#include <mtk_pll.h>
#include <mtk_pll_reg.h>

void mt_pll_early_init(void)
{
	unsigned int temp;

	mmio_write_32(ACLKEN_DIV, AXI_DIV2);

	/* reduce clksrc disable delay */
	mmio_write_32(CLKSQ_STB_CON0, 0x05010501);

	/* set PWR & ISO control delay to 1us */
	mmio_write_32(PLL_ISO_CON0, 0x00080008);

	mmio_write_32(AP_PLL_CON6, 0x00000000);

	/* power on root PLLs */
	temp = mmio_read_32(ARMCA15PLL_PWR_CON0);
	mmio_write_32(ARMCA15PLL_PWR_CON0, temp | PLL_PWR);
	temp = mmio_read_32(ARMCA7PLL_PWR_CON0);
	mmio_write_32(ARMCA7PLL_PWR_CON0, temp | PLL_PWR);
	temp = mmio_read_32(MAINPLL_PWR_CON0);
	mmio_write_32(MAINPLL_PWR_CON0, temp | PLL_PWR);
	temp = mmio_read_32(UNIVPLL_PWR_CON0);
	mmio_write_32(UNIVPLL_PWR_CON0, temp | PLL_PWR);
	temp = mmio_read_32(MMPLL_PWR_CON0);
	mmio_write_32(MMPLL_PWR_CON0, temp | PLL_PWR);
	temp = mmio_read_32(MSDCPLL_PWR_CON0);
	mmio_write_32(MSDCPLL_PWR_CON0, temp | PLL_PWR);
	temp = mmio_read_32(VENCPLL_PWR_CON0);
	mmio_write_32(VENCPLL_PWR_CON0, temp | PLL_PWR);
	temp = mmio_read_32(TVDPLL_PWR_CON0);
	mmio_write_32(TVDPLL_PWR_CON0, temp | PLL_PWR);
	temp = mmio_read_32(VCODECPLL_PWR_CON0);
	mmio_write_32(VCODECPLL_PWR_CON0, temp | PLL_PWR);
	temp = mmio_read_32(APLL1_PWR_CON0);
	mmio_write_32(APLL1_PWR_CON0, temp | PLL_PWR);
	temp = mmio_read_32(APLL2_PWR_CON0);
	mmio_write_32(APLL2_PWR_CON0, temp | PLL_PWR);

	udelay(5);

	/* disable root PLLs' ISO */
	temp = mmio_read_32(ARMCA15PLL_PWR_CON0);
	mmio_write_32(ARMCA15PLL_PWR_CON0, temp & ~PLL_ISO_MASK);
	temp = mmio_read_32(ARMCA7PLL_PWR_CON0);
	mmio_write_32(ARMCA7PLL_PWR_CON0, temp & ~PLL_ISO_MASK);
	temp = mmio_read_32(MAINPLL_PWR_CON0);
	mmio_write_32(MAINPLL_PWR_CON0, temp & ~PLL_ISO_MASK);
	temp = mmio_read_32(UNIVPLL_PWR_CON0);
	mmio_write_32(UNIVPLL_PWR_CON0, temp & ~PLL_ISO_MASK);
	temp = mmio_read_32(MMPLL_PWR_CON0);
	mmio_write_32(MMPLL_PWR_CON0, temp & ~PLL_ISO_MASK);
	temp = mmio_read_32(MSDCPLL_PWR_CON0);
	mmio_write_32(MSDCPLL_PWR_CON0, temp & ~PLL_ISO_MASK);
	temp = mmio_read_32(VENCPLL_PWR_CON0);
	mmio_write_32(VENCPLL_PWR_CON0, temp & ~PLL_ISO_MASK);
	temp = mmio_read_32(TVDPLL_PWR_CON0);
	mmio_write_32(TVDPLL_PWR_CON0, temp & ~PLL_ISO_MASK);
	temp = mmio_read_32(APLL1_PWR_CON0);
	mmio_write_32(APLL1_PWR_CON0, temp & ~PLL_ISO_MASK);
	temp = mmio_read_32(APLL2_PWR_CON0);
	mmio_write_32(APLL2_PWR_CON0, temp & ~PLL_ISO_MASK);

	/* set PLLs' frequency */
	mmio_write_32(ARMCA15PLL_CON1, ARMCA15PLL_FDBK_DIV | ARMCA15PLL_POSTDIV2 | PLL_FDBK_DIV_UP);
	mmio_write_32(ARMCA7PLL_CON1, ARMCA7PLL_FDBK_DIV | ARMCA7PLL_POSTDIV2 | PLL_FDBK_DIV_UP);
	mmio_write_32(MAINPLL_CON1, MAINPLL_FDBK_DIV | PLL_FDBK_DIV_UP);
	mmio_write_32(MMPLL_CON1, MMPLL_FDBK_DIV | MMPLL_POSTDIV4 | PLL_FDBK_DIV_UP);
	mmio_write_32(MSDCPLL_CON1, MSDCPLL_FDBK_DIV | PLL_FDBK_DIV_UP);
	mmio_write_32(VENCPLL_CON1, VENCPLL_FDBK_DIV | PLL_FDBK_DIV_UP);
	mmio_write_32(VENCPLL_CON0, VENCPLL_POSTDIV4);
	mmio_write_32(TVDPLL_CON1, TVDPLL_FDBK_DIV | PLL_FDBK_DIV_UP);

	/* enable root PLLs */
	temp = mmio_read_32(ARMCA15PLL_CON0);
	mmio_write_32(ARMCA15PLL_CON0, temp | PLL_EN);
	temp = mmio_read_32(ARMCA7PLL_CON0);
	mmio_write_32(ARMCA7PLL_CON0, temp | PLL_EN);
	temp = mmio_read_32(MAINPLL_CON0);
	mmio_write_32(MAINPLL_CON0, temp | PLL_EN);
	temp = mmio_read_32(UNIVPLL_CON0);
	mmio_write_32(UNIVPLL_CON0, temp | PLL_EN);
	temp = mmio_read_32(MMPLL_CON0);
	mmio_write_32(MMPLL_CON0, temp | PLL_EN);
	temp = mmio_read_32(MSDCPLL_CON0);
	mmio_write_32(MSDCPLL_CON0, temp | PLL_EN);
	temp = mmio_read_32(VENCPLL_CON0);
	mmio_write_32(VENCPLL_CON0, temp | PLL_EN);
	temp = mmio_read_32(TVDPLL_CON0);
	mmio_write_32(TVDPLL_CON0, temp | PLL_EN);
	temp = mmio_read_32(APLL1_CON0);
	mmio_write_32(APLL1_CON0, temp | PLL_EN);
	temp = mmio_read_32(APLL2_CON0);
	mmio_write_32(APLL2_CON0, temp | PLL_EN);

	udelay(40);

	temp = mmio_read_32(ARMCA7PLL_CON0);
	mmio_write_32(ARMCA7PLL_CON0, temp | PLL_DIV_RST_BAR);
	temp = mmio_read_32(MAINPLL_CON0);
	mmio_write_32(MAINPLL_CON0, temp | PLL_DIV_RST_BAR);
	temp = mmio_read_32(UNIVPLL_CON0);
	mmio_write_32(UNIVPLL_CON0, temp | PLL_DIV_RST_BAR);

	/* enable bus dcm */
	temp = mmio_read_32(TOP_DCMCTL);
	mmio_write_32(TOP_DCMCTL, temp | INFRA_BUS_DCM_EN);

	/* setup armpll divider */
	temp = mmio_read_32(TOP_CKDIV1_BIG) ;
	mmio_write_32(TOP_CKDIV1_BIG, temp & ARMBPLL_CLK_DIV_MASK);
	temp = mmio_read_32(TOP_CKDIV1_SML);
	mmio_write_32(TOP_CKDIV1_SML, temp & ARMSPLL_CLK_DIV_MASK);

	/* setup cci divider */
	temp = mmio_read_32(TOP_CKDIV1_BUS);
	mmio_write_32(TOP_CKDIV1_BUS, temp & ((temp & CCI_CLK_DIV_MASK) | CCI_CLK_DIV2));

	/* setup clkmux */
	temp = mmio_read_32(TOP_CKMUXSEL);
	mmio_write_32(TOP_CKMUXSEL, temp | (ARMCA7PLL_MUX_ARMPLL | ARMCA15PLL_MUX_ARMPLL | BIG_ARMPLL_MUX_ARMBPLL | SML_ARMPLL_MUX_ARMSPLL | CCI_MUX_ARMBPLL));

	/* enable spm dcm */
	mmio_write_32(INFRA_BUS_DCM_CTRL, mmio_read_32(INFRA_BUS_DCM_CTRL) | SPM_DCM_EN);

	/* setup TCK mux */
	mmio_write_32(CLK_CFG_0, 0x02002201);
	mmio_write_32(CLK_CFG_1, 0x01000300);
	mmio_write_32(CLK_CFG_2, 0x00010001);
	mmio_write_32(CLK_CFG_3, 0x07010100);
	mmio_write_32(CLK_CFG_4, 0x01000107);
	mmio_write_32(CLK_CFG_5, 0x01020000);
	mmio_write_32(CLK_CFG_6, 0x01010102);
	mmio_write_32(CLK_CFG_7, 0x01000101);
	mmio_write_32(CLK_CFG_8, 0x01010201);

	/* apply TCK mux config */
	mmio_write_32(CLK_CFG_UPDATE, 0xffffffff);
	mmio_write_32(CLK_CFG_UPDATE1, 0x00000007);

	/* enable scp clock off control */
	mmio_write_32(CLK_SCP_CFG_0, 0x703FF);
	mmio_write_32(CLK_SCP_CFG_1, 0x7);

	/* ungate all */
	mmio_write_32(INFRA_PDN_CLR0, 0xFFFFFFFF);
	mmio_write_32(INFRA_PDN_CLR1, 0xFFFFFFFF);
	mmio_write_32(INFRA_PDN_CLR2, 0xFFFFFFFF);
}

void mt_pll_late_init(void)
{
	unsigned int temp;

	temp = mmio_read_32(AP_PLL_CON3);
	mmio_write_32(AP_PLL_CON3, temp & 0xFFFCCCCC);
	temp = mmio_read_32(AP_PLL_CON4);
	mmio_write_32(AP_PLL_CON4, temp & 0xFFFFFCFC);
}
