/*
 * Copyright 2016 Elnico, s.r.o.
 * Copyright 2013 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/iomux-vf610.h>
#include <asm/arch/ddrmc-vf610.h>
#include <asm/arch/crm_regs.h>
#include <asm/arch/clock.h>
#include <miiphy.h>
#include <netdev.h>

DECLARE_GLOBAL_DATA_PTR;

#define ENET_PAD_CTRL	(PAD_CTL_PUS_47K_UP | PAD_CTL_SPEED_HIGH | \
			PAD_CTL_DSE_50ohm | PAD_CTL_OBE_IBE_ENABLE)

#define DDR_PAD_CTRL		(PAD_CTL_DSE_20ohm)
#define DDR_PAD_CTRL_1		(PAD_CTL_DSE_20ohm | PAD_CTL_INPUT_DIFFERENTIAL)
#define DDR_RESET_PAD_CTRL	(PAD_CTL_DSE_150ohm | PAD_CTL_PUS_100K_UP | \
				PAD_CTL_INPUT_DIFFERENTIAL)

enum {
	PAD_DDR_RESETB			= IOMUX_PAD(0x021c, __NA_, 0, __NA_, 0, DDR_RESET_PAD_CTRL),
	PAD_DDR_A15__DDR_A_15		= IOMUX_PAD(0x0220, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_A14__DDR_A_14		= IOMUX_PAD(0x0224, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_A13__DDR_A_13		= IOMUX_PAD(0x0228, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_A12__DDR_A_12		= IOMUX_PAD(0x022c, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_A11__DDR_A_11		= IOMUX_PAD(0x0230, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_A10__DDR_A_10		= IOMUX_PAD(0x0234, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_A9__DDR_A_9		= IOMUX_PAD(0x0238, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_A8__DDR_A_8		= IOMUX_PAD(0x023c, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_A7__DDR_A_7		= IOMUX_PAD(0x0240, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_A6__DDR_A_6		= IOMUX_PAD(0x0244, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_A5__DDR_A_5		= IOMUX_PAD(0x0248, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_A4__DDR_A_4		= IOMUX_PAD(0x024c, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_A3__DDR_A_3		= IOMUX_PAD(0x0250, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_A2__DDR_A_2		= IOMUX_PAD(0x0254, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_A1__DDR_A_1		= IOMUX_PAD(0x0258, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_A0__DDR_A_0		= IOMUX_PAD(0x025c, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_BA2__DDR_BA_2		= IOMUX_PAD(0x0260, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_BA1__DDR_BA_1		= IOMUX_PAD(0x0264, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_BA0__DDR_BA_0		= IOMUX_PAD(0x0268, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_CAS__DDR_CAS_B		= IOMUX_PAD(0x026c, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_CKE__DDR_CKE_0		= IOMUX_PAD(0x0270, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_CLK__DDR_CLK_0		= IOMUX_PAD(0x0274, __NA_, 0, __NA_, 0, DDR_PAD_CTRL_1),
	PAD_DDR_CS__DDR_CS_B_0		= IOMUX_PAD(0x0278, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_D15__DDR_D_15		= IOMUX_PAD(0x027c, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_D14__DDR_D_14		= IOMUX_PAD(0x0280, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_D13__DDR_D_13		= IOMUX_PAD(0x0284, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_D12__DDR_D_12		= IOMUX_PAD(0x0288, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_D11__DDR_D_11		= IOMUX_PAD(0x028c, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_D10__DDR_D_10		= IOMUX_PAD(0x0290, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_D9__DDR_D_9		= IOMUX_PAD(0x0294, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_D8__DDR_D_8		= IOMUX_PAD(0x0298, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_D7__DDR_D_7		= IOMUX_PAD(0x029c, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_D6__DDR_D_6		= IOMUX_PAD(0x02a0, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_D5__DDR_D_5		= IOMUX_PAD(0x02a4, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_D4__DDR_D_4		= IOMUX_PAD(0x02a8, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_D3__DDR_D_3		= IOMUX_PAD(0x02ac, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_D2__DDR_D_2		= IOMUX_PAD(0x02b0, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_D1__DDR_D_1		= IOMUX_PAD(0x02b4, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_D0__DDR_D_0		= IOMUX_PAD(0x02b8, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_DQM1__DDR_DQM_1		= IOMUX_PAD(0x02bc, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_DQM0__DDR_DQM_0		= IOMUX_PAD(0x02c0, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_DQS1__DDR_DQS_1		= IOMUX_PAD(0x02c4, __NA_, 0, __NA_, 0, DDR_PAD_CTRL_1),
	PAD_DDR_DQS0__DDR_DQS_0		= IOMUX_PAD(0x02c8, __NA_, 0, __NA_, 0, DDR_PAD_CTRL_1),
	PAD_DDR_RAS__DDR_RAS_B		= IOMUX_PAD(0x02cc, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_WE__DDR_WE_B		= IOMUX_PAD(0x02d0, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_ODT1__DDR_ODT_0		= IOMUX_PAD(0x02d4, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_ODT0__DDR_ODT_1		= IOMUX_PAD(0x02d8, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_DDRBYTE1__DDR_DDRBYTE1	= IOMUX_PAD(0x02dc, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
	PAD_DDR_DDRBYTE0__DDR_DDRBYTE0	= IOMUX_PAD(0x02e0, __NA_, 0, __NA_, 0, DDR_PAD_CTRL),
};

static struct ddrmc_cr_setting sqm4vf6_cr_settings[] = {
	/* not in the datasheets, but in the original code */
	{ 0x00002000, 105 },
	{ 0x00000020, 110 },
	/* AXI */
	{ DDRMC_CR117_AXI0_W_PRI(1) | DDRMC_CR117_AXI0_R_PRI(1), 117 },
	{ DDRMC_CR118_AXI1_W_PRI(1) | DDRMC_CR118_AXI1_R_PRI(1), 118 },
	{ DDRMC_CR120_AXI0_PRI1_RPRI(2) |
		   DDRMC_CR120_AXI0_PRI0_RPRI(2), 120 },
	{ DDRMC_CR121_AXI0_PRI3_RPRI(2) |
		   DDRMC_CR121_AXI0_PRI2_RPRI(2), 121 },
	{ DDRMC_CR122_AXI1_PRI1_RPRI(1) | DDRMC_CR122_AXI1_PRI0_RPRI(1) |
		   DDRMC_CR122_AXI0_PRIRLX(100), 122 },
	{ DDRMC_CR123_AXI1_P_ODR_EN | DDRMC_CR123_AXI1_PRI3_RPRI(1) |
		   DDRMC_CR123_AXI1_PRI2_RPRI(1), 123 },
	{ DDRMC_CR124_AXI1_PRIRLX(100), 124 },
	{ DDRMC_CR126_PHY_RDLAT(11), 126 },
	{ DDRMC_CR132_WRLAT_ADJ(5) | DDRMC_CR132_RDLAT_ADJ(6), 132 },
	{ DDRMC_CR137_PHYCTL_DL(2), 137 },
	{ DDRMC_CR139_PHY_WRLV_RESPLAT(4) | DDRMC_CR139_PHY_WRLV_LOAD(7) |
		   DDRMC_CR139_PHY_WRLV_DLL(3) |
		   DDRMC_CR139_PHY_WRLV_EN(3), 139 },
	{ DDRMC_CR154_PAD_ZQ_EARLY_CMP_EN_TIMER(13) |
		   DDRMC_CR154_PAD_ZQ_MODE(1) |
		   DDRMC_CR154_DDR_SEL_PAD_CONTR(3) |
		   DDRMC_CR154_PAD_ZQ_HW_FOR(0), 154 },
	{ DDRMC_CR155_PAD_ODT_BYTE1(5) | DDRMC_CR155_PAD_ODT_BYTE0(5), 155 },
	{ DDRMC_CR158_TWR(6), 158 },
	{ DDRMC_CR161_ODT_EN(0) | DDRMC_CR161_TODTH_RD(0) |
		   DDRMC_CR161_TODTH_WR(6), 161 },
	/* end marker */
	{ 0, -1 }
};

/* PHY settings -- most of them differ from default in imx-regs.h */

#define SQM4VF6_DDRMC_PHY_DQ_TIMING			0x00002213
#define SQM4VF6_DDRMC_PHY_CTRL				0x00290000
#define SQM4VF6_DDRMC_PHY_SLAVE_CTRL			0x00002c00
#define SQM4VF6_DDRMC_PHY_PROC_PAD_ODT			0x00010020

static struct ddrmc_phy_setting sqm4vf6_phy_settings[] = {
	{ SQM4VF6_DDRMC_PHY_DQ_TIMING,  0 },
	{ SQM4VF6_DDRMC_PHY_DQ_TIMING, 16 },
	{ SQM4VF6_DDRMC_PHY_DQ_TIMING, 32 },
	{ SQM4VF6_DDRMC_PHY_DQ_TIMING, 48 },
	{ DDRMC_PHY_DQS_TIMING,  1 },
	{ DDRMC_PHY_DQS_TIMING, 17 },
	{ DDRMC_PHY_DQS_TIMING, 33 },
	{ DDRMC_PHY_DQS_TIMING, 49 },
	{ SQM4VF6_DDRMC_PHY_CTRL,  2 },
	{ SQM4VF6_DDRMC_PHY_CTRL, 18 },
	{ SQM4VF6_DDRMC_PHY_CTRL, 34 },
	{ DDRMC_PHY_MASTER_CTRL,  3 },
	{ DDRMC_PHY_MASTER_CTRL, 19 },
	{ DDRMC_PHY_MASTER_CTRL, 35 },
	{ SQM4VF6_DDRMC_PHY_SLAVE_CTRL,  4 },
	{ SQM4VF6_DDRMC_PHY_SLAVE_CTRL, 20 },
	{ SQM4VF6_DDRMC_PHY_SLAVE_CTRL, 36 },
	{ DDRMC_PHY50_DDR3_MODE | DDRMC_PHY50_EN_SW_HALF_CYCLE, 50 },
	{ SQM4VF6_DDRMC_PHY_PROC_PAD_ODT, 52 },

	/* end marker */
	{ 0, -1 }
};

int dram_init(void)
{
	static const struct ddr3_jedec_timings sqm4vf6_ddr_timings = {
		.tinit             = 5,
		.trst_pwron        = 80000,
		.cke_inactive      = 200000,
		.wrlat             = 5,
		.caslat_lin        = 12,
		.trc               = 6,
		.trrd              = 4,
		.tccd              = 4,
		.tbst_int_interval = 4,
		.tfaw              = 18,
		.trp               = 6,
		.twtr              = 4,
		.tras_min          = 15,
		.tmrd              = 4,
		.trtp              = 4,
		.tras_max          = 14040,
		.tmod              = 12,
		.tckesr            = 4,
		.tcke              = 3,
		.trcd_int          = 6,
		.tras_lockout      = 1,
		.tdal              = 10,
		.bstlen            = 3,
		.tdll              = 512,
		.trp_ab            = 6,
		.tref              = 1542,
		.trfc              = 64,
		.tref_int          = 5,
		.tpdex             = 3,
		.txpdll            = 10,
		.txsnr             = 68,
		.txsr              = 506,
		.cksrx             = 5,
		.cksre             = 5,
		.freq_chg_en       = 1,
		.zqcl              = 256,
		.zqinit            = 512,
		.zqcs              = 64,
		.ref_per_zq        = 64,
		.zqcs_rotate       = 1,
		.aprebit           = 10,
		.cmd_age_cnt       = 255,
		.age_cnt           = 255,
		.q_fullness        = 0,
		.odt_rd_mapcs0     = 1,
		.odt_wr_mapcs0     = 1,
		.wlmrd             = 40,
		.wldqsen           = 25,
	};

	static const iomux_v3_cfg_t sqm4vf6_pads[] = {
		PAD_DDR_A15__DDR_A_15,
		PAD_DDR_A14__DDR_A_14,
		PAD_DDR_A13__DDR_A_13,
		PAD_DDR_A12__DDR_A_12,
		PAD_DDR_A11__DDR_A_11,
		PAD_DDR_A10__DDR_A_10,
		PAD_DDR_A9__DDR_A_9,
		PAD_DDR_A8__DDR_A_8,
		PAD_DDR_A7__DDR_A_7,
		PAD_DDR_A6__DDR_A_6,
		PAD_DDR_A5__DDR_A_5,
		PAD_DDR_A4__DDR_A_4,
		PAD_DDR_A3__DDR_A_3,
		PAD_DDR_A2__DDR_A_2,
		PAD_DDR_A1__DDR_A_1,
		PAD_DDR_A0__DDR_A_0,
		PAD_DDR_BA2__DDR_BA_2,
		PAD_DDR_BA1__DDR_BA_1,
		PAD_DDR_BA0__DDR_BA_0,
		PAD_DDR_CAS__DDR_CAS_B,
		PAD_DDR_CKE__DDR_CKE_0,
		PAD_DDR_CLK__DDR_CLK_0,
		PAD_DDR_CS__DDR_CS_B_0,
		PAD_DDR_D15__DDR_D_15,
		PAD_DDR_D14__DDR_D_14,
		PAD_DDR_D13__DDR_D_13,
		PAD_DDR_D12__DDR_D_12,
		PAD_DDR_D11__DDR_D_11,
		PAD_DDR_D10__DDR_D_10,
		PAD_DDR_D9__DDR_D_9,
		PAD_DDR_D8__DDR_D_8,
		PAD_DDR_D7__DDR_D_7,
		PAD_DDR_D6__DDR_D_6,
		PAD_DDR_D5__DDR_D_5,
		PAD_DDR_D4__DDR_D_4,
		PAD_DDR_D3__DDR_D_3,
		PAD_DDR_D2__DDR_D_2,
		PAD_DDR_D1__DDR_D_1,
		PAD_DDR_D0__DDR_D_0,
		PAD_DDR_DQM1__DDR_DQM_1,
		PAD_DDR_DQM0__DDR_DQM_0,
		PAD_DDR_DQS1__DDR_DQS_1,
		PAD_DDR_DQS0__DDR_DQS_0,
		PAD_DDR_RAS__DDR_RAS_B,
		PAD_DDR_WE__DDR_WE_B,
		PAD_DDR_ODT1__DDR_ODT_0,
		PAD_DDR_ODT0__DDR_ODT_1,
		PAD_DDR_DDRBYTE1__DDR_DDRBYTE1,
		PAD_DDR_DDRBYTE0__DDR_DDRBYTE0,
		PAD_DDR_RESETB,
	};

	imx_iomux_v3_setup_multiple_pads(sqm4vf6_pads, ARRAY_SIZE(sqm4vf6_pads));

	ddrmc_ctrl_init_ddr3(&sqm4vf6_ddr_timings, sqm4vf6_cr_settings,
			     sqm4vf6_phy_settings, 1, 2);

	gd->ram_size = get_ram_size((void *)PHYS_SDRAM, PHYS_SDRAM_SIZE);

	return 0;
}

void setup_iomux_enet(void)
{
	static const iomux_v3_cfg_t enet0_pads[] = {
		NEW_PAD_CTRL(VF610_PAD_PTA6__RMII0_CLKIN, ENET_PAD_CTRL),
		NEW_PAD_CTRL(VF610_PAD_PTC1__RMII0_MDIO, ENET_PAD_CTRL),
		NEW_PAD_CTRL(VF610_PAD_PTC0__RMII0_MDC, ENET_PAD_CTRL),
		NEW_PAD_CTRL(VF610_PAD_PTC2__RMII0_CRS_DV, ENET_PAD_CTRL),
		NEW_PAD_CTRL(VF610_PAD_PTC3__RMII0_RD1, ENET_PAD_CTRL),
		NEW_PAD_CTRL(VF610_PAD_PTC4__RMII0_RD0, ENET_PAD_CTRL),
		NEW_PAD_CTRL(VF610_PAD_PTC5__RMII0_RXER, ENET_PAD_CTRL),
		NEW_PAD_CTRL(VF610_PAD_PTC6__RMII0_TD1, ENET_PAD_CTRL),
		NEW_PAD_CTRL(VF610_PAD_PTC7__RMII0_TD0, ENET_PAD_CTRL),
		NEW_PAD_CTRL(VF610_PAD_PTC8__RMII0_TXEN, ENET_PAD_CTRL),
	};

	imx_iomux_v3_setup_multiple_pads(enet0_pads, ARRAY_SIZE(enet0_pads));
}

#ifdef CONFIG_NAND_VF610_NFC
void setup_iomux_nfc(void)
{
	static const iomux_v3_cfg_t nfc_pads[] = {
		VF610_PAD_PTD23__NF_IO7,
		VF610_PAD_PTD22__NF_IO6,
		VF610_PAD_PTD21__NF_IO5,
		VF610_PAD_PTD20__NF_IO4,
		VF610_PAD_PTD19__NF_IO3,
		VF610_PAD_PTD18__NF_IO2,
		VF610_PAD_PTD17__NF_IO1,
		VF610_PAD_PTD16__NF_IO0,
		VF610_PAD_PTB24__NF_WE_B,
		VF610_PAD_PTB25__NF_CE0_B,
		VF610_PAD_PTB27__NF_RE_B,
		VF610_PAD_PTC26__NF_RB_B,
		VF610_PAD_PTC27__NF_ALE,
		VF610_PAD_PTC28__NF_CLE
	};

	imx_iomux_v3_setup_multiple_pads(nfc_pads, ARRAY_SIZE(nfc_pads));
}
#endif