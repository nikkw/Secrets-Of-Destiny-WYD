// ---
// by ptr0x
// ---

#include "ReadPlugin.h"

void ReadPlugin()
{
	printf(" ---\n");
	printf(" by ptr0x\n");
	printf(" ---\n\n\n");
	// Procura no diretório que contém os plugins por arquivos com extensão .dll
	printf("Carregando plugin's...\n");
	int pluginCount = ReadFileInDir("Plugin/*");
	printf("Foram carregados %d plugin's.\n\n", pluginCount);
}

int ReadFileInDir(char *dir)
{
	// Busca por arquivos no diretorio dir
	HANDLE handle;
	WIN32_FIND_DATA win32_find_data;
	int pluginCount = 0;

	handle = FindFirstFile(dir, &win32_find_data);

	if(handle == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "Handle invalido.", "Error : FindFirstFile", MB_OK);
		exit(1);
	}

	while(FindNextFile(handle, &win32_find_data))
	{
		char *fileName = win32_find_data.cFileName;
		char fileFormat[4];

		if(sscanf(fileName, "%*[^.].%3s", fileFormat) == 1)
		{
			if(!strcmp(fileFormat, "dll"))
			{
				char fileDir[255];

				sprintf(&fileDir[0], "Plugin/%s", fileName);

				HMODULE hLib = LoadLibraryA(fileDir);

				if(hLib == NULL)
				{
					MessageBox(NULL, "Erro ao carregar plugin.", "Error : LoadLibraryA", MB_OK);
					exit(1);
				}

				pluginCount++;
				printf("Plugin %s foi carregado com sucesso.\n", fileName);
			}
		}
	}

	FindClose(handle);

	return pluginCount;
}