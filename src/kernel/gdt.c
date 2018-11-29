#include "gdt.h"
#include "constants.h"

/**********************************************************
* Private kernel variables declaration                    *
**********************************************************/

struct gdtdesc 	gdtd[GDT_NUM_ENTRIES];
struct gdt      gdt;

/**********************************************************
* Private kernel functions declaration                    *
**********************************************************/

/** gdt_create_entry:
 * Initialize a segment descriptor in gdt.
 */
void gdt_create_entry(unsigned int n, unsigned char pl, unsigned char type);

/**********************************************************
* Private kernel function                                 *
**********************************************************/

void gdt_create_entry(unsigned int n, unsigned char pl, unsigned char type)
{
    gdtd[n].base_low     = (SEGMENT_BASE & 0xFFFF);
    gdtd[n].base_mid     = (SEGMENT_BASE >> 16) & 0xFF;
    gdtd[n].base_high    = (SEGMENT_BASE >> 24) & 0xFF;

    gdtd[n].limit_low    = (SEGMENT_LIMIT & 0xFFFF);

    /*
     * name | value | size | desc
     * ---------------------------
     * G    |     1 |    1 | granularity, size of segment unit, 1 = 4kB
     * D/B  |     1 |    1 | size of operation size, 0 = 16 bits, 1 = 32 bits
     * L    |     0 |    1 | 1 = 64 bit code
     * AVL  |     0 |    1 | "available for use by system software"
     * LIM  |   0xF |    4 | the four highest bits of segment limit
     */
    gdtd[n].granularity  |= (0x01 << 7) | (0x01 << 6) | 0x0F;

    /*
     * name | value | size | desc
     * ---------------------------
     * P    |     1 |    1 | segment present in memory
     * DPL  |    pl |    2 | privilege level
     * S    |     1 |    1 | descriptor type, 0 = system, 1 = code or data
     * Type |  type |    4 | segment type, how the segment can be accessed
     */
    gdtd[n].access =
        (0x01 << 7) | ((pl & 0x03) << 5) | (0x01 << 4) | (type & 0x0F);
}


/**********************************************************
* Public kernel API function                              *
**********************************************************/

void initialize_gdt()
{
    gdt.limit   = sizeof(struct gdtdesc)*GDT_NUM_ENTRIES;
    gdt.base    = (unsigned int)&gdtd;

    /* the null entry */
    gdt_create_entry(0, 0, 0);
    /* kernel mode code segment */
    gdt_create_entry(1, PL0, CODE_RX_TYPE);
    /* kernel mode data segment */
    gdt_create_entry(2, PL0, DATA_RW_TYPE);
    /* user mode code segment */
    gdt_create_entry(3, PL3, CODE_RX_TYPE);
    /* user mode data segment */
    gdt_create_entry(4, PL3, DATA_RW_TYPE);

    load_gdt(&gdt);
}
