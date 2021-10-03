#include <stdint.h>
#include <stddef.h>
#include <elf.h>

////////////////////////////////////
//
//      STRUCT
//
////////////////////////////////////

typedef struct elf_parser_x64_t elf_parser_x64_t;
typedef struct elf_parser_x86_t elf_parser_x86_t;

struct elf_parser_x64_t
{
    Elf64_Ehdr *elf_hdr;
    Elf64_Phdr *program_hdr;
    Elf64_Shdr *section_hdr;
    Elf64_Sym *symbol;
    char *str_tab;
};

struct elf_parser_x86_t
{
    Elf32_Ehdr *elf_hdr;
    Elf32_Phdr *program_hdr;
    Elf32_Shdr *section_hdr;
    Elf32_Sym *symbol;
    char *str_tab;
};

////////////////////////////////////
//
//      PARSER
//
////////////////////////////////////

// parser.c

int parse_elf_x64(elf_parser_x64_t *elf_data, char *data);
int parse_elf_x86(elf_parser_x86_t *elf_data, char *data);
int check_format(unsigned char *magic);
size_t elf_get_section_x86(elf_parser_x86_t *elf_data, char *data, char *name, char **addr);
size_t elf_get_section_x64(elf_parser_x64_t *elf_data, char *data, char *name, char **addr);
