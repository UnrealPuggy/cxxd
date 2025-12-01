#include <fstream>
#include <cstdio>

#include "EmbeddedFiles.hpp"

struct test
{
    int a;
    char b;
};
// extern const char amogus_txt_start[];
int main(int argc, char *argv[])
{
    // printf("First char:%c\n", amogus_txt_start[0]);
    int argCount = argc - 1;
    printf("arg count: %d\n", argCount);
    if (argCount)
    {
        for (int i = 1; i < argCount + 1; ++i)
        {
            printf("Arg%d: %s\n", i, argv[i]);
        }
    }
    test dat = {0, 0};
    std::ifstream in("test", std::ios::binary);

    if (in.good())
    {
        in.read((char *)&dat, 5);
    }
    dat.a++;
    // dat = *(test *)myfile_data();
    printf("Dat: \"%c\"\n", dat.b);

    std::ofstream out("test", std::ios::binary);
    // if (!in.good())
    // {
    // out.write("amogu", 5);
    EmbeddedFiles::File amogus = EmbeddedFiles::findFile("src/amogus.txt");
    out.write(amogus.data(), amogus.size());
    // }
    // else
    // {
    // out.write((char *)&dat, 5);
    // }

    // in.close();
    out.close();
    // printf("embedded data: %s\n", myfile_data());

    return 0;
}