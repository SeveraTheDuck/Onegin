#include "headers/sorts.h"
#include "../FileOpenLib/filestruct.h"

void MySwap(line_struct* str1,
            line_struct* str2)
{
    assert(str1);
    assert(str2);

    line_struct temp_str = *str1;
    *str1 = *str2;
    *str2 = temp_str;
    return;
}

void BubbleSort(const file_input* buffer_info)
{
    assert(buffer_info);

    int cmp_status = 0;
    for (size_t i = 0; i < buffer_info->number_of_lines; ++i)
    {
        for (size_t j = 0; j < buffer_info->number_of_lines - i - 1; ++j)
        {
            cmp_status = MyStrcmp((const line_struct*)&buffer_info->lines_array[j],
                                  (const line_struct*)&buffer_info->lines_array[j + 1],
                                  (int)REVERSE);
            if (cmp_status > 0)
            {
                MySwap((line_struct*)&(buffer_info->lines_array[j]),
                       (line_struct*)&(buffer_info->lines_array[j + 1]));
            }
        }
    }
}

int MyStrcmp(const line_struct* struct1,
             const line_struct* struct2,
             int step)
{
    assert(struct1);
    assert(struct2);

    if (struct1->line[0] == '\0')
        return INT_MIN;
    if (struct2->line[0] == '\0')
        return INT_MAX;

    int i = 0;
    int j = 0;

    if (step == 1)
    {
        i = 0;
        j = 0;
    }
    else
    {
        i = (int)struct1->number_of_elements - 1;
        j = (int)struct2->number_of_elements - 1;
    }

    for (; struct1->line[i] != '\0' && struct2->line[j] != '\0'
        && 0 <= i && 0 <= j; i = i + step, j = j + step)
    {
        while (!isalpha(struct1->line[i]) && !isdigit(struct1->line[i]))
        {
            i += step;
        }
        while (!isalpha(struct2->line[j]) && !isdigit(struct2->line[j]))
        {
            j += step;
        }

        if (struct1->line[i] != struct2->line[j])
        {
            return (int)struct1->line[i] - (int)struct2->line[j];
        }
    }

    return 0;
}

int StraightCompare(const void* ptr1, const void* ptr2)
{
    assert(ptr1);
    assert(ptr2);

    const line_struct* struct1 = (const line_struct*)ptr1;
    const line_struct* struct2 = (const line_struct*)ptr2;

    return MyStrcmp(struct1, struct2, (int)STRAIGHT);
}

void StraightSort(file_input* buffer_info)
{
    assert(buffer_info);

    qsort((void*)(buffer_info->lines_array), buffer_info->number_of_lines,
          sizeof(line_struct), StraightCompare);
}

void RevSort(file_input* buffer_info)
{
    assert(buffer_info);

    BubbleSort(buffer_info);
    Output("output.txt", buffer_info);
}

void Output(const char* file_name, file_input* buffer_info)
{
    assert(buffer_info);

    FILE* fp = fopen(file_name, "a");
    assert(fp);

    for (size_t i = 0; i < buffer_info->number_of_lines; ++i)
    {
        if (buffer_info->lines_array[i].line[0] == '\0')
            continue;
        fprintf(fp, "%s\n", buffer_info->lines_array[i].line);
    }
    fprintf(fp, "\n--------------------------------------------------\n\n\n");

    fclose(fp);
}

void BufferOutput(const char* file_name, char* buffer, size_t buffer_size)
{
    FILE* fp = fopen(file_name, "a");
    assert(fp);

    for (size_t i = 0; i < buffer_size; ++i)
    {
        if (buffer[i] == '\0')
            fputc('\n', fp);
        else
            fputc(buffer[i], fp);
    }

    fclose(fp);
}
