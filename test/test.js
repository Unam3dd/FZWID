let decoder  = new TextDecoder();
let memory   = new Uint8Array(wasmMemory.buffer)
let binary   = new Uint8Array([
    0x51, 0x8D, 0x45, 0xFF, 0x50, 0xFF, 0x75, 0x0C, 0xFF, 0x75,
    0x08, 0xFF, 0x15, 0xA0, 0xA5, 0x48, 0x76, 0x85, 0xC0, 0x0F,
    0x88, 0xFC, 0xDA, 0x02, 0x00
]);

// Set binary at position 1000.
memory.set(binary, 100000);

// Decode instructions and save result at 2000.
let length = Module._decode_instructions(200000, 100000, binary.length);

// Decode result string.
let decoded = decoder.decode(memory.slice(200000, (200000 + length)));

// Print result.
console.log(length)
console.log(decoded);
