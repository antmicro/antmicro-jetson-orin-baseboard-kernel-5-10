/*
 * file based on ov5693.h
 * Copyright (c) 2013-2015, NVIDIA CORPORATION.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __OV5640_H__
#define __OV5640_H__

#include <media/nvc.h>
#include <uapi/media/nvc_image.h>
#include <uapi/media/ov5640.h>

#define OV5640_INVALID_COARSE_TIME  -1

#define OV5640_EEPROM_ADDRESS		0x50
#define OV5640_EEPROM_SIZE		1024
#define OV5640_EEPROM_STR_SIZE		(OV5640_EEPROM_SIZE * 2)
#define OV5640_EEPROM_BLOCK_SIZE	(1 << 8)
#define OV5640_EEPROM_NUM_BLOCKS \
	(OV5640_EEPROM_SIZE / OV5640_EEPROM_BLOCK_SIZE)

#define OV5640_OTP_LOAD_CTRL_ADDR	0x3D81
#define OV5640_OTP_BANK_SELECT_ADDR	0x3D84
#define OV5640_OTP_BANK_START_ADDR	0x3D00
#define OV5640_OTP_BANK_END_ADDR	0x3D0F
#define OV5640_OTP_NUM_BANKS		(32)
#define OV5640_OTP_BANK_SIZE \
	 (OV5640_OTP_BANK_END_ADDR - OV5640_OTP_BANK_START_ADDR + 1)
#define OV5640_OTP_SIZE \
	 (OV5640_OTP_BANK_SIZE * OV5640_OTP_NUM_BANKS)
#define OV5640_OTP_STR_SIZE (OV5640_OTP_SIZE * 2)

#define OV5640_FUSE_ID_OTP_START_ADDR	0x3D00
#define OV5640_FUSE_ID_OTP_BANK	0
#define OV5640_FUSE_ID_SIZE		8
#define OV5640_FUSE_ID_STR_SIZE	(OV5640_FUSE_ID_SIZE * 2)

#define OV5640_FRAME_LENGTH_ADDR_MSB		0x380E
#define OV5640_FRAME_LENGTH_ADDR_LSB		0x380F
#define OV5640_COARSE_TIME_ADDR_1		0x3500
#define OV5640_COARSE_TIME_ADDR_2		0x3501
#define OV5640_COARSE_TIME_ADDR_3		0x3502
#define OV5640_COARSE_TIME_SHORT_ADDR_1	0x3506
#define OV5640_COARSE_TIME_SHORT_ADDR_2	0x3507
#define OV5640_COARSE_TIME_SHORT_ADDR_3	0x3508
#define OV5640_GAIN_ADDR_MSB			0x350A
#define OV5640_GAIN_ADDR_LSB			0x350B
#define OV5640_GROUP_HOLD_ADDR			0x3208
#define OV5640_TIMING_REG20			0x3820
#define VERTICAL_FLIP				(0x3 << 1)
#define OV5640_TIMING_REG21			0x3821
#define HORIZONTAL_MIRROR_MASK			(0x3 << 1)

/* See notes in the nvc.h file on the GPIO usage */
enum ov5640_gpio_type {
	OV5640_GPIO_TYPE_PWRDN = 0,
	OV5640_GPIO_TYPE_RESET,
};

struct ov5640_eeprom_data {
	struct i2c_client *i2c_client;
	struct i2c_adapter *adap;
	struct i2c_board_info brd;
	struct regmap *regmap;
};

struct ov5640_power_rail {
	struct regulator *dvdd;
	struct regulator *avdd;
	struct regulator *dovdd;
};

struct ov5640_regulators {
	const char *avdd;
	const char *dvdd;
	const char *dovdd;
};

struct ov5640_platform_data {
	unsigned cfg;
	unsigned num;
	const char *dev_name;
	unsigned gpio_count; /* see nvc.h GPIO notes */
	struct nvc_gpio_pdata *gpio; /* see nvc.h GPIO notes */
	struct nvc_imager_static_nvc *static_info;
	bool use_vcm_vdd;
	int (*probe_clock)(unsigned long);
	int (*power_on)(struct ov5640_power_rail *);
	int (*power_off)(struct ov5640_power_rail *);
	const char *mclk_name;
	struct nvc_imager_cap *cap;
	struct ov5640_regulators regulators;
	bool has_eeprom;
	bool use_cam_gpio;
};

#endif  /* __OV5640_H__ */
