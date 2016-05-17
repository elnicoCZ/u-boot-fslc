/*
 * Copyright 2016 Elnico, s.r.o.
 *
 * Configuration settings for the Elnico SQM4-VF6 SOM.
 *
 * Based on vf610twr.h:
 * Copyright 2013 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <asm/arch/imx-regs.h>

#define CONFIG_VF610
#define CONFIG_SQM4VF6_BOARD_NAME	"EasyBoard"

#define CONFIG_ARCH_MISC_INIT
#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO
#define CONFIG_SYS_FSL_CLK
#define CONFIG_SYS_THUMB_BUILD
#define CONFIG_SYS_DCACHE_OFF                   /* crucial for MQX to start directly from u-boot! */
#define CONFIG_SYS_CACHELINE_SIZE	64

#define CONFIG_SKIP_LOWLEVEL_INIT

#define CONFIG_CMD_FUSE
#ifdef CONFIG_CMD_FUSE
#define CONFIG_MXC_OCOTP
#endif

#define CONFIG_CMDLINE_TAG                      /* enable passing of ATAGs - required for old good uImage's */

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 2 * 1024 * 1024)

#define CONFIG_BOARD_EARLY_INIT_F

#define CONFIG_FSL_LPUART
#define LPUART_BASE			UART1_BASE

/* Allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG
#define CONFIG_VERSION_VARIABLE
#define CONFIG_SYS_UART_PORT		(1)
#define CONFIG_BAUDRATE			115200
#define CONFIG_CMD_ASKENV

/* NAND support */
#define CONFIG_CMD_NAND
#ifdef CONFIG_CMD_NAND

#define CONFIG_USE_ARCH_MEMCPY
#define CONFIG_USE_ARCH_MEMSET

#define CONFIG_SYS_NAND_ONFI_DETECTION
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		NFC_BASE_ADDR
#define CONFIG_VF610_NFC_SKIP_CHIPSELECT	/* required to make NAND working in Linux! */

#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#define CONFIG_MTD_UBI_FASTMAP
#define CONFIG_RBTREE
#define CONFIG_LZO
#define CONFIG_CMD_FS_GENERIC

#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_PARTITIONS
#define CONFIG_MTD_DEVICE
#define MTDIDS_DEFAULT			"nand0=fsl_nfc"
#define MTDPARTS_DEFAULT		"mtdparts=fsl_nfc:"		\
					"128k(mtd_bcb)ro,"		\
					"1408k(mtd_uboot)ro,"		\
					"512k(mtd_uboot_env),"		\
					"5m(mtd_m4),"			\
					"5m(mtd_kernel),"		\
					"512k(mtd_fdt),"		\
					"5m(mtd_epd),"			\
					"-(mtd_rootfs)"
#else /* !CONFIG_CMD_NAND */
#define MTDIDS_DEFAULT			""
#define MTDPARTS_DEFAULT		""
#endif /* !CONFIG_CMD_NAND */

#define CONFIG_MMC
#define CONFIG_FSL_ESDHC
#define CONFIG_SYS_FSL_ESDHC_ADDR	0
#define CONFIG_SYS_FSL_ESDHC_NUM	1

#define CONFIG_SYS_FSL_ERRATUM_ESDHC111

#define CONFIG_CMD_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_CMD_FAT
#define CONFIG_CMD_EXT3
#define CONFIG_CMD_EXT4
#define CONFIG_DOS_PARTITION

#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_MII
#define CONFIG_FEC_MXC
#define CONFIG_MII
#define IMX_FEC_BASE			ENET_BASE_ADDR
#define CONFIG_FEC_XCV_TYPE		RMII
#define CONFIG_FEC_MXC_PHYADDR          0
#define CONFIG_PHYLIB
#define CONFIG_PHY_MICREL

/* I2C Configs */
#define CONFIG_CMD_I2C
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC_I2C1
#define CONFIG_SYS_I2C_MXC

#define CONFIG_BOOTDELAY		3
#define CONFIG_ZERO_BOOTDELAY_CHECK
#define CONFIG_BOARD_LATE_INIT

#define CONFIG_LOADADDR			0x82000000

/* We boot from the gfxRAM area of the OCRAM. */
#define CONFIG_SYS_TEXT_BASE		0x3f408000
#define CONFIG_BOARD_SIZE_LIMIT		524288

/* Miscellaneous configurable options */
#define CONFIG_SYS_LONGHELP		/* undef to save memory */
#define CONFIG_SYS_HUSH_PARSER		/* use "hush" command parser */
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#define CONFIG_AUTO_COMPLETE
#define CONFIG_CMDLINE_EDITING
#define CONFIG_SYS_CBSIZE		256	/* Console I/O Buffer Size */
#define CONFIG_SYS_PBSIZE		\
			(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS		16	/* max number of command args */
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE

#define CONFIG_CMD_MEMTEST
#define CONFIG_SYS_MEMTEST_START	0x80010000
#define CONFIG_SYS_MEMTEST_END		0x8FC00000

/*
 * Stack sizes
 * The stack sizes are set up in start.S using the settings below
 */
#define CONFIG_STACKSIZE		(128 * 1024)	/* regular stack */

/* Physical memory map */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM			(0x80000000)
#define PHYS_SDRAM_SIZE			(256 * 1024 * 1024)

#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR
#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* FLASH and environment organization */
#define CONFIG_SYS_NO_FLASH

#ifdef CONFIG_ENV_IS_IN_MMC
#define CONFIG_ENV_SIZE			(8 * 1024)

#define CONFIG_ENV_OFFSET		(12 * 64 * 1024)
#define CONFIG_SYS_MMC_ENV_DEV		0
#endif

#ifdef CONFIG_ENV_IS_IN_NAND
#define CONFIG_ENV_SECT_SIZE		(128 * 1024)
#define CONFIG_ENV_SIZE			(8 * 1024)
#define CONFIG_ENV_OFFSET		0x180000
#define CONFIG_ENV_SIZE_REDUND		(8 * 1024)
#define CONFIG_ENV_OFFSET_REDUND	0x1A0000
#endif

#define CONFIG_OF_LIBFDT
#define CONFIG_CMD_BOOTZ

/* GPIO support */
#define CONFIG_DM_GPIO
#define CONFIG_VYBRID_GPIO

/* USB Host Support */
#define CONFIG_CMD_USB
#ifdef CONFIG_CMD_USB
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_VF
#define CONFIG_USB_MAX_CONTROLLER_COUNT 2
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#endif /* CONFIG_CMD_USB */

/* USB Device Support */
#define CONFIG_USB_GADGET
#ifdef CONFIG_USB_GADGET

#define CONFIG_CI_UDC
#define CONFIG_USB_GADGET_DUALSPEED
#define CONFIG_USB_GADGET_VBUS_DRAW	2
#define CONFIG_G_DNL_MANUFACTURER	"Elnico"
#define CONFIG_G_DNL_VENDOR_NUM		0x0525		// Freescale`s vendor ID
#define CONFIG_G_DNL_PRODUCT_NUM	0xa4a5		// Freescale`s product ID

/* USB DFU */
#define CONFIG_USB_GADGET_DOWNLOAD
#define CONFIG_CMD_DFU
#define CONFIG_USB_FUNCTION_DFU
#define CONFIG_DFU_NAND
#define CONFIG_DFU_MMC
#define CONFIG_SYS_DFU_DATA_BUF_SIZE	(1024 * 1024)
#define CONFIG_FAT_WRITE

/* USB Storage */
#define CONFIG_USB_STORAGE
#define CONFIG_USB_FUNCTION_MASS_STORAGE
#define CONFIG_CMD_USB_MASS_STORAGE

#endif /* CONFIG_USB_GADGET */


/* Environment configuration */
#ifndef CONFIG_ELNICO_SUPPRESS_ENVIRONMENT

#define CONFIG_EXTRA_BOOTCMD_MMC                "bootcmd_mmc=mmc rescan;fatload mmc 0:1 ${loadaddr} ${kernel};bootm ${loadaddr}"
#define CONFIG_EXTRA_BOOTCMD_MMC_DEBUG_A5       "bootcmd_mmc_debug_a5=run bootargs_base bootargs_mmc bootargs_debug_a5 bootcmd_mmc"
#define CONFIG_EXTRA_BOOTCMD_MMC_DEBUG_M4       "bootcmd_mmc_debug_m4=run bootargs_base bootargs_mmc bootargs_debug_m4 bootcmd_mmc"
#define CONFIG_EXTRA_BOOTCMD_MMC_RELEASE        "bootcmd_mmc_release=run bootargs_base bootargs_mmc bootargs_release bootcmd_mmc"

#define CONFIG_EXTRA_BOOTCMD_NAND               "bootcmd_nand=nboot mtd_kernel;bootm"
#define CONFIG_EXTRA_BOOTCMD_NAND_DEBUG_A5      "bootcmd_nand_debug_a5=run bootargs_base bootargs_nand bootargs_debug_a5 bootcmd_nand"
#define CONFIG_EXTRA_BOOTCMD_NAND_DEBUG_M4      "bootcmd_nand_debug_m4=run bootargs_base bootargs_nand bootargs_debug_m4 bootcmd_nand"
#define CONFIG_EXTRA_BOOTCMD_NAND_RELEASE       "bootcmd_nand_release=run bootargs_base bootargs_nand bootargs_release bootcmd_nand"
#define CONFIG_EXTRA_MTDPARTS                   "mtdparts=" MTDPARTS_DEFAULT
#define CONFIG_EXTRA_MTDIDS                     "mtdids=" MTDIDS_DEFAULT

#define CONFIG_EXTRA_BOOTARGS_BASE              "bootargs_base=setenv bootargs mem=256M"
#define CONFIG_EXTRA_BOOTARGS_MMC               "bootargs_mmc=setenv bootargs ${bootargs} root=/dev/mmcblk0p2 ${rootfs_rights} rootwait"
#define CONFIG_EXTRA_BOOTARGS_NAND              "bootargs_nand=setenv bootargs ${bootargs} ${mtdparts} ubi.mtd=mtd_rootfs root=ubi0_0 rootfstype=ubifs ${rootfs_rights} rootwait"
#define CONFIG_EXTRA_BOOTARGS_DEBUG_A5          "bootargs_debug_a5=setenv bootargs ${bootargs} console=ttymxc1,115200 2"
#define CONFIG_EXTRA_BOOTARGS_DEBUG_M4          "bootargs_debug_m4=setenv bootargs ${bootargs} console=ttymxc0,115200 quiet 3"
#define CONFIG_EXTRA_BOOTARGS_RELEASE           "bootargs_release=setenv bootargs ${bootargs} console=ttymxc0,115200 quiet 5"
#define CONFIG_EXTRA_ROOTFS_RIGHTS              "rootfs_rights=rw"

#define CONFIG_EXTRA_ETHADDR                    "ethaddr=00:e0:0c:bc:e5:60"
#define CONFIG_EXTRA_IPADDR                     "ipaddr=192.168.10.222"

#define CONFIG_EXTRA_ENV_DFU_ALT_INFO           "dfu_alt_info=kernel part 0 1;rootfs part 0 2;uImage fat 0 1"
#define CONFIG_EXTRA_ENV_DFU_BUFSIZ             "dfu_bufsiz=524288"

#define CONFIG_EXTRA_ENV_SETTINGS_GENERAL                                       \
        "kernel=uImage"                                                 "\0"    \
        CONFIG_EXTRA_BOOTARGS_BASE                                      "\0"    \
        CONFIG_EXTRA_BOOTARGS_DEBUG_A5                                  "\0"    \
        CONFIG_EXTRA_BOOTARGS_DEBUG_M4                                  "\0"    \
        CONFIG_EXTRA_BOOTARGS_RELEASE                                   "\0"    \
        CONFIG_EXTRA_ROOTFS_RIGHTS                                      "\0"    \
        ""

#define CONFIG_EXTRA_ENV_SETTINGS_MMC                                           \
        CONFIG_EXTRA_BOOTARGS_MMC                                       "\0"    \
        CONFIG_EXTRA_BOOTCMD_MMC                                        "\0"    \
        CONFIG_EXTRA_BOOTCMD_MMC_DEBUG_A5                               "\0"    \
        CONFIG_EXTRA_BOOTCMD_MMC_DEBUG_M4                               "\0"    \
        CONFIG_EXTRA_BOOTCMD_MMC_RELEASE                                "\0"    \
        ""

#ifdef CONFIG_CMD_NAND
# define CONFIG_EXTRA_ENV_SETTINGS_NAND                                         \
        CONFIG_EXTRA_BOOTARGS_NAND                                      "\0"    \
        CONFIG_EXTRA_BOOTCMD_NAND                                       "\0"    \
        CONFIG_EXTRA_BOOTCMD_NAND_DEBUG_A5                              "\0"    \
        CONFIG_EXTRA_BOOTCMD_NAND_DEBUG_M4                              "\0"    \
        CONFIG_EXTRA_BOOTCMD_NAND_RELEASE                               "\0"    \
        CONFIG_EXTRA_MTDPARTS                                           "\0"    \
        CONFIG_EXTRA_MTDIDS                                             "\0"    \
        ""
#else /* !CONFIG_CMD_NAND */
# define CONFIG_EXTRA_ENV_SETTINGS_NAND         ""
#endif /* !CONFIG_CMD_NAND */

#define CONFIG_EXTRA_ENV_SETTINGS_NET                                           \
        CONFIG_EXTRA_ETHADDR                                            "\0"    \
        CONFIG_EXTRA_IPADDR                                             "\0"    \
        ""

#ifdef CONFIG_USB_GADGET
# define CONFIG_EXTRA_ENV_SETTINGS_USB                                          \
        CONFIG_EXTRA_ENV_DFU_ALT_INFO                                   "\0"    \
        CONFIG_EXTRA_ENV_DFU_BUFSIZ                                     "\0"    \
        ""
#else /* !CONFIG_USB_GADGET */
# define CONFIG_EXTRA_ENV_SETTINGS_USB          ""
#endif /* !CONFIG_USB_GADGET */

#define CONFIG_EXTRA_ENV_SETTINGS                                               \
        CONFIG_EXTRA_ENV_SETTINGS_GENERAL                                       \
        CONFIG_EXTRA_ENV_SETTINGS_MMC                                           \
        CONFIG_EXTRA_ENV_SETTINGS_NAND                                          \
        CONFIG_EXTRA_ENV_SETTINGS_NET                                           \
        CONFIG_EXTRA_ENV_SETTINGS_USB                                           \
        ""

#define CONFIG_BOOTCOMMAND                                                      \
        "run bootcmd_mmc_debug_a5"

#endif /* !CONFIG_ELNICO_SUPPRESS_ENVIRONMENT */

#endif /* __CONFIG_H */
