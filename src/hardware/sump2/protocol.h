/*
 * This file is part of the libsigrok project.
 *
 * Copyright (C) 2013 Bert Vermeulen <bert@biot.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBSIGROK_HARDWARE_SUMP2_PROTOCOL_H
#define LIBSIGROK_HARDWARE_SUMP2_PROTOCOL_H

#include <stdint.h>
#include <string.h>
//#include <glib.h>
#include <libsigrok/libsigrok.h>
#include "libsigrok-internal.h"

#define LOG_PREFIX "sump2"

/* Registers */
#define ADDR_BASE									0x00000010
#define ADDR_CTRL									ADDR_BASE
#define ADDR_DATA									ADDR_BASE + 4

/* Commands */
#define CMD_STATE_IDLE				 		0x00
#define CMD_STATE_ARM       			0x01
#define CMD_STATE_RESET      			0x02 // Always Reset before Arm.

// self.cmd_wr_trig_type      = 0x04;
// self.cmd_wr_trig_field     = 0x05;# Correspond to Event Bits
// self.cmd_wr_trig_dly_nth   = 0x06;# Trigger Delay and Nth
// self.cmd_wr_trig_position  = 0x07;# Samples post Trigger to Capture
// self.cmd_wr_rle_event_en   = 0x08;# Enables events for RLE detection
// self.cmd_wr_ram_ptr        = 0x09;# Load specific pointer.
// self.cmd_wr_ram_page       = 0x0a;# Load DWORD Page.

#define CMD_RD_HW_ID_REV					0x0b
#define CMD_RD_RAM_WIDTH_LEN			0x0c
#define CMD_RD_SAMPLE_FREQ				0x0d
#define CMD_RD_TRIGGER_PTR	    	0x0e
#define CMD_RD_RAM_DATA       		0x0f

// self.cmd_rd_ds_width_len     = 0x18;# DeepSUMP registers
// self.cmd_rd_ds_trig_status   = 0x19;
// self.cmd_rd_ds_ram_data      = 0x1a;
// self.cmd_wr_ds_ram_ptr       = 0x1b;
// self.cmd_wr_ds_ram_page      = 0x1c;
// self.cmd_wr_ds_user_ctrl     = 0x1d;
// self.cmd_wr_ds_user_mask     = 0x1e;
// self.cmd_wr_ds_user_cfg      = 0x1f;
//
// self.cmd_wr_user_ctrl      = 0x10;
// self.cmd_wr_user_pattern0  = 0x11;# Also Mask    for Pattern Matching
// self.cmd_wr_user_pattern1  = 0x12;# Also Pattern for Pattern Matching
// self.cmd_wr_user_data_en   = 0x13;# Special Data Enable Capture Mode
// self.cmd_wr_watchdog_time  = 0x14;# Watchdog Timeout
//
// self.trig_and_ris          = 0x00;# Bits AND Rising
// self.trig_and_fal          = 0x01;# Bits AND Falling
// self.trig_or_ris           = 0x02;# Bits OR  Rising
// self.trig_or_fal           = 0x03;# Bits OR  Falling
// self.trig_pat_ris          = 0x04;# Pattern Match Rising
// self.trig_pat_fal          = 0x05;# Pattern Match Falling
// self.trig_in_ris           = 0x06;# External Input Trigger Rising
// self.trig_in_fal           = 0x07;# External Input Trigger Falling
// self.trig_watchdog         = 0x08;# Watchdog trigger
// self.cfg_dict = {};
//
// self.ds_status_overrun_err = 0x80000000;# DeepSUMP RAM was overrun
// self.ds_status_rle_done    = 0x40000000;# DeepSUMP Acquisition Complete
// self.ds_status_triggered   = 0x20000000;# DeepSUMP has Triggered
// self.ds_status_rle_pre     = 0x10000000;# DeepSUMP RLEpre has finished
//
// self.status_armed          = 0x01;# Engine is Armed, ready for trigger
// self.status_triggered      = 0x02;# Engine has been triggered
// self.status_ram_post       = 0x04;# Engine has filled post-trig RAM
// self.status_ram_pre        = 0x08;# Engine has filled pre-trigger RAM
// self.status_rle_pre        = 0x10;# RLE Engine has filled pre-trig RAM
// self.status_rle_post       = 0x20;# RLE Engine has filled post-trig RAM
// self.status_rle_en         = 0x80;# RLE Engine is present


/* original */

#define NUM_TRIGGER_STAGES         4
#define CLOCK_RATE                 SR_MHZ(100)
#define MIN_NUM_SAMPLES            4
#define DEFAULT_SAMPLERATE         SR_KHZ(200)

/* Command opcodes */
#define CMD_RESET                  0x00
#define CMD_RUN                    0x01
#define CMD_ID                     0x02
#define CMD_TESTMODE               0x03
#define CMD_METADATA               0x04
#define CMD_SET_DIVIDER            0x80
#define CMD_CAPTURE_SIZE           0x81
#define CMD_SET_FLAGS              0x82
#define CMD_CAPTURE_DELAYCOUNT     0x83		/* extension for Pepino */
#define CMD_CAPTURE_READCOUNT      0x84		/* extension for Pepino */
#define CMD_SET_TRIGGER_MASK       0xc0
#define CMD_SET_TRIGGER_VALUE      0xc1
#define CMD_SET_TRIGGER_CONFIG     0xc2

/* Trigger config */
#define TRIGGER_START              (1 << 3)

/* Bitmasks for CMD_FLAGS */
/* 12-13 unused, 14-15 RLE mode (we hardcode mode 0). */
#define FLAG_INTERNAL_TEST_MODE    (1 << 11)
#define FLAG_EXTERNAL_TEST_MODE    (1 << 10)
#define FLAG_SWAP_CHANNELS         (1 << 9)
#define FLAG_RLE                   (1 << 8)
#define FLAG_SLOPE_FALLING         (1 << 7)
#define FLAG_CLOCK_EXTERNAL        (1 << 6)
#define FLAG_CHANNELGROUP_4        (1 << 5)
#define FLAG_CHANNELGROUP_3        (1 << 4)
#define FLAG_CHANNELGROUP_2        (1 << 3)
#define FLAG_CHANNELGROUP_1        (1 << 2)
#define FLAG_FILTER                (1 << 1)
#define FLAG_DEMUX                 (1 << 0)

struct dev_context {
	int max_channels;
	uint32_t max_samples;
	uint32_t max_samplerate;
	uint32_t protocol_version;

	uint64_t cur_samplerate;
	uint32_t cur_samplerate_divider;
	uint64_t limit_samples;
	uint64_t capture_ratio;
	int trigger_at;
	uint32_t channel_mask;
	uint32_t trigger_mask[NUM_TRIGGER_STAGES];
	uint32_t trigger_value[NUM_TRIGGER_STAGES];
	int num_stages;
	uint16_t flag_reg;

	unsigned int num_transfers;
	unsigned int num_samples;
	int num_bytes;
	int cnt_bytes;
	int cnt_samples;
	int cnt_samples_rle;

	unsigned int rle_count;
	unsigned char sample[4];
	unsigned char tmp_sample[4];
	unsigned char *raw_sample_buf;
};

SR_PRIV extern const char *ols_channel_names[];

SR_PRIV int send_shortcommand(struct sr_serial_dev_inst *serial,
		uint8_t command);
SR_PRIV int send_longcommand(struct sr_serial_dev_inst *serial,
		uint8_t command, uint8_t *data);
SR_PRIV int ols_send_reset(struct sr_serial_dev_inst *serial);
SR_PRIV void ols_channel_mask(const struct sr_dev_inst *sdi);
SR_PRIV int ols_convert_trigger(const struct sr_dev_inst *sdi);
SR_PRIV struct dev_context *ols_dev_new(void);
SR_PRIV struct sr_dev_inst *get_metadata(struct sr_serial_dev_inst *serial);
SR_PRIV int ols_set_samplerate(const struct sr_dev_inst *sdi,
		uint64_t samplerate);
SR_PRIV void abort_acquisition(const struct sr_dev_inst *sdi);
SR_PRIV int ols_receive_data(int fd, int revents, void *cb_data);

#endif
