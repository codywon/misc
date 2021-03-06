#include <stdio.h>
#include <string.h>
#include <ftdi.h>
 
int main() {
  struct ftdi_context ftdic;
  ftdi_init(&ftdic);
  uint8_t data[256];
  uint8_t data2[256];
 
  if(ftdi_usb_open_desc(&ftdic, 0x0403, 0x6001, NULL, NULL) < 0) {
    fprintf(stderr, "ftdi_usb_open_desc failed: %s\n", 
      ftdi_get_error_string(&ftdic));
    exit(1);
  }
 

  if(ftdi_set_bitmode(&ftdic, 0xff, BITMODE_SYNCBB) < 0) {
    fprintf(stderr, "ftdi_set_bitmode failed: %s\n", 
      ftdi_get_error_string(&ftdic));
    exit(1);
  }
 
  if(ftdi_set_baudrate(&ftdic, 4096) < 0) {
    fprintf(stderr, "ftdi_set_baudrate failed: %s\n", 
      ftdi_get_error_string(&ftdic));
    exit(1);
  }

  for(int i=0; i<sizeof(data); i++) {
      data[i] = (uint8_t ) i & 0xff;
  }
 
  for(;;) {
    ftdi_write_data(&ftdic, data, sizeof(data));
    ftdi_read_data(&ftdic, data2, sizeof(data2));
  }
 
  return 0;
}
