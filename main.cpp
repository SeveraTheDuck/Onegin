#include "../FileOpenLib/filestruct.h"
#include "headers/sorts.h"

int main(int /*argc*/, char** /*argv*/)
{
    struct file_input onegin_struct = {.buffer = NULL, .buffer_size = 0,
                                       .number_of_lines = 0,
                                       .lines_array = NULL};

    FileClean("output.txt");

    GetFileInput("onegin.txt", &onegin_struct, PARTED);

    StraightSort(&onegin_struct);
    Output("output.txt", &onegin_struct);

    RevSort(&onegin_struct);
    Output("output.txt", &onegin_struct);

    BufferOutput("output.txt", onegin_struct.buffer, onegin_struct.buffer_size);

    FreeFileInput(&onegin_struct);

    return 0;
}
