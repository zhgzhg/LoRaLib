#ifndef _LORALIB_TYPES_H
#define _LORALIB_TYPES_H

#ifdef ARDUINO
	#if ARDUINO >= 100
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif
#endif

#ifdef LINUX
	#include <inttypes.h>
	#include <stdint.h>
	#include <stddef.h>
	#include <cstring>
	#include <cmath>

	#include <string>
	#include <iostream>
	#define String std::string

	#define CHANGE 1
	#define FALLING 2
	#define RISING 3

	void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode);
	void detachInterrupt(uint8_t interruptNum);


	#ifndef DUMMY_ARDUINO_FUNCS
		#define DUMMY_ARDUINO_FUNCS
		#define digitalPinToInterrupt(p) {}
		#define max std::max
		#define ceil std::ceil

		class __FlashStringHelper;
		#define FPSTR(pstr_pointer) (reinterpret_cast<const __FlashStringHelper *>(pstr_pointer))
		#define F(string_literal) (FPSTR(PSTR(string_literal)))
		#define ICACHE_RODATA_ATTR
		#define PROGMEM ICACHE_RODATA_ATTR
		#define PGM_P const char *
		#define PGM_VOID_P const void *
		#define PSTR(s) (__extension__({static const char __c[] PROGMEM = (s); &__c[0];}))
		#define pgm_read_byte(addr)                                    \
  (__extension__({                                                     \
    PGM_P __local = (PGM_P)(addr);  /* isolate varible for macro expansion */\
    ptrdiff_t __offset = (reinterpret_cast<uint32_t>(__local) & 0x00000003); /* byte aligned mask */\
    const uint32_t* __addr32 = (const uint32_t*)((const uint8_t*)(__local)-__offset); \
    uint8_t __result = ((*__addr32) >> (__offset * 8));                        \
    __result;                                                                  \
}))
	#endif

#endif

//#define RADIOLIB_DEBUG

#ifdef RADIOLIB_DEBUG
  #ifndef LINUX
    #define DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }
    #define DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }
  #else
     void DEBUG_PRINT() { }
     void DEBUG_PRINTLN() { std::cerr << std::endl; }

     template <typename First, typename... Rest>
     void DEBUG_PRINT(First&& first, Rest&& rest)
     {
         std::cerr << std::forward<First>(first);
         DEBUG_PRINT(std::forward<Rest>(rest)...);
     }

     template <typename First, typename... Rest>
     void DEBUG_PRINTLN(First&& first, Rest&& rest)
     {
         std::cerr << std::forward<First>(first);
         DEBUG_PRINTLN(std::forward<Rest>(rest)...);
     }
  #endif
#else
  #define DEBUG_PRINT(...) {}
  #define DEBUG_PRINTLN(...) {}
#endif

// Shield configuration
#define USE_SPI                               0x00
#define USE_UART                              0x01
#define USE_I2C                               0x02
#define INT_NONE                              0x00
#define INT_0                                 0x01
#define INT_1                                 0x02
#define INT_BOTH                              0x03

// Status/error codes

/*!
  \defgroup status_codes Status Codes

  \{
*/

/*!
  \brief No error, method executed successfully.
*/
#define ERR_NONE                               0

/*!
  \brief There was an unexpected, unknown error. If you see this, something went incredibly wrong.
  Your Arduino may be possessed, contact your local exorcist to resolve this error.
*/
#define ERR_UNKNOWN                           -1

/*!
  \brief %SX127x chip was not found during initialization. This can be caused by specifying wrong chip type in the constructor
  (i.e. calling SX1272 constructor for SX1278 chip) or by a fault in your wiring (incorrect slave select pin).
*/
#define ERR_CHIP_NOT_FOUND                    -2

/*!
  \brief Deprecated.
*/
#define ERR_EEPROM_NOT_INITIALIZED            -3

/*!
  \brief Packet supplied to transmission method was longer than 255 bytes.
  %SX127x chips can not send more than 255 bytes in a single %LoRa transmission.
  Length limit is reduced to 63 bytes for FSK transmissions.
*/
#define ERR_PACKET_TOO_LONG                   -4

/*!
  \brief Timed out waiting for TxDone signal from %SX127x. This error can be caused by faulty wiring (unreliable connection at DIO0).
*/
#define ERR_TX_TIMEOUT                        -5

/*!
  \brief No packet arrived within a timeframe.
*/
#define ERR_RX_TIMEOUT                        -6

/*!
  \brief The calculated and expected CRCs of received packet do not match.
  This means that the packet was damaged during transmission and should be sent again.
*/
#define ERR_CRC_MISMATCH                      -7

/*!
  \brief The supplied bandwidth value is invalid for this module.
*/
#define ERR_INVALID_BANDWIDTH                 -8

/*!
  \brief The supplied spreading factor value is invalid for this module.
*/
#define ERR_INVALID_SPREADING_FACTOR          -9

/*!
  \brief The supplied coding rate value is invalid.
*/
#define ERR_INVALID_CODING_RATE               -10

/*!
  \brief Internal only.
*/
#define ERR_INVALID_BIT_RANGE                 -11

/*!
  \brief The supplied frequency value is invalid for this module.
*/
#define ERR_INVALID_FREQUENCY                 -12

/*!
  \brief The supplied output power is invalid.
*/
#define ERR_INVALID_OUTPUT_POWER              -13

/*!
  \brief %LoRa preamble was detected during channel activity detection.
  This means that there is some %LoRa device currently transmitting in your channel.
*/
#define PREAMBLE_DETECTED                     -14

/*!
  \brief No %LoRa preambles were detected during channel activity detection. Your channel is free.
*/
#define CHANNEL_FREE                          -15

/*!
  \brief Real value in SPI register does not match the expected one. This can be caused by faulty SPI wiring.
*/
#define ERR_SPI_WRITE_FAILED                  -16

/*!
  \brief The supplied current limit value is invalid.
*/
#define ERR_INVALID_CURRENT_LIMIT             -17

/*!
  \brief The supplied preamble length is invalid.
*/
#define ERR_INVALID_PREAMBLE_LENGTH           -18

/*!
  \brief The supplied gain value is invalid.
*/
#define ERR_INVALID_GAIN                      -19

/*!
  \brief User tried to execute modem-exclusive method on a wrong modem.
  For example, this can happen when you try to change %LoRa configuration when FSK modem is active.
*/
#define ERR_WRONG_MODEM                       -20

/*!
  \brief The supplied bit rate value is invalid.
*/
#define ERR_INVALID_BIT_RATE                  -21

/*!
  \brief The supplied receiver bandwidth value is invalid.
*/
#define ERR_INVALID_RX_BANDWIDTH              -22

/*!
  \brief The supplied frequency deviation value is invalid.
*/
#define ERR_INVALID_FREQUENCY_DEVIATION       -23

/*!
  \brief The supplied FSK sync word is invalid. The sync word is either longer than 8 bytes or contains null-bytes.
*/
#define ERR_INVALID_SYNC_WORD                 -24

/*!
  \brief The supplied FSK data shaping option is invalid.
*/
#define ERR_INVALID_DATA_SHAPING              -25

/*!
  \brief The current modulation is invalid for the requested operation.
*/
#define ERR_INVALID_MODULATION                -26

/*!
  \}
*/

#endif
