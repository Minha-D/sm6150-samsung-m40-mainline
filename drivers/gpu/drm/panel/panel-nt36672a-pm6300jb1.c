// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 Minhazul Hassan
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/delay.h>
#include <linux/device-id/of.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/regulator/consumer.h>

#include <video/mipi_display.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>
#include <drm/drm_probe_helper.h>

/*
 * Fixed 0x51 value (no backlight device yet). Downstream maps userspace
 * 1..255 to 1..181, level 128 -> 58. 255 is only the "outdoor" level;
 * keep this <= 181.
 */
#define NT36672A_PM6300JB1_BRIGHTNESS	58

struct nt36672a_pm6300jb1 {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct regulator *vddr;		/* 1.8 V logic (pm6150 L15) */
	struct regulator *vddpos;	/* LM36274 ENP bias */
	struct regulator *vddneg;	/* LM36274 ENN bias */
	struct gpio_desc *reset_gpio;
};

static inline
struct nt36672a_pm6300jb1 *to_nt36672a_pm6300jb1(struct drm_panel *panel)
{
	return container_of_const(panel, struct nt36672a_pm6300jb1, panel);
}

static void nt36672a_pm6300jb1_reset(struct nt36672a_pm6300jb1 *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
}

static int nt36672a_pm6300jb1_on(struct nt36672a_pm6300jb1 *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x07, 0x9e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0f, 0xa4);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x62, 0xb2);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6d, 0x44);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x78, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x95, 0xe1);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x96, 0xe1);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x24);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x00, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x01, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x02, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x03, 0x0e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x04, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x05, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x06, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x07, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x08, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x09, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0a, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0b, 0x0d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0c, 0x1e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0d, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0e, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0f, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x10, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x11, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x12, 0x14);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x13, 0x12);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x14, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x15, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x16, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x17, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x18, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x19, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1a, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1b, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1c, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1d, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1e, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1f, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x20, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x21, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x22, 0x0d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x23, 0x1e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x24, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x25, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x26, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x27, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x28, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x29, 0x14);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2a, 0x12);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2b, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2d, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2f, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x31, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x32, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x33, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x34, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x37, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x38, 0x6e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x39, 0x6e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x3f, 0x6e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x41, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x42, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4c, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4d, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x60, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x61, 0x24);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x72, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x73, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x74, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x75, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x79, 0x87);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7a, 0x0b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7b, 0x9c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7c, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7d, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x80, 0x45);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x81, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x82, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x83, 0x22);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x84, 0x31);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x85, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x86, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x87, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x88, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x89, 0x22);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8a, 0x31);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8b, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8c, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8d, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8e, 0xf4);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8f, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x90, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x92, 0x73);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9d, 0xb1);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb3, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xdc, 0x25);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xdd, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xde, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xdf, 0x72);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe0, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xeb, 0x0b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x25);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x21, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x22, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x24, 0x73);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x25, 0x73);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x30, 0x2f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x38, 0x2f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x3f, 0x21);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x40, 0x5f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4b, 0x21);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4c, 0x5f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x69, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x84, 0x78);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x85, 0x75);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8d, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbf, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc2, 0x5a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd9, 0x48);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xdb, 0x22);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x26);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x06, 0xff);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x12, 0x75);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x19, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1a, 0xf7);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1c, 0xaf);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1e, 0x7a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x98, 0xf1);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa9, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xaa, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xae, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x27);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x13, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1e, 0x14);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0xf0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa2, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0,
				     0x00, 0x10, 0x00, 0x32, 0x00, 0x65, 0x00,
				     0x8b, 0x00, 0xa9, 0x00, 0xc2, 0x00, 0xd9,
				     0x00, 0xeb);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb1,
				     0x00, 0xfb, 0x01, 0x35, 0x01, 0x5e, 0x01,
				     0x9b, 0x01, 0xc9, 0x02, 0x0e, 0x02, 0x45,
				     0x02, 0x47);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb2,
				     0x02, 0x6c, 0x02, 0xa8, 0x02, 0xcc, 0x03,
				     0x0b, 0x03, 0x2a, 0x03, 0x50, 0x03, 0x5d,
				     0x03, 0x6a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb3,
				     0x03, 0x7a, 0x03, 0x8a, 0x03, 0xa1, 0x03,
				     0xb7, 0x03, 0xce, 0x03, 0xd3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4,
				     0x00, 0x10, 0x00, 0x32, 0x00, 0x65, 0x00,
				     0x8b, 0x00, 0xa9, 0x00, 0xc2, 0x00, 0xd9,
				     0x00, 0xeb);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb5,
				     0x00, 0xfb, 0x01, 0x35, 0x01, 0x5e, 0x01,
				     0x9b, 0x01, 0xc9, 0x02, 0x0e, 0x02, 0x45,
				     0x02, 0x47);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb6,
				     0x02, 0x6c, 0x02, 0xa8, 0x02, 0xcc, 0x03,
				     0x0b, 0x03, 0x2a, 0x03, 0x50, 0x03, 0x5d,
				     0x03, 0x6a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb7,
				     0x03, 0x7a, 0x03, 0x8a, 0x03, 0xa1, 0x03,
				     0xb7, 0x03, 0xce, 0x03, 0xd3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb8,
				     0x00, 0x10, 0x00, 0x32, 0x00, 0x65, 0x00,
				     0x8b, 0x00, 0xa9, 0x00, 0xc2, 0x00, 0xd9,
				     0x00, 0xeb);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb9,
				     0x00, 0xfb, 0x01, 0x35, 0x01, 0x5e, 0x01,
				     0x9b, 0x01, 0xc9, 0x02, 0x0e, 0x02, 0x45,
				     0x02, 0x47);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xba,
				     0x02, 0x6c, 0x02, 0xa8, 0x02, 0xcc, 0x03,
				     0x0b, 0x03, 0x2a, 0x03, 0x50, 0x03, 0x5d,
				     0x03, 0x6a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbb,
				     0x03, 0x7a, 0x03, 0x8a, 0x03, 0xa1, 0x03,
				     0xb7, 0x03, 0xce, 0x03, 0xd3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x21);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0,
				     0x00, 0x18, 0x00, 0x3a, 0x00, 0x6d, 0x00,
				     0x93, 0x00, 0xb1, 0x00, 0xca, 0x00, 0xe1,
				     0x00, 0xf3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb1,
				     0x01, 0x03, 0x01, 0x3d, 0x01, 0x66, 0x01,
				     0xa3, 0x01, 0xd1, 0x02, 0x16, 0x02, 0x4d,
				     0x02, 0x4f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb2,
				     0x02, 0x8e, 0x02, 0xca, 0x02, 0xee, 0x03,
				     0x13, 0x03, 0x32, 0x03, 0x58, 0x03, 0x65,
				     0x03, 0x72);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb3,
				     0x03, 0x82, 0x03, 0x92, 0x03, 0xa9, 0x03,
				     0xbf, 0x03, 0xd6, 0x03, 0xdb);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4,
				     0x00, 0x18, 0x00, 0x3a, 0x00, 0x6d, 0x00,
				     0x93, 0x00, 0xb1, 0x00, 0xca, 0x00, 0xe1,
				     0x00, 0xf3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb5,
				     0x01, 0x03, 0x01, 0x3d, 0x01, 0x66, 0x01,
				     0xa3, 0x01, 0xd1, 0x02, 0x16, 0x02, 0x4d,
				     0x02, 0x4f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb6,
				     0x02, 0x8e, 0x02, 0xca, 0x02, 0xee, 0x03,
				     0x13, 0x03, 0x32, 0x03, 0x58, 0x03, 0x65,
				     0x03, 0x72);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb7,
				     0x03, 0x82, 0x03, 0x92, 0x03, 0xa9, 0x03,
				     0xbf, 0x03, 0xd6, 0x03, 0xdb);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb8,
				     0x00, 0x18, 0x00, 0x3a, 0x00, 0x6d, 0x00,
				     0x93, 0x00, 0xb1, 0x00, 0xca, 0x00, 0xe1,
				     0x00, 0xf3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb9,
				     0x01, 0x03, 0x01, 0x3d, 0x01, 0x66, 0x01,
				     0xa3, 0x01, 0xd1, 0x02, 0x16, 0x02, 0x4d,
				     0x02, 0x4f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xba,
				     0x02, 0x8e, 0x02, 0xca, 0x02, 0xee, 0x03,
				     0x13, 0x03, 0x32, 0x03, 0x58, 0x03, 0x65,
				     0x03, 0x72);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbb,
				     0x03, 0x82, 0x03, 0x92, 0x03, 0xa9, 0x03,
				     0xbf, 0x03, 0xd6, 0x03, 0xdb);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x62, 0xaf);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5d, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x24);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x93, 0x0c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x94, 0x0e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x35, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x23);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x07, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x08, 0x0c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x53, 0x24);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x51, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x10);

	/* downstream: sleep out, 120 ms, display on (29h) */
	mipi_dsi_dcs_exit_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);
	mipi_dsi_dcs_set_display_on_multi(&dsi_ctx);

	/* DDI spec: 51h only 40 ms after 29h. Raw 1-byte write on purpose. */
	mipi_dsi_msleep(&dsi_ctx, 40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_DISPLAY_BRIGHTNESS,
				     NT36672A_PM6300JB1_BRIGHTNESS);

	return dsi_ctx.accum_err;
}

static int nt36672a_pm6300jb1_off(struct nt36672a_pm6300jb1 *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_set_display_off_multi(&dsi_ctx);
	mipi_dsi_dcs_enter_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 67);

	return dsi_ctx.accum_err;
}

static void nt36672a_pm6300jb1_power_off(struct nt36672a_pm6300jb1 *ctx)
{
	/* downstream lm36274_bl_ic_en(0): ENN, 1.5 ms, ENP, 15 ms */
	regulator_disable(ctx->vddneg);
	usleep_range(1500, 2000);
	regulator_disable(ctx->vddpos);
	usleep_range(15000, 16000);
	regulator_disable(ctx->vddr);
}

static int nt36672a_pm6300jb1_prepare(struct drm_panel *panel)
{
	struct nt36672a_pm6300jb1 *ctx = to_nt36672a_pm6300jb1(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = regulator_enable(ctx->vddr);
	if (ret < 0) {
		dev_err(dev, "Failed to enable vddr: %d\n", ret);
		return ret;
	}
	usleep_range(1000, 2000);	/* downstream supply-post-on-sleep */

	/* order matters: ENP (+5.5 V) first, then ENN (-5.5 V) */
	ret = regulator_enable(ctx->vddpos);
	if (ret < 0) {
		dev_err(dev, "Failed to enable vddpos: %d\n", ret);
		goto err_vddr;
	}

	ret = regulator_enable(ctx->vddneg);
	if (ret < 0) {
		dev_err(dev, "Failed to enable vddneg: %d\n", ret);
		goto err_vddpos;
	}

	nt36672a_pm6300jb1_reset(ctx);

	ret = nt36672a_pm6300jb1_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		nt36672a_pm6300jb1_power_off(ctx);
		return ret;
	}

	return 0;

err_vddpos:
	regulator_disable(ctx->vddpos);
err_vddr:
	regulator_disable(ctx->vddr);
	return ret;
}

static int nt36672a_pm6300jb1_unprepare(struct drm_panel *panel)
{
	struct nt36672a_pm6300jb1 *ctx = to_nt36672a_pm6300jb1(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = nt36672a_pm6300jb1_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	nt36672a_pm6300jb1_power_off(ctx);

	return 0;
}

static const struct drm_display_mode nt36672a_pm6300jb1_mode = {
	.clock = (1080 + 32 + 48 + 32) * (2340 + 12 + 4 + 10) * 60 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 32,
	.hsync_end = 1080 + 32 + 48,
	.htotal = 1080 + 32 + 48 + 32,
	.vdisplay = 2340,
	.vsync_start = 2340 + 12,
	.vsync_end = 2340 + 12 + 4,
	.vtotal = 2340 + 12 + 4 + 10,
	.width_mm = 67,
	.height_mm = 145,
	.type = DRM_MODE_TYPE_DRIVER,
};

static int nt36672a_pm6300jb1_get_modes(struct drm_panel *panel,
					struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &nt36672a_pm6300jb1_mode);
}

static const struct drm_panel_funcs nt36672a_pm6300jb1_panel_funcs = {
	.prepare = nt36672a_pm6300jb1_prepare,
	.unprepare = nt36672a_pm6300jb1_unprepare,
	.get_modes = nt36672a_pm6300jb1_get_modes,
};

static int nt36672a_pm6300jb1_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct nt36672a_pm6300jb1 *ctx;
	int ret;

	ctx = devm_drm_panel_alloc(dev, struct nt36672a_pm6300jb1, panel,
				   &nt36672a_pm6300jb1_panel_funcs,
				   DRM_MODE_CONNECTOR_DSI);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	ctx->vddr = devm_regulator_get(dev, "vddr");
	if (IS_ERR(ctx->vddr))
		return dev_err_probe(dev, PTR_ERR(ctx->vddr),
				     "Failed to get vddr\n");

	ctx->vddpos = devm_regulator_get(dev, "vddpos");
	if (IS_ERR(ctx->vddpos))
		return dev_err_probe(dev, PTR_ERR(ctx->vddpos),
				     "Failed to get vddpos\n");

	ctx->vddneg = devm_regulator_get(dev, "vddneg");
	if (IS_ERR(ctx->vddneg))
		return dev_err_probe(dev, PTR_ERR(ctx->vddneg),
				     "Failed to get vddneg\n");

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_CLOCK_NON_CONTINUOUS;

	ctx->panel.prepare_prev_first = true;

	ret = devm_drm_panel_add(dev, &ctx->panel);
	if (ret)
		return ret;

	return devm_mipi_dsi_attach(dev, dsi);
}

static const struct of_device_id nt36672a_pm6300jb1_of_match[] = {
	{ .compatible = "csot,nt36672a-pm6300jb1" },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, nt36672a_pm6300jb1_of_match);

static struct mipi_dsi_driver nt36672a_pm6300jb1_driver = {
	.probe = nt36672a_pm6300jb1_probe,
	.driver = {
		.name = "panel-nt36672a-pm6300jb1",
		.of_match_table = nt36672a_pm6300jb1_of_match,
	},
};
module_mipi_dsi_driver(nt36672a_pm6300jb1_driver);

MODULE_AUTHOR("Minhazul Hassan");
MODULE_DESCRIPTION("DRM driver for ss_dsi_panel_NT36672A_PM6300JB1_FHD");
MODULE_LICENSE("GPL");
