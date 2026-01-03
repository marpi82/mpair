/**
 * @file uart_protocol.h
 * @brief UART communication protocol between ESP32-S3 and ESP32-H2
 * 
 * Simple packet-based protocol for bidirectional communication.
 * 
 * Packet format:
 * [START_BYTE][CMD][LEN_H][LEN_L][DATA...][CHECKSUM]
 * 
 * @copyright 2026 mpair contributors
 * @license GPL-3.0
 */

#ifndef UART_PROTOCOL_H
#define UART_PROTOCOL_H

#include <stdint.h>
#include <stdbool.h>

// Protocol constants
#define UART_PROTO_START_BYTE       0xA5
#define UART_PROTO_MAX_DATA_LEN     256

// Command types
typedef enum {
    // S3 → H2: Sensor data updates
    UART_CMD_SENSOR_DATA        = 0x01,
    UART_CMD_PM_DATA            = 0x02,
    UART_CMD_CO2_DATA           = 0x03,
    UART_CMD_TEMP_HUM_DATA      = 0x04,
    UART_CMD_PRESSURE_DATA      = 0x05,
    
    // H2 → S3: Matter commands
    UART_CMD_MATTER_CMD         = 0x10,
    UART_CMD_SET_LED            = 0x11,
    UART_CMD_SET_HEATER         = 0x12,
    
    // Bidirectional: Status and control
    UART_CMD_STATUS_REQ         = 0x20,
    UART_CMD_STATUS_RSP         = 0x21,
    UART_CMD_PING               = 0x30,
    UART_CMD_PONG               = 0x31,
    
    // Errors
    UART_CMD_ERROR              = 0xFF,
} uart_cmd_t;

// Packet structure
typedef struct __attribute__((packed)) {
    uint8_t start;          // UART_PROTO_START_BYTE
    uint8_t cmd;            // Command type
    uint16_t len;           // Data length (big-endian)
    uint8_t data[];         // Variable length data + checksum
} uart_packet_t;

// Sensor data structures
typedef struct __attribute__((packed)) {
    float pm1_0;
    float pm2_5;
    float pm4_0;
    float pm10;
} pm_data_t;

typedef struct __attribute__((packed)) {
    uint16_t co2_ppm;
} co2_data_t;

typedef struct __attribute__((packed)) {
    float temperature;
    float humidity;
} temp_hum_data_t;

typedef struct __attribute__((packed)) {
    float pressure;
} pressure_data_t;

// Function prototypes
uint8_t uart_proto_calculate_checksum(const uint8_t *data, uint16_t len);
bool uart_proto_verify_checksum(const uart_packet_t *packet);
int uart_proto_build_packet(uint8_t *buffer, uint8_t cmd, const uint8_t *data, uint16_t data_len);
int uart_proto_parse_packet(const uint8_t *buffer, uint16_t buffer_len, uart_packet_t **packet);

#endif // UART_PROTOCOL_H
