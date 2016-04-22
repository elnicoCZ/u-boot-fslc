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
					"128k(vf-bcb)ro,"		\
					"1408k(u-boot)ro,"		\
					"512k(u-boot-env),"		\
					"4m(kernel),"			\
					"512k(fdt),"		\
					"-(rootfs)"

#endif /* CONFIG_CMD_NAND */

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
#define CONFIG_BOARD_LATE_INIT

#define CONFIG_SYS_LOAD_ADDR		0x82000000

/* We boot from the gfxRAM area of the OCRAM. */
#define CONFIG_SYS_TEXT_BASE		0x3f408000
#define CONFIG_BOARD_SIZE_LIMIT		524288

#define MEM_LAYOUT_ENV_SETTINGS \
	"bootm_size=0x07000000\0" \
	"loadaddr=0x82000000\0" \
	"kernel_addr_r=0x82000000\0" \
	"fdt_addr=0x84000000\0" \
	"fdt_addr_r=0x84000000\0" \
	"rdaddr=0x84080000\0" \
	"ramdisk_addr_r=0x84080000\0"

#define DFU_ALT_NAND_INFO		"kernel part 0 1\;rootfs part 0 2\;uImage fat 0 1"
#define DFU_BUFSIZ			"524288"

#define CONFIG_EXTRA_ENV_SETTINGS \
	MEM_LAYOUT_ENV_SETTINGS \
	"script=boot.scr\0" \
	"image=zImage\0" \
	"console=ttyLP1\0" \
	"fdt_file=vf610-twr.dtb\0" \
	"boot_fdt=try\0" \
	"ip_dyn=yes\0" \
	"mmcdev=" __stringify(CONFIG_SYS_MMC_ENV_DEV) "\0" \
	"mmcpart=1\0" \
	"mmcroot=/dev/mmcblk0p2 rootwait rw\0" \
	"update_sd_firmware_filename=u-boot.imx\0" \
	"update_sd_firmware=" \
		"if test ${ip_dyn} = yes; then " \
			"setenv get_cmd dhcp; " \
		"else " \
			"setenv get_cmd tftp; " \
		"fi; " \
		"if mmc dev ${mmcdev}; then "	\
			"if ${get_cmd} ${update_sd_firmware_filename}; then " \
				"setexpr fw_sz ${filesize} / 0x200; " \
				"setexpr fw_sz ${fw_sz} + 1; "	\
				"mmc write ${loadaddr} 0x2 ${fw_sz}; " \
			"fi; "	\
		"fi\0" \
	"mmcargs=setenv bootargs console=${console},${baudrate} " \
		"root=${mmcroot}\0" \
	"loadbootscript=" \
		"fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${script};\0" \
	"bootscript=echo Running bootscript from mmc ...; " \
		"source\0" \
	"loadimage=fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${image}\0" \
	"loadfdt=fatload mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${fdt_file}\0" \
	"mmcboot=echo Booting from mmc ...; " \
		"run mmcargs; " \
		"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
			"if run loadfdt; then " \
				"bootz ${loadaddr} - ${fdt_addr}; " \
			"else " \
				"if test ${boot_fdt} = try; then " \
					"bootz; " \
				"else " \
					"echo WARN: Cannot load the DT; " \
				"fi; " \
			"fi; " \
		"else " \
			"bootz; " \
		"fi;\0" \
	"netargs=setenv bootargs console=${console},${baudrate} " \
		"root=/dev/nfs " \
	"ip=dhcp nfsroot=${serverip}:${nfsroot},v3,tcp\0" \
		"netboot=echo Booting from net ...; " \
		"run netargs; " \
		"if test ${ip_dyn} = yes; then " \
			"setenv get_cmd dhcp; " \
		"else " \
			"setenv get_cmd tftp; " \
		"fi; " \
		"${get_cmd} ${image}; " \
		"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
			"if ${get_cmd} ${fdt_addr} ${fdt_file}; then " \
				"bootz ${loadaddr} - ${fdt_addr}; " \
			"else " \
				"if test ${boot_fdt} = try; then " \
					"bootz; " \
				"else " \
					"echo WARN: Cannot load the DT; " \
				"fi; " \
			"fi; " \
		"else " \
			"bootz; " \
		"fi;\0" \
	"dfu_alt_info=" DFU_ALT_NAND_INFO "\0" \
	"dfu_bufsiz=" DFU_BUFSIZ "\0"

#define CONFIG_BOOTCOMMAND \
	   "mmc dev ${mmcdev}; if mmc rescan; then " \
		   "if run loadbootscript; then " \
			   "run bootscript; " \
		   "else " \
			   "if run loadimage; then " \
				   "run mmcboot; " \
			   "else run netboot; " \
			   "fi; " \
		   "fi; " \
	   "else run netboot; fi"

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
#define CONFIG_ENV_OFFSET		0xA0000
#define CONFIG_ENV_SIZE_REDUND		(8 * 1024)
#define CONFIG_ENV_OFFSET_REDUND	0xC0000
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

#endif /* __CONFIG_H */
