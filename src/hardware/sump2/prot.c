#include <stdio.h>
#include <string.h>
//#include "protocol.h"

/* Registers */
#define ADDR_BASE									0x00000090
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

typedef int bool;
#define true 1
#define false 0

static char mesa_lf = '\n';

void mesa_send_lf() {
  printf("%c", mesa_lf);
}

void mesa_init() {
    mesa_send_lf();
    printf("FFFFFFFF");
    mesa_send_lf();
}

void stringToHex(char *result, int start, void *input, int input_size) {
  int i,j;

  for(i=0, j=start; i<input_size; i++, j+=2)
  {
    sprintf((char*)result+j,"%02X", ((char *)input)[i]);
  }
  result[j] = 0x00;
}

#define MESA_MAX_ADDR 8
#define MESA_MAX_PAYLOAD 248
void mesa_write(char unsigned slot, char subslot, unsigned int addr, void *payload, int payload_size, bool repeat) {
  char cmd = repeat ? 0x2 : 0x0;

  char *data_list = payload;
  char data_payload[MESA_MAX_PAYLOAD+1];
  char str_payload[(MESA_MAX_ADDR + MESA_MAX_PAYLOAD*2) + 1];
  int data_size;

  while (payload_size > 0) {
    if (payload_size > MESA_MAX_PAYLOAD) {
      memcpy(data_payload, data_list, MESA_MAX_PAYLOAD);
      data_list += MESA_MAX_PAYLOAD;
      payload_size -= MESA_MAX_PAYLOAD;
      data_size = MESA_MAX_PAYLOAD;
    } else {
      memcpy(data_payload, data_list, payload_size);
      data_size = payload_size;
      payload_size -= MESA_MAX_PAYLOAD;
    }

    stringToHex(str_payload, 0, &addr, 4);
    stringToHex(str_payload, 8, data_payload, data_size);
    if (!repeat) {
      addr += strlen(data_payload);
    }
  }

  printf("F0%02x%01x%01x%02x%s", slot, subslot, cmd, (int)strlen(str_payload)/2, str_payload);
  mesa_send_lf();
}

void sump2_read(unsigned int addr) {
  mesa_write(0, 0, ADDR_CTRL, &addr, sizeof(addr), false);

}

int main() {
  sump2_read(CMD_RD_HW_ID_REV);
}
