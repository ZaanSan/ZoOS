#ifndef SERIAL_H
# define SERIAL_H

# include "io.h"

/* The I/O ports */

/* All the I/O ports are calculated relative to the data port. This is because
 * all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
 * order, but they start at different values.
 */

# define SERIAL_COM1_BASE                0x3F8      /* COM1 base port */

# define SERIAL_DATA_PORT(base)          (base)
# define SERIAL_DATA_PORT_HIGH(base)     (base + 1)
# define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
# define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
# define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
# define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

/* The I/O port commands */

/* SERIAL_LINE_ENABLE_DLAB:
 * Tells the serial port to expect first the highest 8 bits on the data port,
 * then the lowest 8 bits will follow
 */
# define SERIAL_LINE_ENABLE_DLAB         0x80

/**********************************************************
 * Public Kernel API                                      *
 **********************************************************/

/* Log severity */
typedef enum log_severity
{
  DEBUG = 0,
  INFO = 1,
  ERROR = 2
} log_severity;

/**********************************************************
 * Public Kernel API functions                            *
 **********************************************************/

void set_serial_port(unsigned short com);

void initialize_serial_logging();

void log(log_severity severity, char *message);


#endif // !SERIAL_H
