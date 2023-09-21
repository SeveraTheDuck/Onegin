#include "headers/sorts.h"

void MySwap(void* str1, void* str2, size_t element_size)
{
    assert(str1);
    assert(str2);

    char temp = 0;
    for(size_t i = 0; i < element_size; i += sizeof(char))
    {
        temp = *((char*)str1 + i);
        *((char*)str1 + i) = *((char*)str2 + i);
        *((char*)str2 + i) = temp;
    }
}

void BubbleSort(void* data,
                const size_t number_of_elements,
                const size_t element_size,
                int (*comparator) (const void* ptr1, const void* ptr2))
{
    assert(data);

    int cmp_status = 0;
    for (size_t i = 0; i < number_of_elements; ++i)
    {
        for (size_t j = 0; j < number_of_elements - i - 1; ++j)
        {
            cmp_status = comparator((const void*)((char*)data +  j      * element_size),
                                    (const void*)((char*)data + (j + 1) * element_size));
            if (cmp_status > 0)
            {
                MySwap((void*)((char*)data +  j      * element_size),
                       (void*)((char*)data + (j + 1) * element_size),
                       element_size);
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

int RevCompare(const void* ptr1, const void* ptr2)
{
    assert(ptr1);
    assert(ptr2);

    const line_struct* struct1 = (const line_struct*)ptr1;
    const line_struct* struct2 = (const line_struct*)ptr2;

    return MyStrcmp(struct1, struct2, (int)REVERSE);
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

    BubbleSort((void*)buffer_info->lines_array, buffer_info->number_of_lines,
               sizeof(line_struct), RevCompare);
}

void FileClean(const char* file_name)
{
    FILE* fp = fopen(file_name, "wb");
    assert(fp);
    fclose(fp);
    fp = NULL;
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
    assert(buffer);

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
