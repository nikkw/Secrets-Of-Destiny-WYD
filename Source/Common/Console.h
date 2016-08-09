// ---
// by ptr0x
// ---

#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>

inline void WriteInConsole(const char *frmt_text, ...)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD nWritten;
    char text[1024];

    va_list pArgs;
    va_start(pArgs, frmt_text);
    vsprintf(text, frmt_text, pArgs);
    va_end(pArgs);

    WriteConsole(hConsole, text, strlen(text), &nWritten, NULL);
}

inline void FixIOHandles()
{
    /* Output fix */
    int outParam = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
    FILE *stdout_stream = _fdopen(outParam, "w");

    *stdout = *stdout_stream;

    /* Input fix */
    int inParam = _open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT);
    FILE *stdin_stream = _fdopen(inParam, "r");

    *stdin = *stdin_stream;
}

inline void CreateConsole()
{
    AllocConsole();
    FixIOHandles();

	printf("#######################################\n");
	printf("#######################################\n");
	printf("##      Erick Mota   Producoes       ##\n");
	printf("##                                   ##\n");
	printf("##        Se você não sou eu         ##\n");
	printf("##                                   ##\n");
	printf("##                                   ##\n");
	printf("##         VAI SE FUDER              ##\n");
	printf("##                                   ##\n");
	printf("##       Beijos carinhosos           ##\n");
	printf("##                                   ##\n");
	printf("#######################################\n");
	printf("#######################################\n");

    /*while(TRUE)
    {
        WORD cmd;
        scanf("%x", &cmd);

        execute_command(cmd);
    }*/
}
