/**
 * This source file will be responsible for implementing the DataLoader.h file. This file is responsible
 * for loading the file information into a data struct, which the HreshchyshynPageTable uses for carrying
 * out page replacement algorithms.
 *
 * Completion time: 10 hours total
 * @author Jacob Hreshchyshyn
 * @version 1.0
 */
#include "DataLoader.h"
//FILE* file_input;
/**
 * Loads a test_scenario strut from a textfile.
 *
 * @param filename The name of the file to load.
 * @return A struct containing the loaded file.
 */
struct test_scenario* load_test_data(char* filename) // successfully implemented
{
    struct test_scenario* info_store = (struct test_scenario*)(malloc)(sizeof(struct test_scenario));
    FILE* file_input;
    file_input = fopen(filename, "r");
    //file_input = fopen("data-1.txt", "r");
    if(file_input == NULL)
    {
        printf("Error. File not found.\n");
        exit(1);
    }
    char lineToRead[150];
    // read to find the number of pages
    fgets(lineToRead, 150, file_input);
    info_store->page_count = atoi(lineToRead);
    // read to find the number of frames
    fgets(lineToRead, 150, file_input);
    info_store->frame_count = atoi(lineToRead);
    // read to find the number of page entries (aka refstr_len)
    fgets(lineToRead, 150, file_input);
    info_store->refstr_len = atoi(lineToRead);
    // read page entries into refstr[512]
    for(int i = 0; i < info_store->refstr_len; i++)
    {
        fgets(lineToRead, 150, file_input);
        info_store->refstr[i] = atoi(lineToRead);
    }
    fclose(file_input);
    return info_store;
}