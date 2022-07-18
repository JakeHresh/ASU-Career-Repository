/**
* This program utilizes multithreading to apply filters to images loaded in through the command line. If b is passed in as an argument, the blur filter is applied
 * to the image. If c is passed in as an argument, the cheese filter is applied. The number of threads used to modify the image can be modified by changing the
 * macro THREAD_COUNT.
*
* Completion time: 13 hours
* @author Jacob Hreshchyshyn, Vatricia Edgar, Xiangwei Zheng, Ruben Acuna
* @version 1.0
*/

////////////////////////////////////////////////////////////////////////////////
//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

//UNCOMMENT BELOW LINE IF USING SER334 LIBRARY/OBJECT FOR BMP SUPPORT
#include "BmpProcessor.h"


////////////////////////////////////////////////////////////////////////////////
//MACRO DEFINITIONS

//problem assumptions
#define BMP_HEADER_SIZE 14
#define BMP_DIB_HEADER_SIZE 40
#define MAXIMUM_IMAGE_SIZE 4096
#define THREAD_COUNT 1
//TODO: finish me


////////////////////////////////////////////////////////////////////////////////
//DATA STRUCTURES

//TODO: finish me
struct PixelArrContainer {
    struct Pixel** pixels;
    char filterSelection;
    int width;
    int height;
    int* x_hole_pos; // the hole pos variables mark the origins of each circle
    int* y_hole_pos;
    int holeNumAndSize;
    int threadNum;
};

////////////////////////////////////////////////////////////////////////////////
//MAIN PROGRAM CODE

struct Pixel** pArr;// global pixel array variable that threads can easily access.

void* runner(void* param)
{
    // cast the param parameter into a PixelArrContainer
    // use the PixelArrContainer to extract the filterSelection
    // if it's a blur selection, execute an algorithm that applies a blur to the pixels
    // if it's a cheese selection, execute an algorithm that applies a cheese effect to the pixels

    // for the blur, create a new 2D pixel array with the original pixel values
    // then, reading the original values, apply a change to the 2D array in the struct
    // create a pointer to the pixel array with its own memory allocated to it so it can store its own unmodified values
    struct PixelArrContainer* container = (struct PixelArrContainer*)param;
    char selection = container->filterSelection;
    printf("thread ran\n");
    printf("hello\n");
    printf("container height: %d\n", container->height);
    printf("%c\n", selection);
    if(selection == 'b')
    {
        //execute blur algorithm
        struct Pixel** originalPixels;
        originalPixels = (struct Pixel**)malloc(sizeof(struct Pixel*) * container->width);
        for(int p = 0; p < container->width; p++)
        {
            originalPixels[p] = (struct Pixel*)malloc(sizeof(struct Pixel) * container->height);
        }
        // copy is created
        // ALL i's AND j's IN INDICES NEED TO BE SWAPPED************************************************
        for(int i = 0; i < container->height; i++)
        {
            for(int j = 0; j < container->width; j++)
            {
                originalPixels[j][i] = container->pixels[j][i];
            }
        }
        // apply blur in loop
        for(int i = 0; i < container->height; i++)
        {
            for(int j = 0; j < container->width; j++)
            {
                if(i > 0 && i < container->height - 1 && j > 0 && j < container->width - 1)
                {
                    container->pixels[j][i].blue = (
                            originalPixels[j - 1][i - 1].blue + originalPixels[  j  ][i - 1].blue + originalPixels[j + 1][i - 1].blue +
                            originalPixels[j - 1][  i  ].blue + originalPixels[  j  ][  i  ].blue + originalPixels[j + 1][  i  ].blue +
                            originalPixels[j - 1][i + 1].blue + originalPixels[  j  ][i + 1].blue + originalPixels[j + 1][i + 1].blue)/9;
                    container->pixels[j][i].green = (
                            originalPixels[j - 1][i - 1].green + originalPixels[  j  ][i - 1].green + originalPixels[j + 1][i - 1].green +
                            originalPixels[j - 1][  i  ].green + originalPixels[  j  ][  i  ].green + originalPixels[j + 1][  i  ].green +
                            originalPixels[j - 1][i + 1].green + originalPixels[  j  ][i + 1].green + originalPixels[j + 1][i + 1].green)/9;
                    container->pixels[j][i].red = (
                            originalPixels[j - 1][i - 1].red + originalPixels[  j  ][i - 1].red + originalPixels[j + 1][i - 1].red +
                            originalPixels[j - 1][  i  ].red + originalPixels[  j  ][  i  ].red + originalPixels[j + 1][  i  ].red +
                            originalPixels[j - 1][i + 1].red + originalPixels[  j  ][i + 1].red + originalPixels[j + 1][i + 1].red)/9;
                }
                if(container->height > 1 && container->width > 1)
                {
                    if(i == 0 && j == 0)
                    {
                        container->pixels[j][i].blue = (
                                originalPixels[ j ][ i ].blue + originalPixels[j + 1][  i  ].blue +
                                originalPixels[j][i + 1].blue + originalPixels[j + 1][i + 1].blue)/4;
                        container->pixels[j][i].green = (
                                originalPixels[ j ][ i ].green + originalPixels[j + 1][  i  ].green +
                                originalPixels[j][i + 1].green + originalPixels[j + 1][i + 1].green)/4;
                        container->pixels[j][i].red = (
                                originalPixels[ j ][ i ].red + originalPixels[j + 1][  i  ].red +
                                originalPixels[j][i + 1].red + originalPixels[j + 1][i + 1].red)/4;
                    }
                    else if(i == 0 && j == container->width - 1)
                    {
                        container->pixels[j][i].blue = (
                                originalPixels[j - 1][  i  ].blue + originalPixels[ j ][ i ].blue +
                                originalPixels[j - 1][i + 1].blue + originalPixels[j][i + 1].blue)/4;
                        container->pixels[j][i].green = (
                                originalPixels[j - 1][  i  ].green + originalPixels[ j ][ i ].green +
                                originalPixels[j - 1][i + 1].green + originalPixels[j][i + 1].green)/4;
                        container->pixels[j][i].red = (
                                originalPixels[j - 1][  i  ].red + originalPixels[ j ][ i ].red +
                                originalPixels[j - 1][i + 1].red + originalPixels[j][i + 1].red)/4;
                    }
                    else if(i == container->height - 1 && j == 0)
                    {
                        container->pixels[j][i].blue = (
                                originalPixels[j][i - 1].blue + originalPixels[j + 1][i - 1].blue +
                                originalPixels[ j ][ i ].blue + originalPixels[j + 1][  i  ].blue)/4;
                        container->pixels[j][i].green = (
                                originalPixels[j][i - 1].green + originalPixels[j + 1][i - 1].green +
                                originalPixels[ j ][ i ].green + originalPixels[j + 1][  i  ].green)/4;
                        container->pixels[j][i].red = (
                                originalPixels[j][i - 1].red + originalPixels[j + 1][i - 1].red +
                                originalPixels[ j ][ i ].red + originalPixels[j + 1][  i  ].red)/4;
                    }
                    else if(i == container->height - 1 && j == container ->width - 1)
                    {
                        container->pixels[j][i].blue = (
                                originalPixels[j - 1][i - 1].blue + originalPixels[j][i - 1].blue +
                                originalPixels[j - 1][  i  ].blue + originalPixels[ j ][ i ].blue)/4;
                        container->pixels[j][i].green = (
                                originalPixels[j - 1][i - 1].green + originalPixels[j][i - 1].green +
                                originalPixels[j - 1][  i  ].green + originalPixels[ j ][ i ].green)/4;
                        container->pixels[j][i].red = (
                                originalPixels[j - 1][i - 1].red + originalPixels[j][i - 1].red +
                                originalPixels[j - 1][  i  ].red + originalPixels[ j ][ i ].red)/4;
                    }
                    else if(i == 0)
                    {
                        container->pixels[j][i].blue = (
                                originalPixels[j - 1][  i  ].blue + originalPixels[ j ][ i ].blue + originalPixels[j + 1][  i  ].blue +
                                originalPixels[j - 1][i + 1].blue + originalPixels[j][i + 1].blue + originalPixels[j + 1][i + 1].blue)/6;
                        container->pixels[j][i].green = (
                                originalPixels[j - 1][  i  ].green + originalPixels[ j ][ i ].green + originalPixels[j + 1][  i  ].green +
                                originalPixels[j - 1][i + 1].green + originalPixels[j][i + 1].green + originalPixels[j + 1][i + 1].green)/6;
                        container->pixels[j][i].red = (
                                originalPixels[j - 1][  i  ].red + originalPixels[ j ][ i ].red + originalPixels[j + 1][  i  ].red +
                                originalPixels[j - 1][i + 1].red + originalPixels[j][i + 1].red + originalPixels[j + 1][i + 1].red)/6;
                    }
                    else if(i == container->height - 1)
                    {
                        container->pixels[j][i].blue = (
                                originalPixels[j - 1][i - 1].blue + originalPixels[j][i - 1].blue + originalPixels[j + 1][i - 1].blue +
                                originalPixels[j - 1][  i  ].blue + originalPixels[ j ][ i ].blue + originalPixels[j + 1][  i  ].blue)/6;
                        container->pixels[j][i].green = (
                                originalPixels[j - 1][i - 1].green + originalPixels[j][i - 1].green + originalPixels[j + 1][i - 1].green +
                                originalPixels[j - 1][  i  ].green + originalPixels[ j ][ i ].green + originalPixels[j + 1][  i  ].green)/6;
                        container->pixels[j][i].red = (
                                originalPixels[j - 1][i - 1].red + originalPixels[j][i - 1].red + originalPixels[j + 1][i - 1].red +
                                originalPixels[j - 1][  i  ].red + originalPixels[ j ][ i ].red + originalPixels[j + 1][  i  ].red)/6;
                    }
                    else if(j == 0)
                    {
                        container->pixels[j][i].blue = (
                                originalPixels[j][i - 1].blue + originalPixels[j + 1][i - 1].blue +
                                originalPixels[ j ][ i ].blue + originalPixels[j + 1][  i  ].blue +
                                originalPixels[j][i + 1].blue + originalPixels[j + 1][i + 1].blue)/6;
                        container->pixels[j][i].green = (
                                originalPixels[j][i - 1].green + originalPixels[j + 1][i - 1].green +
                                originalPixels[ j ][ i ].green + originalPixels[j + 1][  i  ].green +
                                originalPixels[j][i + 1].green + originalPixels[j + 1][i + 1].green)/6;
                        container->pixels[j][i].red = (
                                originalPixels[j][i - 1].red + originalPixels[j + 1][i - 1].red +
                                originalPixels[ j ][ i ].red + originalPixels[j + 1][  i  ].red +
                                originalPixels[j][i + 1].red + originalPixels[j + 1][i + 1].red)/6;
                    }
                    else if(j == container->width - 1)
                    {
                        container->pixels[j][i].blue = (
                                originalPixels[j - 1][i - 1].blue + originalPixels[j][i - 1].blue +
                                originalPixels[j - 1][  i  ].blue + originalPixels[ j ][ i ].blue +
                                originalPixels[j - 1][i + 1].blue + originalPixels[j][i + 1].blue)/6;
                        container->pixels[j][i].green = (
                                originalPixels[j - 1][i - 1].green + originalPixels[j][i - 1].green +
                                originalPixels[j - 1][  i  ].green + originalPixels[ j ][ i ].green +
                                originalPixels[j - 1][i + 1].green + originalPixels[j][i + 1].green)/6;
                        container->pixels[j][i].red = (
                                originalPixels[j - 1][i - 1].red + originalPixels[j][i - 1].red +
                                originalPixels[j - 1][  i  ].red + originalPixels[ j ][ i ].red +
                                originalPixels[j - 1][i + 1].red + originalPixels[j][i + 1].red)/6;
                    }
                }
                if(container->height > 1 && container->width == 1) // width index is always 0
                {
                    if(i == 0)
                    {
                        container->pixels[j][i].blue = (
                                originalPixels[ j ][ i ].blue +
                                originalPixels[j][i + 1].blue)/2;
                        container->pixels[j][i].green = (
                                originalPixels[ j ][ i ].green +
                                originalPixels[j][i + 1].green)/2;
                        container->pixels[j][i].red = (
                                originalPixels[ j ][ i ].red +
                                originalPixels[j][i + 1].red)/2;
                    }
                    else if(i == container->height - 1)
                    {
                        container->pixels[j][i].blue = (
                                originalPixels[j][i - 1].blue +
                                originalPixels[ j ][ i ].blue)/2;
                        container->pixels[j][i].green = (
                                originalPixels[j][i - 1].green +
                                originalPixels[ j ][ i ].green)/2;
                        container->pixels[j][i].red = (
                                originalPixels[j][i - 1].red +
                                originalPixels[ j ][ i ].red)/2;
                    }
                    else
                    {
                        container->pixels[j][i].blue = (
                                originalPixels[j][i - 1].blue +
                                originalPixels[ j ][ i ].blue +
                                originalPixels[j][i + 1].blue)/3;
                        container->pixels[j][i].green = (
                                originalPixels[j][i - 1].green +
                                originalPixels[ j ][ i ].green +
                                originalPixels[j][i + 1].green)/3;
                        container->pixels[j][i].red = (
                                originalPixels[j][i - 1].red +
                                originalPixels[ j ][ i ].red +
                                originalPixels[j][i + 1].red)/3;
                    }
                }
                if(container->height == 1 && container->width > 1) // height index is always 0
                {
                    if(j == 0)
                    {
                        container->pixels[j][i].blue = (
                                originalPixels[ j ][ i ].blue + originalPixels[j + 1][  i  ].blue)/2;
                        container->pixels[j][i].green = (
                                originalPixels[ j ][ i ].green + originalPixels[j + 1][  i  ].green)/2;
                        container->pixels[j][i].red = (
                                originalPixels[ j ][ i ].red + originalPixels[j + 1][  i  ].red)/2;
                    }
                    else if(j == container->width - 1)
                    {
                        container->pixels[j][i].blue = (
                                originalPixels[j - 1][  i  ].blue + originalPixels[ j ][ i ].blue)/2;
                        container->pixels[j][i].green = (
                                originalPixels[j - 1][  i  ].green + originalPixels[ j ][ i ].green)/2;
                        container->pixels[j][i].red = (
                                originalPixels[j - 1][  i  ].red + originalPixels[ j ][ i ].red)/2;
                    }
                    else
                    {
                        container->pixels[j][i].blue = (
                                originalPixels[j - 1][  i  ].blue + originalPixels[ j ][ i ].blue + originalPixels[j + 1][  i  ].blue)/3;
                        container->pixels[j][i].green = (
                                originalPixels[j - 1][  i  ].green + originalPixels[ j ][ i ].green + originalPixels[j + 1][  i  ].green)/3;
                        container->pixels[j][i].red = (
                                originalPixels[j - 1][  i  ].red + originalPixels[ j ][ i ].red + originalPixels[j + 1][  i  ].red)/3;
                    }
                }
            }
        }
    }// FIX THE j and i swap AFTER THE BLUR IS SORTED OUT
    else if(selection == 'c')
    {
        // create copy of pixel information.
        // apply yellow tint to each of the pixels in container using copy as reference
        // swap the j's and i's
        struct Pixel** originalPixels;
        originalPixels = (struct Pixel**)malloc(sizeof(struct Pixel*) * container->width);
        for(int p = 0; p < container->width; p++)
        {
            originalPixels[p] = (struct Pixel*)malloc(sizeof(struct Pixel) * container->height);
        }
        // copy is created
        for(int i = 0; i < container->height; i++)
        {
            for(int j = 0; j < container->width; j++)
            {
                originalPixels[j][i] = container->pixels[j][i];
            }
        }
        // apply yellow tint
        for(int i = 0; i < container->height; i++)
        {
            for(int j = 0; j < container->width; j++)
            {
                int redShift = ((20*255)/100);
                int greenShift = ((20*255)/100);
                int redMaxxed = 0;
                int greenMaxxed = 0;
                if((container->pixels[j][i].red + redShift) > 255)
                {
                    redShift = 255;
                    redMaxxed = 1;
                }
                if((container->pixels[j][i].green + greenShift) > 255)
                {
                    greenShift = 255;
                    greenMaxxed = 1;
                }
                if(redMaxxed == 0)
                {
                    container->pixels[j][i].red += ((20*255)/100);// 20% shift
                }
                else
                {
                    container->pixels[j][i].red = 255;
                }
                if(greenMaxxed == 0)
                {
                    container->pixels[j][i].green += ((20*255)/100);
                }
                else
                {
                    container->pixels[j][i].green = 255;
                }
            }
        }
        // draw circles onto image
        int largedone = 0;
        int smalldone = 0;
        printf("threadnum: %d\n", container->threadNum);
        for(int i = 0; i < container->height; i++)
        {
            for(int j = 0; j < container->width; j++) // j is x. i is y.
            {
                // calculate a point using the equation for a circle
                for(int k = 0; k < container->holeNumAndSize; k++)
                {
                    // swap j's and i's, including with test point?
                    //int testPoint = ((j - container->x_hole_pos[k]) * (j - container->x_hole_pos[k])) + ((i - container->y_hole_pos[k]) * (i - container->y_hole_pos[k]));
                    //int testPoint = ((j - container->x_hole_pos[k + container->threadNum]) * (j - container->x_hole_pos[k + container->threadNum])) + ((i - container->y_hole_pos[k + container->threadNum]) * (i - container->y_hole_pos[k + container->threadNum]));
                    //int testPoint = ((i - container->x_hole_pos[k]) * (i - container->x_hole_pos[k])) + ((j - container->y_hole_pos[k]) * (j - container->y_hole_pos[k]));
                    int testPoint = ((((container->width * container->threadNum) - 1 + j) - container->x_hole_pos[k]) * (((container->width * container->threadNum) - 1 + j) - container->x_hole_pos[k])) + ((i - container->y_hole_pos[k]) * (i - container->y_hole_pos[k]));
                    if(largedone < 2)
                    {
                        if(testPoint <= (container->holeNumAndSize + 5) * (container->holeNumAndSize + 5)) // check if it's equal to the square of the average radius
                        {
                            container->pixels[j][i].red = 0;
                            container->pixels[j][i].green = 0;
                            container->pixels[j][i].blue = 0;
                        }
                    }
                    else if(smalldone < 2)
                    {
                        int r = container->holeNumAndSize - 5;
                        if(r <= 0)
                        {
                            r = 1;
                        }
                        if(testPoint <= r * r) // check if it's equal to the square of the average radius
                        {
                            container->pixels[j][i].red = 0;
                            container->pixels[j][i].green = 0;
                            container->pixels[j][i].blue = 0;
                        }
                    }
                    else
                    {
                        if(testPoint <= container->holeNumAndSize * container->holeNumAndSize) // check if it's equal to the square of the average radius
                        {
                            container->pixels[j][i].red = 0;
                            container->pixels[j][i].green = 0;
                            container->pixels[j][i].blue = 0;
                        }
                    }
                }
                largedone++;
                smalldone++;
            }
        }
    }
    pthread_exit(0);
}

int main(int argc, char* argv[]) {// used to have a void return type
    srand(time(NULL));
	pthread_t tid[THREAD_COUNT];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	char* outputFileName = argv[4];
	char filterSelection = argv[6][0];// hopefully this will correctly be a character
    FILE* file_input;
    file_input = fopen(argv[2], "rb"); // should read argv[2] since argv[1] will be the -i argument
    if(file_input == NULL)
    {
        printf("Error. File not found.\n");
        exit(1);
    }

    struct BMP_Header* header = (struct BMP_Header*)malloc(sizeof(struct BMP_Header)); // remember to deallocate
    struct DIB_Header* header_dib = (struct DIB_Header*)malloc(sizeof(struct BMP_Header)); // remember to deallocate
    printf("reading BMP header\n");
    readBMPHeader(file_input, header);
    printf("reading DIB header\n");
    readDIBHeader(file_input, header_dib);
    printf("width of dib: %d\n", header_dib->width);
    printf("height of dib: %d\n", header_dib->height);
    //struct Pixel** pArr;
    int tc = THREAD_COUNT;
    if(tc%2 == 1 && tc != 1) tc++;
    pArr = (struct Pixel**)malloc(sizeof(struct Pixel*) * header_dib->width);
    for(int p = 0; p < header_dib->width; p++)
    {
        pArr[p] = (struct Pixel*)malloc(sizeof(struct Pixel) * header_dib->height);
    }
    printf("reading pixels\n");
    readPixelsBMP(file_input, pArr, header_dib->width, header_dib->height);
    printf("successfully read pixels\n");
    struct PixelArrContainer* pContainer = (struct PixelArrContainer*)malloc(sizeof(struct PixelArrContainer) * tc); // multiply by thread_count to have an array of pixel containers, which each thread manages
    printf("successfully allocated pContainer memory\n");
    if(filterSelection == 'b')
    {
        /*pContainer->pixels = pArr;
        pContainer->filterSelection = filterSelection;
        pContainer->width = header_dib->width;
        pContainer->height = header_dib->height;*/
        for(int i = 0; i < tc; i++)
        {
            printf("assigned filter selection\n");
            pContainer[i].filterSelection = filterSelection;
            // allocate the pixel array of each pContainer. Once each thread has memory allocated to it and
            if(THREAD_COUNT == 1)
            {
                pContainer[i].pixels = pArr;
                pContainer[i].filterSelection = filterSelection;
                pContainer[i].width = header_dib->width;
                pContainer[i].height = header_dib->height;
            }
            else if(header_dib->width%tc == 0)
            {
                // must account for first pContainer and last pContainer. First only looks for adjacent pixel data to the right of it. Last looks only to the left.
                // ALL other pContainers must look both right and left for adjacent pixel data
                if(i == 0)
                {
                    // width should be divided by the THREAD_COUNT
                    pContainer[i].width = (header_dib->width/tc) + 1;
                    printf("width: %d\n", pContainer[i].width);
                    //printf("height: %d\n", pContainer[i].height);
                    printf("assigned width\n");
                    pContainer[i].height = header_dib->height;
                    printf("height: %d\n", pContainer[i].height);
                    printf("assigned height\n");
                    // allocate memory for pixel info
                    pContainer[i].pixels = (struct Pixel**)malloc(sizeof(struct Pixel*) * pContainer[i].width);
                    for(int p = 0; p < pContainer[i].width; p++)
                    {
                        pContainer[i].pixels[p] = (struct Pixel*)malloc(sizeof(struct Pixel) * pContainer[i].height);
                    }
                    printf("allocated memory for specific pixel container\n");
                    // specific pixel info from pArr is copied into array for struct
                    for(int j = 0; j < pContainer[i].height; j++)
                    {
                        for(int k = 0; k < pContainer[i].width; k++)
                        {
                            pContainer[i].pixels[k][j] = pArr[k][j];
                        }
                    }
                }
                else if(i == tc - 1)
                {
                    // width should be divided by the THREAD_COUNT
                    pContainer[i].width = (header_dib->width/tc) + 1;
                    pContainer[i].height = header_dib->height;
                    // allocate memory for pixel info
                    pContainer[i].pixels = (struct Pixel**)malloc(sizeof(struct Pixel*) * pContainer[i].width);
                    for(int p = 0; p < pContainer[i].width; p++)
                    {
                        pContainer[i].pixels[p] = (struct Pixel*)malloc(sizeof(struct Pixel) * pContainer[i].height);
                    }
                    // specific pixel info from pArr is copied into array for struct
                    for(int j = 0; j < pContainer[i].height; j++)
                    {
                        for(int k = 0; k < pContainer[i].width; k++)
                        {
                            // tricky indexing to get to the end of the pixel array
                            // swapped k's with j's and vice versa
                            //pContainer[i].pixels[k][j] = pArr[k][(header_dib->width - 1) - (pContainer[i].width - 1) + j]; //this is the line of code that is different if the last thread is being worked on. It should start reading from a separate part of pArr.
                            pContainer[i].pixels[k][j] = pArr[(header_dib->width - 1) - (pContainer[i].width - 1) + k][j];
                        }
                    }
                }
                else
                {
                    printf("reads pixel data for next thread\n");
                    // width is the same + 2 in order to account for both adjacent sides
                    pContainer[i].width = (header_dib->width/tc) + 2;
                    pContainer[i].height = header_dib->height;
                    // allocate memory for pixel info
                    pContainer[i].pixels = (struct Pixel**)malloc(sizeof(struct Pixel*) * pContainer[i].width);
                    for(int p = 0; p < pContainer[i].width; p++)
                    {
                        pContainer[i].pixels[p] = (struct Pixel*)malloc(sizeof(struct Pixel) * pContainer[i].height);
                    }
                    for(int j = 0; j < pContainer[i].height; j++)
                    {
                        for(int k = 0; k < pContainer[i].width; k++)
                        {
                            // needs fancy indexing to access the correct parts of pArr
                            // swapped k's with j's and vice versa
                            printf("i: %d", i);
                            //pContainer[i].pixels[k][j] = pArr[k][(((header_dib->width/THREAD_COUNT) * i) - 1) + j]; // the subtraction needs to be modified
                            pContainer[i].pixels[k][j] = pArr[(((header_dib->width/tc) * i) - 1) + k][j];
                        }
                    }
                }
            }
            printf("next thread\n");
        }
    }
    if(filterSelection == 'c') // memory should be allocated differently as well based on the filter selection
    {
        // allocate memory for integer arrays
        for(int i = 0; i < tc; i++)
        {
            pContainer[i].filterSelection = filterSelection;
            pContainer[i].threadNum = i;
            // allocate the pixel array of each pContainer. Once each thread has memory allocated to it and
            if(THREAD_COUNT == 1)
            {
                pContainer[i].pixels = pArr;
                pContainer[i].filterSelection = filterSelection;
                pContainer[i].width = header_dib->width;
                pContainer[i].height = header_dib->height;
            }
            else if(header_dib->width%tc == 0)
            {
                // width should be divided by the THREAD_COUNT
                pContainer[i].width = (header_dib->width/tc); // no need for plus 1.
                printf("width: %d\n", pContainer[i].width);
                //printf("height: %d\n", pContainer[i].height);
                printf("assigned width\n");
                pContainer[i].height = header_dib->height;
                printf("height: %d\n", pContainer[i].height);
                printf("assigned height\n");
                // allocate memory for pixel info
                pContainer[i].pixels = (struct Pixel**)malloc(sizeof(struct Pixel*) * pContainer[i].width);
                for(int p = 0; p < pContainer[i].width; p++)
                {
                    pContainer[i].pixels[p] = (struct Pixel*)malloc(sizeof(struct Pixel) * pContainer[i].height);
                }
                // assign values to pContainer pixels
                if(i == 0)
                {
                    for(int j = 0; j < pContainer[i].height; j++)
                    {
                        for(int k = 0; k < pContainer[i].width; k++)
                        {
                            pContainer[i].pixels[k][j] = pArr[k][j];
                        }
                    }
                }
                else if(i == tc - 1)
                {
                    for(int j = 0; j < pContainer[i].height; j++)
                    {
                        for(int k = 0; k < pContainer[i].width; k++)
                        {
                            pContainer[i].pixels[k][j] = pArr[(header_dib->width - 1) - (pContainer[i].width - 1) + k][j];
                        }
                    }
                }
                else
                {
                    for(int j = 0; j < pContainer[i].height; j++)
                    {
                        for(int k = 0; k < pContainer[i].width; k++)
                        {
                            pContainer[i].pixels[k][j] = pArr[(((header_dib->width/tc) * i) - 1) + k][j];
                        }
                    }
                }
            }

            if(header_dib->width <= header_dib->height)
            {
                pContainer[i].holeNumAndSize = ((8 * header_dib->width)/100);
            }
            else
            {
                pContainer[i].holeNumAndSize = ((8 * header_dib->height)/100);
            }
            pContainer[i].x_hole_pos = (int *) malloc(sizeof(int) * header_dib->width);
            pContainer[i].y_hole_pos = (int *) malloc(sizeof(int) * header_dib->height);

            // use RNG to find x and y coordinates for the positions of the black circles
            /*for (int j = 0; j < pContainer[i].holeNumAndSize; j++) {
                int randx = rand();
                while (randx >= header_dib->width) {
                    randx = rand();
                }
                int randy = rand();
                while (randy >= header_dib->height) {
                    randy = rand();
                }
                pContainer[i].x_hole_pos[j] = randx;
                pContainer[i].y_hole_pos[j] = randy;
            }*/
        }
        // This should be where the circle points are calculated
        for (int j = 0; j < pContainer[0].holeNumAndSize; j++) {
            int randx = rand();
            while (randx >= header_dib->width) {
                randx = rand();
            }
            int randy = rand();
            while (randy >= header_dib->height) {
                randy = rand();
            }
            pContainer[0].x_hole_pos[j] = randx;
            pContainer[0].y_hole_pos[j] = randy;
            printf("x_hole_pos: %d\n", randx);
            printf("y_hole_pos: %d\n", randy);
        }
        for(int i = 0; i < tc; i++)
        {
            for(int j = 0; j < pContainer[0].holeNumAndSize; j++)
            {
                pContainer[i].x_hole_pos[j] = pContainer[0].x_hole_pos[j];
                pContainer[i].y_hole_pos[j] = pContainer[0].y_hole_pos[j];
            }
        }
    }
    // run threads through runner function
    printf("Pixel info before function: %d", pContainer[0].pixels[0][0].blue);
    for(int i = 0; i < tc; i++)
    {
        pthread_create(&tid[i], &attr, runner, pContainer + i); // adding i to pContainer to shift the memory location to pass in the correct pContainer.
    }
    // merge threads
    for(int i = 0; i < tc; i++)
    {
        pthread_join(tid[i], NULL);
    }
    fclose(file_input);
    printf("Pixel info after function: %d", pContainer[0].pixels[0][0].blue);
    //once threads are finished working, the images need to be merged together. Loop through the collection of pixel containers, assign their values to pArr, and write pArr to file
    //if(filterSelection == 'b')
    //{
        for(int i = 0; i < tc; i++)
        {
            if(THREAD_COUNT == 1)
            {
                pArr = pContainer[i].pixels;
            }
            else if(header_dib->width%tc == 0)
            {
                if(i == 0)
                {
                    printf("first merge\n");
                    // should write pixel info to pArr
                    for(int j = 0; j < pContainer[i].height; j++)
                    {
                        for(int k = 0; k < pContainer[i].width; k++)
                        {
                            //pContainer[i].pixels[j][k] = pArr[j][k];
                            // swapped j's with k's and vice versa
                            pArr[k][j] = pContainer[i].pixels[k][j];
                        }
                    }
                }
                else if(i == tc - 1)
                {
                    printf("last merge\n");
                    // should write pixel info to pArr
                    for(int j = 0; j < pContainer[i].height; j++)
                    {
                        for(int k = 0; k < pContainer[i].width; k++)
                        {
                            // tricky indexing to get to the end of the pixel array
                            //pContainer[i].pixels[j][k] = pArr[j][(header_dib->width - 1) - (pContainer[i].width - 1) + k]; //this is the line of code that is different if the last thread is being worked on. It should start reading from a separate part of pArr.
                            // swapped j's with k's and vice versa
                            //pArr[k][(header_dib->width - 1) - (pContainer[i].width - 1) + j] = pContainer[i].pixels[k][j];
                            pArr[(header_dib->width - 1) - (pContainer[i].width - 1) + k][j] = pContainer[i].pixels[k][j];
                        }
                    }
                }
                else
                {
                    // should write pixel info to pArr
                    for(int j = 0; j < pContainer[i].height; j++)
                    {
                        for(int k = 0; k < pContainer[i].width; k++)
                        {
                            // needs fancy indexing to access the correct parts of pArr
                            //pContainer[i].pixels[j][k] = pArr[j][(((header_dib->width/THREAD_COUNT) * i) - 1) + k]; // the subtraction needs to be modified
                            // this line is definitely wrong
                            //pArr[k][(((header_dib->width/THREAD_COUNT) * i) - 1) + j] = pContainer[i].pixels[k][j];
                            pArr[(((header_dib->width/tc) * i) - 1) + k][j] = pContainer[i].pixels[k][j];
                        }
                    }
                }
            }
        }
    //}
    // create new file by writing pixel information into new pixel array
    FILE* fOut = fopen(outputFileName, "wb");
    printf("writing BMP header\n");
    writeBMPHeader(fOut, header);
    printf("writing DIB header\n");
    writeDIBHeader(fOut, header_dib);
    printf("writing pixels\n");
    // changed pContainer->pixels (2nd parameter) to pArr
    writePixelsBMP(fOut, pArr, header_dib->width, header_dib->height); // accessing modified pixel array in pContainer to write that info to new file
    printf("success\n");
    fclose(fOut);
}