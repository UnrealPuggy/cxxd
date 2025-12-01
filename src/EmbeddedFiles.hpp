namespace EmbeddedFiles
{

    class File
    {
        const char *data_;
        unsigned long long size_;
        unsigned int hash_;

    public:
        File(const char *data, unsigned long long size, unsigned int hash) : data_(data), size_(size), hash_(hash) {}

        unsigned long long size() const { return size_; };
        unsigned int hash() const { return hash_; };
        const char *data() const { return data_; };

        // Read struct safely
    };
    const File &findFile(const char *path);

};
// void testDaEmbed();
