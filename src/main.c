#include <stdio.h>
#include <stddef.h>
#include <emscripten.h>
#include "Zydis/Zydis.h"

EMSCRIPTEN_KEEPALIVE
int decode_instructions(char *output, const char *data, size_t length)
{
    ZydisDecoder            decoder;
    ZydisFormatter          formatter;
    ZydisDecodedInstruction instruction;
    ZyanU64                 runtime_address     = 0x0000;
    ZyanUSize               offset              = 0;
    size_t                  pos                 = 0;

    ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64);
    ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);

    // Loop over the instructions in our buffer.
    // The runtime-address (instruction pointer) is chosen arbitrary here in order to better
    // visualize relative addressing
    while (ZYAN_SUCCESS(ZydisDecoderDecodeBuffer(&decoder, (data + offset), (length - offset), &instruction))) {
        char buffer[256];

        // Format the binary instruction structure to human readable format
        ZydisFormatterFormatInstruction(&formatter, &instruction, buffer, sizeof(buffer), runtime_address);

        // Format binary instruction with runtime address.
        pos += sprintf((output + pos), "%016llx %s\n", runtime_address, buffer);

        // Add instruction length to offset.
        offset          += instruction.length;
        runtime_address += instruction.length;
    }

    return (pos);
}
