/*
 * Copyright (c) 2017-2020, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <errno.h>

#include <platform_def.h>

#include <common/bl_common.h>
#include <common/debug.h>
#include <common/desc_image_load.h>
#include <common/image_decompress.h>
#include <drivers/io/io_storage.h>
#include <lib/xlat_tables/xlat_tables_v2.h>
#include <plat/common/platform.h>
#ifdef UNIPHIER_DECOMPRESS_GZIP
#include <tf_gunzip.h>
#endif

#include "uniphier.h"

#define BL2_SIZE		((BL2_END) - (BL2_BASE))

#define UNIPHIER_IMAGE_BUF_BASE		0x84300000UL
#define UNIPHIER_IMAGE_BUF_SIZE		0x00100000UL

static int uniphier_bl2_kick_scp;

void bl2_el3_early_platform_setup(u_register_t x0, u_register_t x1,
				  u_register_t x2, u_register_t x3)
{
	uniphier_console_setup();
}

void bl2_el3_plat_arch_setup(void)
{
	unsigned int soc;
	int skip_scp = 0;
	int ret;

	uniphier_mmap_setup(BL2_BASE, BL2_SIZE, NULL);
	enable_mmu_el3(0);

	soc = uniphier_get_soc_id();
	if (soc == UNIPHIER_SOC_UNKNOWN) {
		ERROR("unsupported SoC\n");
		plat_error_handler(-ENOTSUP);
	}

	ret = uniphier_io_setup(soc);
	if (ret) {
		ERROR("failed to setup io devices\n");
		plat_error_handler(ret);
	}

	switch (uniphier_get_boot_master(soc)) {
	case UNIPHIER_BOOT_MASTER_THIS:
		INFO("Booting from this SoC\n");
		skip_scp = 1;
		break;
	case UNIPHIER_BOOT_MASTER_SCP:
		INFO("Booting from on-chip SCP\n");
		if (uniphier_scp_is_running()) {
			INFO("SCP is already running. SCP_BL2 load will be skipped.\n");
			skip_scp = 1;
		}

		/*
		 * SCP must be kicked every time even if it is already running
		 * because it polls this event after the reboot of the backend.
		 */
		uniphier_bl2_kick_scp = 1;
		break;
	case UNIPHIER_BOOT_MASTER_EXT:
		INFO("Booting from external SCP\n");
		skip_scp = 1;
		break;
	default:
		plat_error_handler(-ENOTSUP);
		break;
	}

	if (skip_scp) {
		struct image_info *image_info;

		image_info = uniphier_get_image_info(SCP_BL2_IMAGE_ID);
		image_info->h.attr |= IMAGE_ATTRIB_SKIP_LOADING;
	}
}

void bl2_platform_setup(void)
{
}

void plat_flush_next_bl_params(void)
{
	flush_bl_params_desc();
}

bl_load_info_t *plat_get_bl_image_load_info(void)
{
	return get_bl_load_info_from_mem_params_desc();
}

bl_params_t *plat_get_next_bl_params(void)
{
	return get_next_bl_params_from_mem_params_desc();
}

void bl2_plat_preload_setup(void)
{
#ifdef UNIPHIER_DECOMPRESS_GZIP
	int ret;

	ret = mmap_add_dynamic_region(UNIPHIER_IMAGE_BUF_BASE,
				      UNIPHIER_IMAGE_BUF_BASE,
				      UNIPHIER_IMAGE_BUF_SIZE,
				      MT_MEMORY | MT_RW | MT_NS);
	if (ret)
		plat_error_handler(ret);

	image_decompress_init(UNIPHIER_IMAGE_BUF_BASE,
			      UNIPHIER_IMAGE_BUF_SIZE,
			      gunzip);
#endif
}

int bl2_plat_handle_pre_image_load(unsigned int image_id)
{
	struct image_info *image_info;
	int ret;

	image_info = uniphier_get_image_info(image_id);

	ret = mmap_add_dynamic_region(image_info->image_base,
				      image_info->image_base,
				      image_info->image_max_size,
				      MT_MEMORY | MT_RW | MT_NS);
	if (ret)
		return ret;

#ifdef UNIPHIER_DECOMPRESS_GZIP
	image_decompress_prepare(image_info);
#endif
	return 0;
}

int bl2_plat_handle_post_image_load(unsigned int image_id)
{
	struct image_info *image_info = uniphier_get_image_info(image_id);
#ifdef UNIPHIER_DECOMPRESS_GZIP
	int ret;

	if (!(image_info->h.attr & IMAGE_ATTRIB_SKIP_LOADING)) {
		ret = image_decompress(uniphier_get_image_info(image_id));
		if (ret)
			return ret;
	}
#endif

	if (image_id == SCP_BL2_IMAGE_ID && uniphier_bl2_kick_scp)
		uniphier_scp_start(image_info->image_base);

	return 0;
}
