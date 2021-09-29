#include "include/Zydis.h"

int decode_instructions(const char *ptr, size_t length)
{
    ZydisDecoder            decoder;
    ZydiFormatter           formatter;
    ZydisDecodedInstruction instruction;
    ZyanU64                 runtime_address     = 0x0000;
    ZyanUSize               offset              = 0;

    ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64);
    ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);

    // Loop over the instructions in our buffer.
    // The runtime-address (instruction pointer) is chosen arbitrary here in order to better
    // visualize relative addressing
    while (ZYAN_SUCCESS(ZydisDecoderDecodeBuffer(&decoder, (data + offset), (length - offset), &instruction))) {
        char buffer[256];

        // Print current instruction pointer.
        printf("%016" PRIX64 "  ", runtime_address);

        // Format & print the binary instruction structure to human readable format
        ZydisFormatterFormatInstruction(&formatter, &instruction, buffer, sizeof(buffer), runtime_address);
        puts(buffer);

        offset          += instruction.length;
        runtime_address += instruction.length;
    }
}
