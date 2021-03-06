#ifndef _LORALIB_TYPES_H
#define _LORALIB_TYPES_H

#ifdef ARDUINO
	#if ARDUINO >= 100
		#include "Arduino.h"
	#else
  		#error "Unsupported Arduino version (< 1.0.0)"
	#endif
#endif

/*
 * Platform-specific configuration.
 *
 * RADIOLIB_PIN_TYPE - which type should be used for pin numbers in functions like digitalRead().
 * RADIOLIB_PIN_MODE - which type should be used for pin modes in functions like pinMode().
 * RADIOLIB_PIN_STATUS - which type should be used for pin values in functions like digitalWrite().
 * RADIOLIB_NC - alias for unused pin, usually the largest possible value of RADIOLIB_PIN_TYPE.
 * RADIOLIB_SOFTWARE_SERIAL_UNSUPPORTED - defined if the specific platform does not support SoftwareSerial.
 * RADIOLIB_HARDWARE_SERIAL_PORT - which hardware serial port should be used on platform that do not have SoftwareSerial support.
 *
 * In addition, some platforms may require RadioLib to disable specific drivers (such as ESP8266).
 */
#if defined(__AVR__) && !(defined(ARDUINO_AVR_UNO_WIFI_REV2) || defined(ARDUINO_AVR_NANO_EVERY))
   // Arduino AVR boards (except for megaAVR) - Uno, Mega etc.
   #define RADIOLIB_PIN_TYPE                          uint8_t
   #define RADIOLIB_PIN_MODE                          uint8_t
   #define RADIOLIB_PIN_STATUS                        uint8_t
   #define RADIOLIB_NC                                (0xFF)

#elif defined(ESP8266)
   // ESP8266 boards
   #define RADIOLIB_PIN_TYPE                          uint8_t
   #define RADIOLIB_PIN_MODE                          uint8_t
   #define RADIOLIB_PIN_STATUS                        uint8_t
   #define RADIOLIB_NC                                (0xFF)

   // RadioLib has ESPS8266 driver, this must be disabled to use ESP8266 as platform
   #define _RADIOLIB_ESP8266_H

#elif defined(ESP32)
  // ESP32 boards
  #define RADIOLIB_PIN_TYPE                           uint8_t
  #define RADIOLIB_PIN_MODE                           uint8_t
  #define RADIOLIB_PIN_STATUS                         uint8_t
  #define RADIOLIB_NC                                 (0xFF)
  #define RADIOLIB_SOFTWARE_SERIAL_UNSUPPORTED
  #define RADIOLIB_HARDWARE_SERIAL_PORT               Serial1

#elif defined(ARDUINO_ARCH_STM32)
  // STM32duino boards
  #define RADIOLIB_PIN_TYPE                           uint32_t
  #define RADIOLIB_PIN_MODE                           uint32_t
  #define RADIOLIB_PIN_STATUS                         uint32_t
  #define RADIOLIB_NC                                 (0xFFFFFFFF)
  #define RADIOLIB_SOFTWARE_SERIAL_UNSUPPORTED
  #define RADIOLIB_HARDWARE_SERIAL_PORT               Serial1

#elif defined(SAMD_SERIES)
  // Arduino SAMD boards - Zero, MKR, etc.
  #define RADIOLIB_PIN_TYPE                           uint32_t
  #define RADIOLIB_PIN_MODE                           uint32_t
  #define RADIOLIB_PIN_STATUS                         uint32_t
  #define RADIOLIB_NC                                 (0xFFFFFFFF)
  #define RADIOLIB_SOFTWARE_SERIAL_UNSUPPORTED
  #define RADIOLIB_HARDWARE_SERIAL_PORT               Serial1

#elif defined(__SAM3X8E__)
  // Arduino Due
  #define RADIOLIB_PIN_TYPE                           uint32_t
  #define RADIOLIB_PIN_MODE                           uint32_t
  #define RADIOLIB_PIN_STATUS                         uint32_t
  #define RADIOLIB_NC                                 (0xFFFFFFFF)
  #define RADIOLIB_SOFTWARE_SERIAL_UNSUPPORTED
  #define RADIOLIB_HARDWARE_SERIAL_PORT               Serial1

#elif (defined(NRF52832_XXAA) || defined(NRF52840_XXAA)) && !defined(ARDUINO_ARDUINO_NANO33BLE)
  // Adafruit nRF52 boards
  #define RADIOLIB_PIN_TYPE                           uint32_t
  #define RADIOLIB_PIN_MODE                           uint32_t
  #define RADIOLIB_PIN_STATUS                         uint32_t
  #define RADIOLIB_NC                                 (0xFFFFFFFF)

#elif defined(ARDUINO_ARC32_TOOLS)
  // Intel Curie
  #define RADIOLIB_PIN_TYPE                           uint8_t
  #define RADIOLIB_PIN_MODE                           uint8_t
  #define RADIOLIB_PIN_STATUS                         uint8_t
  #define RADIOLIB_NC                                 (0xFF)

#elif defined(ARDUINO_AVR_UNO_WIFI_REV2) || defined(ARDUINO_AVR_NANO_EVERY)
  // Arduino megaAVR boards - Uno Wifi Rev.2, Nano Every
  #define RADIOLIB_PIN_TYPE                           uint8_t
  #define RADIOLIB_PIN_MODE                           PinMode
  #define RADIOLIB_PIN_STATUS                         PinStatus
  #define RADIOLIB_NC                                 (0xFF)

#elif defined(AM_PART_APOLLO3)
  // Sparkfun Artemis boards
  #define RADIOLIB_PIN_TYPE                           uint8_t
  #define RADIOLIB_PIN_MODE                           uint8_t
  #define RADIOLIB_PIN_STATUS                         uint8_t
  #define RADIOLIB_NC                                 (0xFF)
  #define RADIOLIB_SOFTWARE_SERIAL_UNSUPPORTED
  #define RADIOLIB_HARDWARE_SERIAL_PORT               Serial1

#elif defined(ARDUINO_ARDUINO_NANO33BLE)
  // Arduino Nano 33 BLE
  #define RADIOLIB_PIN_TYPE                           pin_size_t
  #define RADIOLIB_PIN_MODE                           PinMode
  #define RADIOLIB_PIN_STATUS                         PinStatus
  #define RADIOLIB_NC                                 (0xFF)
  #define RADIOLIB_SOFTWARE_SERIAL_UNSUPPORTED
  #define RADIOLIB_HARDWARE_SERIAL_PORT               Serial1

  // Nano 33 BLE uses mbed libraries, which already contain ESP8266 driver
  #define _RADIOLIB_ESP8266_H

#elif defined (LINUX)
  // Linux pseudo-definitions, for Armbian/Raspbian/etc.
  #define RADIOLIB_PIN_TYPE                           uint32_t
  #define RADIOLIB_PIN_MODE                           uint32_t
  #define RADIOLIB_PIN_STATUS                         uint32_t
  #define RADIOLIB_NC                                 (0xFFFFFFFF)
  #define RADIOLIB_SOFTWARE_SERIAL_UNSUPPORTED
  #define RADIOLIB_HARDWARE_SERIAL_PORT               Serial1


#else
  // other platforms not covered by the above list - this may or may not work
  #define RADIOLIB_UNKNOWN_PLATFORM
  #define RADIOLIB_PIN_TYPE                           uint8_t
  #define RADIOLIB_PIN_MODE                           uint8_t
  #define RADIOLIB_PIN_STATUS                         uint8_t
  #define RADIOLIB_NC                                 (0xFF)

#endif


#ifdef LINUX
	#include <inttypes.h>
	#include <stdint.h>
	#include <stddef.h>
	#include <cstring>
	#include <cmath>

	#include <string>
	#include <iostream>
	#include <iomanip>
	#include <limits>
	#include <locale>

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
		//#define F(string_literal) (string_literal)
		#define ICACHE_RODATA_ATTR
		#define PROGMEM ICACHE_RODATA_ATTR
		#define PGM_P const char *
		#define PGM_VOID_P const void *
		#define PSTR(s) (__extension__({static const char __c[] PROGMEM = (s); &__c[0];}))
		#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
		#define yield() (delay(1))

		typedef std::ios_base& (*mock_manipulator)(std::ios_base&);

		#define HEX std::hex
		#define DEC std::dec
		#define OCT std::oct

		#define is_char_type(T) ( std::is_same<T, char>::value || \
			std::is_same<T, unsigned char>::value || std::is_same<T, uint8_t>::value || \
			std::is_same<T, int8_t>::value || std::is_same<T, wchar_t>::value || \
			std::is_same<T, char16_t>::value || std::is_same<T, char32_t>::value )

		template <typename _T>
		struct _binary { std::string _digits; };

		template <typename T>
		constexpr auto _mypow(T b, unsigned int e ) -> decltype(b + 1)
		{ return e ? b * _mypow( b, e - 1 ) : 1 ; }

		template <typename T>
		inline _binary<T> binary(T n) {
			_binary<T> __binary;
			constexpr int bits = _mypow(8U, sizeof(n)) - 1;

			for (int i = bits; i >= 0; --i) {
				if ((n >> i) & 1) __binary._digits.append(1, '1');
				else __binary._digits.append(1, '0');
			}

			return __binary;
		}

		template <typename T>
		inline std::ostream& operator<<(std::ostream& stream, _binary<T> __binary) {
			stream << __binary._digits;
			return stream;
		}

		struct _BIN {};

		class MockDebugSerial {
		public:
			operator bool() { return true; }

			template <typename SPD, typename CFG=int>
			void begin(SPD speed, CFG config={}) { }
			void end() { }

			void print() { }
			void println() { std::cerr << std::endl; }

			template <typename NI>
			void print(NI number, mock_manipulator mm) {
				static_assert(std::is_integral<NI>::value, "Integral required.");
				typename std::conditional<is_char_type(NI), unsigned long, NI>::type _number = number;
				std::cerr << mm << _number;
			}
			template <typename NI>
			void println(NI number, mock_manipulator mm) {
				static_assert(std::is_integral<NI>::value, "Integral required.");
				print(number, mm);
				println();
			}

			template <typename NI>
			void print(NI number, struct _BIN mm) {
				static_assert(std::is_integral<NI>::value, "Integral required.");
				std::cerr << binary(number);
			}
			template <typename NI>
			void println(NI number, struct _BIN mm) {
				static_assert(std::is_integral<NI>::value, "Integral required.");
				print(number, mm);
				println();
			}

			template <typename ND>
			void print(ND number, int precision) {
				static_assert(std::is_floating_point<ND>::value, "Floating-point required.");
				std::cerr << std::setprecision(precision) << number;
			}

			template <typename ND>
			void println(ND number, int precision) {
				static_assert(std::is_floating_point<ND>::value, "Floating-point required.");
				print(number, precision);
				println();
			}

			template <typename First, typename... Rest>
			void print(First&& first, Rest&&... rest) {
				using MYTYPE = typename std::conditional< \
					std::is_same<const __FlashStringHelper*, First>::value, const char*, First>::type;
				MYTYPE _first = reinterpret_cast<MYTYPE>(first);

				std::cerr << std::forward<MYTYPE>(_first);
				print(std::forward<Rest>(rest)...);
			}

			template <typename First, typename... Rest>
			void println(First&& first, Rest&&... rest) {
				using MYTYPE = typename std::conditional< \
					std::is_same<const __FlashStringHelper*, First>::value, const char*, First>::type;
				MYTYPE _first = reinterpret_cast<MYTYPE>(first);

				std::cerr << std::forward<MYTYPE>(_first);
				println(std::forward<Rest>(rest)...);
			}

		};
		extern _BIN BIN;
		extern MockDebugSerial Serial;

	#endif

#endif

/*
 * Uncomment to enable debug output.
 * Warning: Debug output will slow down the whole system significantly.
 *          Also, it will result in larger compiled binary.
 * Levels: debug - only main info
 *         verbose - full transcript of all SPI/UART communication
 */

//#define RADIOLIB_DEBUG
//#define RADIOLIB_VERBOSE

// set which Serial port should be used for debug output
#define RADIOLIB_DEBUG_PORT   Serial

#ifdef RADIOLIB_DEBUG
  #define RADIOLIB_DEBUG_PRINT(...) { RADIOLIB_DEBUG_PORT.print(__VA_ARGS__); }
  #define RADIOLIB_DEBUG_PRINTLN(...) { RADIOLIB_DEBUG_PORT.println(__VA_ARGS__); }
#else
  #define RADIOLIB_DEBUG_PRINT(...) {}
  #define RADIOLIB_DEBUG_PRINTLN(...) {}
#endif

#ifdef RADIOLIB_VERBOSE
  #define RADIOLIB_VERBOSE_PRINT(...) { RADIOLIB_DEBUG_PORT.print(__VA_ARGS__); }
  #define RADIOLIB_VERBOSE_PRINTLN(...) { RADIOLIB_DEBUG_PORT.println(__VA_ARGS__); }
#else
  #define RADIOLIB_VERBOSE_PRINT(...) {}
  #define RADIOLIB_VERBOSE_PRINTLN(...) {}
#endif

/*
 * Uncomment to enable god mode - all methods and member variables in all classes will be made public, thus making them accessible from Arduino code.
 * Warning: Come on, it's called GOD mode - obviously only use this if you know what you're doing.
 *          Failure to heed the above warning may result in bricked module.
 */
//#define RADIOLIB_GODMODE

// set the size of static arrays to use
#define RADIOLIB_STATIC_ARRAY_SIZE   256

/*!
  \brief A simple assert macro, will return on error.
*/
#define RADIOLIB_ASSERT(STATEVAR) { if((STATEVAR) != ERR_NONE) { return(STATEVAR); } }

/*!
  \brief Macro to check variable is within constraints - this is commonly used to check parameter ranges.
*/
#define RADIOLIB_CHECK_RANGE(VAR, MIN, MAX, ERR) { if(!(((VAR) >= (MIN)) && ((VAR) <= (MAX)))) { return(ERR); } }


// Shield configuration
#define RADIOLIB_USE_SPI                      0x00
#define RADIOLIB_USE_UART                     0x01
#define RADIOLIB_USE_I2C                      0x02
#define RADIOLIB_INT_NONE                     0x00
#define RADIOLIB_INT_0                        0x01
#define RADIOLIB_INT_1                        0x02
#define RADIOLIB_INT_BOTH                     0x03

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
  \brief Failed to allocate memory for temporary buffer. This can be cause by not enough RAM or by passing invalid pointer.
*/
#define ERR_MEMORY_ALLOCATION_FAILED          -3

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
  \brief The supplied number of RSSI samples is invalid.
*/
#define ERR_INVALID_NUM_SAMPLES               -27

/*!
  \brief The supplied RSSI offset is invalid.
*/
#define ERR_INVALID_RSSI_OFFSET               -28

/*!
  \brief The supplied encoding is invalid.
*/
#define ERR_INVALID_ENCODING                  -29

/*!
  \}
*/

#endif

