/*
    Part of the Real-Time Embedded Systems course at Halmstad University
    Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
    All rights reserved.
*/

static const uint8_t ROW_OFFSETS[] = {0, 0x40}; //new

/* PiFace Hardware Description */

/* MCP23S17 Control Register */
#define MCP_IODIRA      0x00
#define MCP_IODIRB      0x01
#define MCP_IPOLA       0x02
#define MCP_IPOLB       0x03
#define MCP_GPINTENA    0x04
#define MCP_GPINTENB    0x05
#define MCP_DEFVALA     0x06
#define MCP_DEFVALB     0x07
#define MCP_INTCONA     0x08
#define MCP_INTCONB     0x09
#define MCP_IOCON       0x0A
#define MCP_IOCON_      0x0B
#define MCP_GPPUA       0x0C
#define MCP_GPPUB       0x0D
#define MCP_INTFA       0x0E
#define MCP_INTFB       0x0F
#define MCP_INTCAPA     0x10
#define MCP_INTCAPB     0x11
#define MCP_GPIOA       0x12
#define MCP_GPIOB       0x13
#define MCP_OLATA       0x14
#define MCP_OLATB       0x15

/* HD44780 Control Pins */
#define LCD_DB4     (1 << 0)
#define LCD_DB5     (1 << 1)
#define LCD_DB6     (1 << 2)
#define LCD_DB7     (1 << 3)
#define LCD_EN      (1 << 4)
#define LCD_RW      (1 << 5)
#define LCD_RS      (1 << 6)
#define LCD_BL      (1 << 7)