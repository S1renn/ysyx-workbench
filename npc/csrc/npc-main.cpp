#include "Vtop.h"
#include "verilated.h"
#include <stdio.h>
//#include "verilated_vcd_c.h"
#include "svdpi.h"
#include "Vtop__Dpi.h"
#include <sys/time.h>
#include <string.h>


// 1. 定义内存
#define MEM_SIZE (64 * 1024 * 1024) // 64 MB
#define MEM_BASE 0x80000000
#define DEVICE_BASE 0xa0000000
#define RTC_ADDR (DEVICE_BASE + 0x00000048)
#define VGACTL_ADDR (DEVICE_BASE + 0x0000100)
#define SERIAL_PORT (0x10000000)

void init_sim(int argc, char** argv);
void sdb_mainloop(bool batch);

int main(int argc, char *argv[]) {


    init_sim(argc, argv);
    
    bool batch = argc > 4 && strcmp(argv[4], "-b") == 0;
    sdb_mainloop(batch);



    return 0;
}
