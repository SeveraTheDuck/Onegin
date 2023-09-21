#ifndef __SORTS_H__
#define __SORTS_H__

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <strings.h>
#include <limits.h>
#include "../../FileOpenLib/filestruct.h"

/// @brief A enumeration for different directions of sorting.
enum SortDirection
{
    REVERSE  = -1, ///< Reversed sort (from the end of strings).
    STRAIGHT = 1,  ///< Straight sort (from the beginning of strings).
};

/// @brief My simple swap function for any type of elements.
/// @param str1, str2 Pointers to swapping elements
/// @param element_size Size of both elements in bytes.
void MySwap(void* str1, void* str2, size_t element_size);

int StraightCompare(const void* ptr1, const void* ptr2);

/// @brief My interpretation of BubbleSort.
/// Sorts any types depending on their size and comparator function.
/// @param data sorting array.
/// @param number_of_elements Number of elements to be sorted in the array.
/// @param element_size Size of each element in bytes.
/// @param comparator Comparator function. Describes how to compare each pair of elements.
void BubbleSort(const void* data, const size_t number_of_elements,
                const size_t element_size,
                int (*comparator) (const void* ptr1, const void* ptr2));

int MyStrcmp(const struct line_struct* struct1,
             const struct line_struct* struct2,
             int step);

void StraightSort(struct file_input* buffer_info);

void RevSort(struct file_input* buffer_info);

void Output(const char* file_name, struct file_input* buffer_info);

void FileClean(const char* file_name);

void BufferOutput(const char* file_name, char* buffer, size_t buffer_size);

int RevCompare(const void* ptr1, const void* ptr2);

#endif
