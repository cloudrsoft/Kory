#ifndef WRITE_H
#define WRITE_H

#include <QtCore>
#include <openssl/aes.h>

static const unsigned char key32[32]=
{0x12,0x34,0x56,0x78,0x9a,0xbc,0xde,0xf0,
0x34,0x56,0x78,0x9a,0xbc,0xde,0xf0,0x12,
0x56,0x78,0x9a,0xbc,0xde,0xf0,0x12,0x34,
0x78,0x9a,0xbc,0xde,0xf0,0x12,0x34,0x56};

#define BLOCK_SIZE 16
#define FREAD_COUNT 4096
#define KEY_BIT 256
#define IV_SIZE 16
#define RW_SIZE 1
#define SUCC 0
#define FAIL -1

AES_KEY aes_ks3;
unsigned char iv[IV_SIZE];

namespace ProjectAIDB
{

    class write
    {
    public:
        write();
        bool writeFile(QString source_dir, QString filetype, QString filename, QStringList Reply, int Lang);

        enum{
            LANGUAGE_DEFAULT,
            LANGUAGE_ENGLISH,
            LANGUAGE_KOREAN,
        };

        unsigned char &language_string[] = {"default", "eng", "kor"};
    };

}

#endif // WRITE_H
