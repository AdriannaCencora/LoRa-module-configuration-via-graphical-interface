#ifndef CONSTANTS_H
#define CONSTANTS_H

#endif // CONSTANTS_H


#define MODE_NORMAL 0			// can send and recieve
#define MODE_WAKEUP 1			// sends a preamble to waken receiver
#define MODE_POWER_SAVING 2		// can't transmit but receive works only in wake up mode
#define MODE_SLEEP 3			// for programming

// options to save change permanently or temp (power down and restart will restore settings to last saved options
#define PERMANENT 0xC0
#define TEMPORARY 0xC2

// parity bit options (must be the same for transmitter and reveiver)
#define PB_8N1 0b00			// default
#define PB_8O1 0b01
#define PB_8E1 0b11

//UART data rates
// (can be different for transmitter and reveiver)
#define UDR_1200 0b000		// 1200 baud
#define UDR_2400 0b001		// 2400 baud
#define UDR_4800 0b010		// 4800 baud
#define UDR_9600 0b011		// 9600 baud default
#define UDR_19200 0b100		// 19200 baud
#define UDR_38400 0b101		// 34800 baud
#define UDR_57600 0b110		// 57600 baud
#define UDR_115200 0b111	// 115200 baud


// air data rates (certian types of modules)
// (must be the same for transmitter and reveiver)
#define ADR_300 0b000		// 300 baud
#define ADR_1200 0b001		// 1200 baud
#define ADR_2400 0b010		// 2400 bauduint8_t Controller:: getMode()

#define ADR_4800 0b011		// 4800 baud
#define ADR_9600 0b100		// 9600 baud
#define ADR_19200 0b101		// 19200 baud

// CHANNEL
// first three bits are reserved (0)
// bits 4 ~0, channel (862MHz+CHAN * 1MHz), default 06H (868MHz)
// 00H-1FH, correspond to 862~893MHz
#define CHAN_0 0b0
#define CHAN_1 0b1
#define CHAN_2 0b10
#define CHAN_3 0b11
#define CHAN_4 0b100
#define CHAN_5 0b101
#define CHAN_6 0b110
#define CHAN_7 0b111
#define CHAN_8 0b1000
#define CHAN_9 0b1001
#define CHAN_10 0b1010
#define CHAN_11 0b1011
#define CHAN_12 0b1100
#define CHAN_13 0b1101
#define CHAN_14 0b1110
#define CHAN_15 0b1111
#define CHAN_16 0b11111

//Fixed transmission enabling
#define OPT_FMDISABLE 0b0
#define OPT_FMENABLE 0b1

//IO drive mode
#define OPT_IOOPENDRAIN 0b0
#define OPT_IOPUSHPULL  0b1

//Wireless wake-up time [ms]
#define OPT_WAKEUP250  0b000
#define OPT_WAKEUP500  0b001
#define OPT_WAKEUP750  0b010
#define OPT_WAKEUP1000 0b011
#define OPT_WAKEUP1250 0b100
#define OPT_WAKEUP1500 0b101
#define OPT_WAKEUP1750 0b110
#define OPT_WAKEUP2000 0b111

//FEC switch
#define OPT_FECDISABLE  0b0
#define OPT_FECENABLE 0b1

//Transmision power
#define OPT_TP30 0b00           // 30 db
#define OPT_TP27 0b01           // 27 db
#define OPT_TP24 0b10           // 24 db
#define OPT_TP21 0b11           // 21 db
