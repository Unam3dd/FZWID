#include "elf_parser.h"
#include <stddef.h>
#include <string.h>
#include <emscripten.h>

////////////////////////////////////
//
//      PARSER
//
////////////////////////////////////

EMSCRIPTEN_KEEPALIVE
int parse_elf_x64(elf_parser_x64_t *elf_data, char *data)
{
    elf_data->elf_hdr = (Elf64_Ehdr *) (data);

    if (check_format(elf_data->elf_hdr->e_ident))
        return (1);

    if (elf_data->elf_hdr->e_ident[EI_CLASS] == ELFCLASS32)
        return (1);
    
    elf_data->program_hdr = (Elf64_Phdr *) (data + elf_data->elf_hdr->e_phoff);
    elf_data->section_hdr = (Elf64_Shdr *) (data + elf_data->elf_hdr->e_shoff);

    elf_data->str_tab = (data + elf_data->section_hdr[elf_data->elf_hdr->e_shstrndx].sh_offset);

    return (0);
}

EMSCRIPTEN_KEEPALIVE
int parse_elf_x86(elf_parser_x86_t *elf_data,char *data)
{
    elf_data->elf_hdr = (Elf32_Ehdr *) (data);

    if (check_format(elf_data->elf_hdr->e_ident))
        return (1);

    if (elf_data->elf_hdr->e_ident[EI_CLASS] == ELFCLASS64)
        return (1);
    
    elf_data->program_hdr = (Elf32_Phdr *) (data + elf_data->elf_hdr->e_phoff);
    elf_data->section_hdr = (Elf32_Shdr *) (data + elf_data->elf_hdr->e_shoff);

    elf_data->str_tab = (data + elf_data->section_hdr[elf_data->elf_hdr->e_shstrndx].sh_offset);

    return (0);
}

int check_format(unsigned char *magic)
{
    return (
        (magic[0] == 0x7f) 
             && 
        (magic[1] == 0x4c)
             &&
        (magic[2] == 0x46)
    );
}

EMSCRIPTEN_KEEPALIVE
size_t elf_get_section_x86(elf_parser_x86_t *elf_data, char *data, char *name, char **addr)
{

    for (uint16_t i = 0; i < elf_data->elf_hdr->e_shnum; i++) {
        if (strcmp(name, (elf_data->str_tab + elf_data->section_hdr[i].sh_name)) == 0) {
            *addr = (data + elf_data->section_hdr[i].sh_offset);
            return (elf_data->section_hdr[i].sh_size);
        }
    }

    return (-1);
}

EMSCRIPTEN_KEEPALIVE
size_t elf_get_section_x64(elf_parser_x64_t *elf_data, char *data, char *name, char **addr)
{

    for (uint16_t i = 0; i < elf_data->elf_hdr->e_shnum; i++) {
        if (strcmp(name, (elf_data->str_tab + elf_data->section_hdr[i].sh_name)) == 0) {
            *addr = (data + elf_data->section_hdr[i].sh_offset);
            return (elf_data->section_hdr[i].sh_size);
        }
    }

    return (-1);
}