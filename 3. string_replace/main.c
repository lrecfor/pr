#include "string_replace.h"

int main(int argc, char** argv)
{
	CheckingArgs(argc, argv);
	char* text = NULL;
	char* tmp = NULL;
	text = malloc(MAX_SIZE);
	tmp = malloc(MAX_SIZE);

	text = ReadFromFile(argv[1], text);
	tmp = CopyString(text);
	text = ReplaceString(text, argv[3], argv[4]);

	if (strcmp(text, tmp) == 0)
		printf("main(): nothing to replace, file output.txt wasnt created");
	
	else
	{
		FILE* out;
		fopen_s(&out, argv[2], "w");
		if (out)
		{
			fprintf(out, "%s", text);
			fclose(out);
		}
	}
	return 0;
}

/*2. Прочитать данные из файла, заменить вхождения одной последовательности байт на другую, результат записать 
в другой файл.Файл и последовательности произвольного размера и произвольного содержимого.
Имена файлов и последовательности(исходная и заменяемая) получать из аргументов командной строки.
Если в тексте "adfkasddkjadfkdaqwed" заменить "ad" на "12345", то получим "12345fkasddkj12345fkdaqwed".*/