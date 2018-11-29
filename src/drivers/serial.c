#include "serial.h"

/**********************************************************
 * Private Kernel functions declaration                   *
 **********************************************************/

/** serial_configure_baud_rate:
*  Sets the speed of the data being sent. The default speed of a serial
*  port is 115200 bits/s. The argument is a divisor of that number, hence
*  the resulting speed becomes (115200 / divisor) bits/s.
*
*  @param com      The COM port to configure
*  @param divisor  The divisor
*/
void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

/** serial_configure_line:
 *  Configures the line of the given serial port. The port is set to have a
 *  data length of 8 bits, no parity bits, one stop bit and break control
 *  disabled.
 *
 *  @param com  The serial port to configure
 */
void serial_configure_line(unsigned short com);

/** serial_configure_buffer:
 *  Configures the buffer of the given serial port. The bufffer is set to
 *  enable FIFO, clear both receiver and transmission FIFO queues and use
 *  14 bytes as size of queue.
 *
 *  @param com  The serial port to configure
 */
void serial_configure_buffer(unsigned short com);

/** serial_configure_modem:
 *  Configures the modem control register of the given serial port.
 *  Don't need to enable interrupts (no handle of received data)
 *  Just set ready to transmit and data terminal ready bits (only send)
 *
 *  @param com  The serial port to configure
 */
void serial_configure_modem(unsigned short com);

/** serial_is_transmit_fifo_empty:
 *  Checks whether the transmit FIFO queue is empty or not for the given COM
 *  port.
 *
 *  @param  com The COM port
 *  @return 0 if the transmit FIFO queue is not empty
 *          1 if the transmit FIFO queue is empty
 */
int serial_is_transmit_fifo_empty(unsigned short com);

/** serial_write_data:
 *  Write data to the serial port
 *
 *  @param  com The COM port
 *  @param  data   The data to be sent
 */
void serial_write_data(unsigned short com, char *data);

/**********************************************************
 * Private Kernel functions variable                      *
 **********************************************************/

static unsigned short serial_port = SERIAL_COM1_BASE;

/**********************************************************
 * Public Kernel API function                             *
 **********************************************************/

void set_serial_port(unsigned short port)
{
  serial_port = port;
}

void initialize_serial_logging()
{
  serial_configure_baud_rate(serial_port, 3);
  serial_configure_line(serial_port);
  serial_configure_buffer(serial_port);
  serial_configure_modem(serial_port);
}

void log(log_severity severity, char *message)
{
    if (severity == DEBUG)
      serial_write_data(serial_port, "[DEBUG]: ");
    else if (severity == INFO)
      serial_write_data(serial_port, "[INFO]: ");
    else
      serial_write_data(serial_port, "[ERROR]: ");
    serial_write_data(serial_port, message);
}

/**********************************************************
 * Private Kernel functions                               *
 **********************************************************/

void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
  outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
  outb(SERIAL_DATA_PORT_HIGH(com), (divisor >> 8) & 0x00FF);
  outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

void serial_configure_line(unsigned short com)
{
  /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
   * Content: | d | b | prty  | s | dl  |
   * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
   */
   outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_configure_buffer(unsigned short com)
{
  /* Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
   * Content: | lvl | bs | r | dma | clt | clr | e |
   * Value:   | 1 1 | 0  | 0 | 0   | 1   | 1   | 1 | = 0xC7
   */
   outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

void serial_configure_modem(unsigned short com)
{
  /* Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
   * Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
   * Value:   | 0 | 0 | 0  | 0  | 0   | 0   | 1   | 1   | = 0x03
   */
   outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

int serial_is_transmit_fifo_empty(unsigned short com)
{
    /* 0x20 = 0010 0000 */
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void serial_write_data(unsigned short com, char *data)
{
  int i = 0;

  while (data[i])
  {
    while (!serial_is_transmit_fifo_empty(com));
    outb(SERIAL_DATA_PORT(serial_port), data[i]);
    i++;
  }
}
