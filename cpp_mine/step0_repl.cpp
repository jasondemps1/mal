#include <stdio.h>

#define BUF_SZ 512

char* read(char* input)
{
        return input;
}

char* eval(char* input)
{
        return input;
}

char* print(char* input)
{
        return input;
}

char* rep(char* input)
{
        return print(eval(read(input)));
}

int main ()//int argc, char ** argv)
{
        const char* prompt = "user>";
        char line_buf[BUF_SZ];

        do {
                printf("%s ", prompt);

                fgets(line_buf, BUF_SZ, stdin);

                printf("%s", rep(line_buf));
        } while (!feof(stdin));

        return 0;
}
