#include "filestruct.h"
#include "sorts.h"

int main(int /*argc*/, char** /*argv*/)
{
    struct file_input onegin_struct = {.buffer = NULL, .buffer_size = 0,
                                     .number_of_lines = 0,
                                     .lines_array = NULL};

    GetFileInput("onegin.txt", &onegin_struct, PARTED);

    StraightSort(&onegin_struct);
    for (size_t i = 0; i < onegin_struct.number_of_lines; ++i)
    {
        if (onegin_struct.lines_array[i].line[0] == '\0')
            continue;
        printf("%s\n", onegin_struct.lines_array[i].line);
    }

    RevSort(&onegin_struct);

    FreeFileInput(&onegin_struct);
    return 0;
}
