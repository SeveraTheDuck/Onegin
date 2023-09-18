#ifndef __SORTS_H__
#define __SORTS_H__

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <strings.h>
#include <limits.h>
#include "../../FileOpenLib/filestruct.h"

enum SortDirection
{
    REVERSE  = -1,
    STRAIGHT = 1,
};

void MySwap(const struct line_struct* str1,
            const struct line_struct* str2);

int StraightCompare(const void* ptr1, const void* ptr2);

void BubbleSort(const file_input* buffer_info,
                int (*comparator) (const void* ptr1, const void* ptr2));

int MyStrcmp(const struct line_struct* struct1,
             const struct line_struct* struct2,
             int step);

void StraightSort(struct file_input* buffer_info);

void RevSort(struct file_input* buffer_info);

void Output(const char* file_name, struct file_input* buffer_info);

void BufferOutput(const char* file_name, char* buffer, size_t buffer_size);

int RevCompare(const void* ptr1, const void* ptr2);

#endif
