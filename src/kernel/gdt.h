#ifndef GDT_H
# define GDT_H

# define SEGMENT_BASE    0
# define SEGMENT_LIMIT   0xFFFFF

# define CODE_RX_TYPE   0xA
# define DATA_RW_TYPE   0x2

# define GDT_NUM_ENTRIES 5

struct gdt {
    unsigned short limit;
    unsigned int   base;
} __attribute__((packed));

struct gdtdesc {
    unsigned short limit_low;     /* The lower 16 bits of the limit */
    unsigned short base_low;      /* The lower 16 bits of the base */
    unsigned char  base_mid;      /* The next 8 bits of the base */
    unsigned char  access;        /* Contains access flags */
    unsigned char  granularity;   /* Specify granularity, and 4 bits of limit */
    unsigned char  base_high; /* The last 8 bits of the base; */
} __attribute__ ((packed));

/** initilize_gdt:
 * Initialize the global descriptor table
 */
void initialize_gdt(void);

/** load_gdt:
*  Load the global descriptor table into the processor
*
*  @param gdt The pointer on the gdt structure
*/
void load_gdt(struct gdt *gdt);

#endif // !GDT_H
