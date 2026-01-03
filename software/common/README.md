# Common Code

Shared code between ESP32-S3 and ESP32-H2 firmware.

## Files

- `uart_protocol.h/c` - UART communication protocol between S3 and H2
- `sensor_types.h` - Common sensor data structures
- `config.h` - Shared configuration constants

## Usage

To use in ESP-IDF components, add to your component's `CMakeLists.txt`:

```cmake
idf_component_register(
    SRCS "your_source.c" "${CMAKE_SOURCE_DIR}/../common/uart_protocol.c"
    INCLUDE_DIRS "." "${CMAKE_SOURCE_DIR}/../common"
)
```

Or create a proper component in each firmware:

```cmake
# In firmware-s3/components/uart_bridge/CMakeLists.txt
idf_component_register(
    SRCS "${CMAKE_SOURCE_DIR}/../common/uart_protocol.c"
    INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/../common"
)
```
