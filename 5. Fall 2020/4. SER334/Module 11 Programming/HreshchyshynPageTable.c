/**
 * This source file will be responsible for implementing the PageTable.h file. It receives the data from the
 * HreshchyshynDataLoader as requests are made from the main method in the Simulator. These add entries into
 * frames through a page table. As the limited entry numbers are filled, various page replacement algorithms are
 * used to select the appropriate page to replace. These results are displayed in the two display functions.
 *
 * Completion time: 10 hours total
 * @author Jacob Hreshchyshyn
 * @version 1.0
 */
#include "PageTable.h"
struct page_table_entry
{
    int frame_number;
    int used;
    int iteration_used;
    // metadata will store the dirty bit and the valid bit
    // right-most bit is vaild/invalid bit
    // second bit from right is dirty bit, always set to 0
    unsigned int metadata;
};
struct page_table
{
    int page_count;
    int frame_count;
    int replacement_type;
    int verbose;
    int page_faults;
    int* frame_entries; // physical memory
    int* frame_queue;
    int* page_tracker;
    struct page_table_entry* page_entries; // virtual memory keeping track of whether the page is already in physical memory
};
int iteration_tracker = 0;
/**
 * Creates a new page table object. Returns a pointer to created page table.
 *
 * @param page_count Number of pages.
 * @param frame_count Numbers of frames.
 * @param algorithm Page replacement algorithm
 * @param verbose Enables showing verbose table contents.
 * @return A page table object.
 */
struct page_table* page_table_create(int page_count, int frame_count, enum replacement_algorithm algorithm, int verbose)
{
    struct page_table* pt = (struct page_table*)malloc(sizeof(struct page_table));
    pt->page_count = page_count;
    pt->frame_count = frame_count;
    pt->replacement_type = algorithm;
    pt->verbose = verbose;
    pt->page_entries = (struct page_table_entry*)(malloc(sizeof(struct page_table_entry) * page_count));
    pt->page_tracker = (int*)malloc(sizeof(int) * page_count);
    pt->frame_entries = (int*)malloc(sizeof(int) * frame_count);
    pt->frame_queue = (int*)malloc(sizeof(int) * frame_count);
    pt->page_faults = 0;
    for(int i = 0; i < page_count; i++)
    {
        pt->page_entries[i].metadata = 0;
        pt->page_entries[i].frame_number = -1;
        pt->page_entries[i].used = 0;
        pt->page_entries[i].iteration_used = -1;
        pt->page_tracker[i] = -1;
    }
    for(int i = 0; i < frame_count; i++)
    {
        pt->frame_entries[i] = -1;
        pt->frame_queue[i] = -1;
    }
    return pt;
}
/**
 * Destroys an existing page table object. Sets outside variable to NULL.
 *
 * @param pt A page table object.
 */
void page_table_destroy(struct page_table** pt)
{
    free((*pt)->page_entries);
    free((*pt)->frame_entries);
    free((*pt)->frame_queue);
    free((*pt)->page_tracker);
    free(*pt);
}
/**
 * Simulates an instruction accessing a particular page in the page table.
 *
 * @param pt A page table object.
 * @param page The page being accessed.
 */
void page_table_access_page(struct page_table *pt, int page)
{
    /*for(int i = 0; i < pt->page_count; i++)
    {
        pt->page_entries[i].frame_number = 2;
        pt->page_entries[i].metadata = 0;
    }*/
    // FIFO page replacement
    if(pt->replacement_type == 0)
    {
        int accessed = 0;
        for(int i = 0; i < pt->frame_count; i++)
        {
            if(page == pt->frame_entries[i])
            {
                accessed = 1;
                break;
            }
            else if(pt->frame_entries[i] == -1)
            {
                pt->frame_entries[i] = page;
                pt->frame_queue[i] = page;
                pt->page_entries[page].frame_number = i;
                pt->page_entries[page].metadata = 1;
                pt->page_faults++;
                accessed = 1;
                break;
            }
        }
        if(accessed == 0)
        {
            for(int i = 0; i < pt->frame_count; i++)
            {
                if(pt->frame_queue[0] == pt->frame_entries[i])
                {
                    pt->page_entries[pt->frame_entries[i]].metadata = 0;
                    pt->frame_entries[i] = page;
                    // figure out how to update frame queue
                    for(int j = 1; j < pt->frame_count; j++)
                    {
                        pt->frame_queue[j - 1] = pt->frame_queue[j];
                    }
                    pt->frame_queue[pt->frame_count - 1] = page;
                    pt->page_entries[page].frame_number = i;
                    pt->page_entries[page].metadata = 1;
                    pt->page_faults++;
                    break;
                }
            }
        }
    }
    else if(pt->replacement_type == 1) // use the queue to determine least recently used, which would be at the top of the queue
    {
        //printf("iteration %d\n", iteration_tracker);
        int accessed = 0;
        for(int i = 0; i < pt->frame_count; i++)
        {
            if(page == pt->frame_entries[i])
            {
                accessed = 1;
                pt->page_entries[page].iteration_used = iteration_tracker;
                iteration_tracker++;
                break;
            }
            else if(pt->frame_entries[i] == -1)
            {
                pt->frame_entries[i] = page;
                pt->page_entries[page].frame_number = i;
                pt->page_entries[page].metadata = 1;
                pt->page_entries[page].iteration_used = iteration_tracker;
                iteration_tracker++;
                pt->page_faults++;
                accessed = 1;
                break;
            }
        }
        if(accessed == 0)
        {
            int most_recently_used = -1;
            int selected_page = -1;
            for(int i = 0; i < pt->page_count; i++)
            {
                if(pt->page_entries[i].metadata == 1)
                {
                    most_recently_used = pt->page_entries[i].iteration_used;
                    selected_page = i;
                    break;
                }
            }
            for(int i = 0; i < pt->page_count; i++)
            {
                if(most_recently_used > pt->page_entries[i].iteration_used && pt->page_entries[i].metadata == 1)
                {
                    most_recently_used = pt->page_entries[i].iteration_used;
                    selected_page = i;
                }
            }
            //printf("selected page: %d\n", selected_page);
            pt->page_entries[selected_page].metadata = 0;
            pt->frame_entries[pt->page_entries[selected_page].frame_number] = page;
            pt->page_entries[page].frame_number = pt->page_entries[selected_page].frame_number;
            pt->page_entries[page].metadata = 1;
            pt->page_entries[page].iteration_used = iteration_tracker;
            iteration_tracker++;
            pt->page_faults++;
        }
        /*for(int i = 0; i < pt->page_count; i++)
        {
            printf("iteration of page %d: %d\n", i, pt->page_entries[i].iteration_used);
        }*/
    }
    else
    {
        int accessed = 0;
        for(int i = 0; i < pt->frame_count; i++)
        {
            if(page == pt->frame_entries[i])
            {
                accessed = 1;
                pt->page_entries[page].used++;
                break;
            }
            else if(pt->frame_entries[i] == -1)
            {
                pt->frame_entries[i] = page;
                pt->frame_queue[i] = page;
                pt->page_entries[page].frame_number = i;
                pt->page_entries[page].metadata = 1;
                pt->page_entries[page].used++;
                pt->page_faults++;
                accessed = 1;
                break;
            }
        }
        if(accessed == 0)
        {
            int most_used = 0;
            int selected_page = -1;
            for(int i = 0; i < pt->page_count; i++)
            {
                if(pt->page_entries[i].metadata == 1)
                {
                    most_used = pt->page_entries[i].used;
                    selected_page = i;
                    break;
                }
            }
            for(int i = 0; i < pt->page_count; i++)
            {
                if(most_used < pt->page_entries[i].used && pt->page_entries[i].metadata == 1)
                {
                    most_used = pt->page_entries[i].used;
                    selected_page = i;
                }
            }
            pt->page_entries[selected_page].metadata = 0;
            pt->frame_entries[pt->page_entries[selected_page].frame_number] = page;
            pt->page_entries[page].frame_number = pt->page_entries[selected_page].frame_number;
            pt->page_entries[page].metadata = 1;
            pt->page_entries[page].used++;
            pt->page_faults++;
        }
    }
}
/**
 * Displays page table replacement algorithm, number of page faults, and the
 * current contents of the page table.
 *
 * @param pt A page table object.
 */
void page_table_display(struct page_table* pt)
{
    printf("====Page Table====\n");
    if(pt->replacement_type == 0)
        printf("Mode: FIFO\n");
    else if(pt->replacement_type == 1)
        printf("Mode: LRU\n");
    else
        printf("Mode: MFU\n");
    printf("Page Faults: %d\n", pt->page_faults);
    printf("page frame | dirty valid\n");
    for(int i = 0; i < pt->page_count; i++)
    {
        printf("   %d  ", i);
        printf("   %d  | ", pt->page_entries[i].frame_number);
        printf("   0  ");
        printf("   %d\n", pt->page_entries[i].metadata);
    }
}
/**
 * Displays the current contents of the page table.
 *
 * @param pt A page table object.
 */
void page_table_display_contents(struct page_table *pt)
{
    if(pt->replacement_type == 0)
    {
        printf("FIFO ");
    }
    else if(pt->replacement_type == 1)
    {
        printf("LRU ");
    }
    else
    {
        printf("MFU ");
    }
    printf("CURRENT CONTENTS\n");
    printf("page frame | dirty valid\n");
    for(int i = 0; i < pt->page_count; i++)
    {
        printf("   %d  ", i);
        printf("   %d  | ", pt->page_entries[i].frame_number);
        printf("   0  ");
        printf("   %d\n", pt->page_entries[i].metadata);
    }
}