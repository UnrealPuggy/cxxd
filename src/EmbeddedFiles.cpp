#include "EmbeddedFiles.hpp"
#include <cstdio>
#include <cstdint>
// asm(
//     ".section .rodata\n"
//     ".L_amogus_txt_start:\n"
//     ".incbin \"src/amogus.txt\"\n"
//     ".L_amogus_txt_end:\n"
//     ".section .text\n");
constexpr uint32_t hash(const char *s)
{
    uint32_t h = 0;
    while (*s)
        h = h * 31 + *s++;
    return h;
}

// Only visible in this TU
#define EMBED_FILE_PRIVATE(NAME, PATH)                          \
    asm(                                                        \
        ".section .rodata\n"                                    \
        ".L_" #NAME "_start:\n"                                 \
        ".incbin \"" PATH "\"\n"                                \
        ".L_" #NAME "_end:\n"                                   \
        ".section .text\n");                                    \
    extern const char NAME##_start[] asm(".L_" #NAME "_start"); \
    extern const char NAME##_end[] asm(".L_" #NAME "_end");     \
    constexpr uint32_t NAME##_hash = hash(PATH);

EMBED_FILE_PRIVATE(amogus_txt, "src/amogus.txt")

using namespace EmbeddedFiles;
static const EmbeddedFiles::File files[] = {
    {amogus_txt_start, (size_t)(amogus_txt_end - amogus_txt_start), amogus_txt_hash},
};

const File &EmbeddedFiles::findFile(const char *path)
{
    uint32_t hashedPath = hash(path);
    for (const File &f : files)
    {
        if (f.hash() == hashedPath)
            return f;
    }
    static const File dummy("", 0, 0);
    return dummy;
}
