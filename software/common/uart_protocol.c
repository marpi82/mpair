/**
 * @file uart_protocol.c
 * @brief UART communication protocol implementation
 *
 * @copyright 2026 mpair contributors
 * @license GPL-3.0
 */

#include "uart_protocol.h"

#include <string.h>

/**
 * @brief Calculate simple XOR checksum
 */
uint8_t uart_proto_calculate_checksum(const uint8_t *data, uint16_t len)
{
    uint8_t checksum = 0;
    for (uint16_t i = 0; i < len; i++) {
        checksum ^= data[i];
    }
    return checksum;
}

/**
 * @brief Verify packet checksum
 */
bool uart_proto_verify_checksum(const uart_packet_t *packet)
{
    uint16_t data_len = (packet->len >> 8) | ((packet->len & 0xFF) << 8);  // Convert from big-endian
    uint8_t calculated = uart_proto_calculate_checksum((const uint8_t *)packet, 4 + data_len);
    uint8_t received = packet->data[data_len];
    return calculated == received;
}

/**
 * @brief Build a packet in the provided buffer
 *
 * @param buffer Output buffer (must be at least data_len + 5 bytes)
 * @param cmd Command type
 * @param data Data payload
 * @param data_len Length of data
 * @return Total packet length, or -1 on error
 */
int uart_proto_build_packet(uint8_t *buffer, uint8_t cmd, const uint8_t *data, uint16_t data_len)
{
    if (data_len > UART_PROTO_MAX_DATA_LEN) {
        return -1;
    }

    // Build packet header
    buffer[0] = UART_PROTO_START_BYTE;
    buffer[1] = cmd;
    buffer[2] = (data_len >> 8) & 0xFF;  // Length high byte
    buffer[3] = data_len & 0xFF;         // Length low byte

    // Copy data
    if (data_len > 0 && data != NULL) {
        memcpy(&buffer[4], data, data_len);
    }

    // Calculate and append checksum
    uint8_t checksum = uart_proto_calculate_checksum(buffer, 4 + data_len);
    buffer[4 + data_len] = checksum;

    return 4 + data_len + 1;  // Header + data + checksum
}

/**
 * @brief Parse received data and extract packet
 *
 * @param buffer Input buffer
 * @param buffer_len Length of input buffer
 * @param packet Output pointer to packet (points into buffer)
 * @return Number of bytes consumed, 0 if incomplete, -1 on error
 */
int uart_proto_parse_packet(const uint8_t *buffer, uint16_t buffer_len, uart_packet_t **packet)
{
    // Need at least header + checksum
    if (buffer_len < 5) {
        return 0;  // Incomplete
    }

    // Check start byte
    if (buffer[0] != UART_PROTO_START_BYTE) {
        return -1;  // Invalid start byte
    }

    // Extract length
    uint16_t data_len = ((uint16_t)buffer[2] << 8) | buffer[3];

    if (data_len > UART_PROTO_MAX_DATA_LEN) {
        return -1;  // Invalid length
    }

    // Check if we have complete packet
    uint16_t total_len = 4 + data_len + 1;
    if (buffer_len < total_len) {
        return 0;  // Incomplete
    }

    // Verify checksum
    *packet = (uart_packet_t *)buffer;
    if (!uart_proto_verify_checksum(*packet)) {
        return -1;  // Checksum error
    }

    return total_len;
}
