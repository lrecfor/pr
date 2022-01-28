#include "string_replace.h"

static int placeholder = 0;
static int count = 0;
static int index = 0;
static int step = 0;

static bool IsEmpty(const char* str)
{
    if (str == NULL || str[0] == '\0')
        return 1;
    else
        return 0;
}

void CheckingArgs(int argc, char** argv)
{
    if (argc == 1)
    {
        printf("main(): argv is empty");
        exit(EXIT_FAILURE);
    }

    else if (argc > 5)
    {
        printf("main(): Too many arguments");
        exit(EXIT_FAILURE);
    }

    if (argv[1] && argv[2])
    {
        const char* extension = ".txt";
        size_t extlen = strlen(extension);
        size_t filelen = strlen(argv[1]);
        if (strcmp(argv[1] + filelen - extlen, extension) != 0)
        {
            printf("main(): First filename is incorrect, no extension/no filename");
            exit(EXIT_FAILURE);
        }
        filelen = strlen(argv[2]);
        if (strcmp(argv[2] + filelen - extlen, extension) != 0)
        {
            printf("main(): Second filename is incorrect, no extension/no filename");
            exit(EXIT_FAILURE);
        }
    }

    if (!argv[3] || !argv[4])
    {
        printf("main(): No template string/no replacement string");
        exit(EXIT_FAILURE);
    }
}

char* ReadFromFile(char* filename, char* string)
{
    FILE* file;
    fopen_s(&file, filename, "r");

    int j = strlen(string);

    if (file)
    {
        int i = 0;
        char c;

        fseek(file, 0, SEEK_SET);
        fseek(file, 0, SEEK_END);
        size_t size = ftell(file);

        fseek(file, placeholder, SEEK_SET);
        if (placeholder >= size) return NULL;
        
        while ((c = fgetc(file)) != EOF)
        {
            if (i == MAX_SIZE) break;
            if (i == j) break;
            string[i] = c;
            i++;
        }

        if (i != j) string[i] = '\0';

        fclose(file);
    }

    else
    {
        printf("ReadFromFile(): Input file wasn't opened");
        exit(EXIT_FAILURE);
    }

    return string;
}

char* ReplaceString(char* original, const char* _template, const char* replacement)
{
    if (IsEmpty(original)) {
        printf("changeSeq(): Original string is empty\n");
        
    }
    else if (IsEmpty(_template)) {
        printf("changeSeq(): Pattern is empty\n");
        return 0;
    }
    else if (IsEmpty(replacement)) {
        printf("changeSeq(): Replacement is empty\n");
    }

    char* current = NULL;
    char* new_str = NULL;
    char* old_str = NULL;
    char* result = { "" };

    int count_placeholder = 0;

    new_str = CopyString(original);

    while ((current = StringFinding(new_str, _template))) {

        if (current == "long")
        {
            count_placeholder++;
            //index += MAX_SIZE;
            placeholder += MAX_SIZE;
            original = ReadFromFile("input.txt", original);
            if (original == NULL) return result;

            new_str = "";
            new_str = CopyString(original);
        }

        else if (current == "notEnough")
        {
            old_str = result;
            result = malloc(placeholder + strlen(result) + 1);
            memcpy(result, old_str, strlen(old_str));
            memcpy(result + strlen(old_str), new_str, placeholder);
            result[strlen(old_str) + placeholder] = '\0';
            //free(old_str);

            placeholder = strlen(result) - count * strlen(replacement) + count * strlen(_template);

            original = ReadFromFile("input.txt", original);
            if (original == NULL) return result;
            new_str = "";
            new_str = CopyString(original);
        }

        else if (current == "none")
        {
            old_str = result;
            result = malloc(strlen(old_str) + strlen(new_str) + 1);
            memcpy(result, old_str, strlen(old_str));
            memcpy(result + strlen(old_str), new_str, strlen(new_str) + 1);
            //free(old_str);

            placeholder += MAX_SIZE;

            original = ReadFromFile("input.txt", original);
            if (original == NULL) return result;
            new_str = "";
            new_str = CopyString(original);
        }

        else if (current == "stepback") 
        {
            placeholder = step;

            new_str = ReadFromFile("input.txt", new_str);
            if (new_str == NULL) return result;

            old_str = result;
            result = malloc(strlen(old_str) + 1);
            memcpy(result, old_str, strlen(old_str));
            memcpy(result + strlen(old_str), new_str, 1);
            result[strlen(old_str) + 1] = '\0';
            //free(old_str);

            placeholder++;

            original = ReadFromFile("input.txt", original);
            if (original == NULL) return result;
            new_str = "";
            new_str = CopyString(original);

            count_placeholder = 0;
        }

        else
        {
            if (count_placeholder != 0)
            {
                old_str = result;
                result = malloc(strlen(old_str) + strlen(replacement) + 1);
                memcpy(result, old_str, strlen(old_str));
                memcpy(result + strlen(old_str), replacement, strlen(replacement) + 1);
                //free(old_str);

                count++;
                if ((index + MAX_SIZE) < (count_placeholder + 1) * MAX_SIZE) placeholder = index;
                else placeholder = strlen(result) - count * strlen(replacement) + count * strlen(_template);

                original = ReadFromFile("input.txt", original);
                if (original == NULL) return result;
                new_str = "";
                new_str = CopyString(original);

                count_placeholder = 0;
                index = 0;
            }

            else
            {
                old_str = new_str;
                new_str = malloc(strlen(old_str) - strlen(current) + strlen(replacement) + 1);

                if (new_str == NULL) {
                    printf("changeSeq(): error with memory allocation\n");
                    free(old_str);
                    return 0;
                }

                memcpy(new_str, old_str, current - old_str);
                memcpy(new_str + (current - old_str), replacement, strlen(replacement) + 1);

                old_str = result;
                result = malloc(strlen(old_str) + strlen(new_str) + 1);
                memcpy(result, old_str, strlen(old_str));
                memcpy(result + strlen(old_str), new_str, strlen(new_str) + 1);
                //free(old_str);

                count++;
                placeholder = strlen(result) - count * strlen(replacement) + count * strlen(_template);

                original = ReadFromFile("input.txt", original);
                if (original == NULL) return result;
                new_str = "";
                new_str = CopyString(original);
            }
        }
    }

    return result;
}

char* StringFinding(const char* str, const char* repl)
{
    const char* tmp_str = str;
    char* notEnough = { "notEnough" };
    char* none = { "none" };
    char* long_ = { "long" };
    char* stepback = { "stepback" };

    int tmp_placeholder = 0;
    int tmp = 0;
    char first_repl = repl[index];
    char first_str = str[0];

    while (*str) {
        const char* tmp_repl = repl;
        tmp = placeholder;
        if (index == 0)
        {
            step = placeholder;
            tmp = placeholder;
            while (*tmp_repl && (*tmp_str == tmp_repl[index])) {
                ++tmp_str;
                index++;
                //tmp_placeholder = placeholder;
                if (!*tmp_str && tmp_repl[index] == '\0')
                    return (char*)str;

                if (!*tmp_str && *tmp_repl && (first_repl == first_str))
                {
                    placeholder = tmp;
                    return long_;
                }

                if (!*tmp_str && *tmp_repl)
                {
                    placeholder = tmp_placeholder;
                    index = 0;
                    return notEnough;
                }
            }
            if (index != 0 && !tmp_repl[index] == '\0')
            {
                index = 0;
                return stepback;
            }

        }

        else
        {
            while (*tmp_repl && (*tmp_str == tmp_repl[index])) {
                ++tmp_str;
                index++;

                if (!*tmp_str && tmp_repl[index] && (first_repl == first_str))
                {
                    placeholder = tmp;
                    return long_;
                }

                if (((!*tmp_str || !isalpha(*tmp_str)) && (tmp_repl[index] == '\0')) && (first_repl == first_str))
                {
                    placeholder = index;
                    return (char*)str;
                }

                if (tmp_repl[index] == '\0' && *tmp_str) return (char*)str;
            }
            index = 0;
            return stepback;
        }

        if (tmp_repl[index] == '\0') {
            index = 0;
            return (char*)str;
        }

        if ((*str == 92) && (++str == 'n')) tmp_placeholder = tmp_placeholder - 2;
        tmp_placeholder++;
        ++str;
        tmp_str = str;  
    }

    return none;
}

char* CopyString(const char* current)
{
    size_t length = strlen(current);

    char* copy = malloc(length + 1);
    char* tmp = copy;

    while (*current)
        *tmp++ = *current++;
    *tmp = '\0';

    return copy;
}