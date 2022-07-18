/**
 * This program utilizes a Tick struct to simulate a batch
 * of processes to run. The program will store processes corresponding
 * to a Tick to a corresponding Tick struct. The stored information
 * will be the burst time of each process, which will be used to calculate
 * the process turnaround time and waiting time. Schedule simulation will be performed
 * using an SJF and SJFL approach.
 *
 * NOTE: The program works, as long as there are no empty lines near the end
 * of the files.
 *
 * Completion time: 6 hours
 * @author Jacob Hreshchyshyn
 * @version 1.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tick{
    // needs multiple process bursts to be stored
    // in a single tick.
    float* processT;
    // needs one Tau variable since, for each tick,
    // the Tau is modified to create a new Tau.
    float* processTau;
    // needs one process alpha which will not change.
    float* processAlpha;
};

struct Tick* tickArr;

int main(int argc, char* argv[]) {
    char* inputFileName = argv[1];
    FILE* file_input;
    file_input = fopen(inputFileName, "r");
    if(file_input == NULL)
    {
        printf("Error. File not found.\n");
        exit(1);
    }
    char lineToRead[150];
    // read to find the number of ticks
    fgets(lineToRead, 150, file_input);
    int tickCount = atoi(lineToRead);
    tickArr = (struct Tick*)malloc(sizeof(struct Tick) * tickCount);
    // read to find the number of process in each tick
    fgets(lineToRead, 150, file_input);
    int processCount = atoi(lineToRead);
    for(int i = 0; i < tickCount; i++)
    {
        tickArr[i].processT = (float*)malloc(sizeof(float) * processCount);
        tickArr[i].processTau = (float*)malloc(sizeof(float) * processCount);
        tickArr[i].processAlpha = (float*)malloc(sizeof(float) * processCount);
    }
    int tickIndex = 0;
    int tickTracker = 0;
    // get tick index to start reading for process 0
    // as it's reading, it increments the tick tracker
    // until the tracker equals the previously found tickCount.
    // the next tick index is read and the information is
    // stored in the next tick for process 1
    /*fgets(lineToRead, 150, file_input);
    tickIndex = atoi(lineToRead);*/
    // initially enters while loop in tick 0
    while(!feof(file_input))
    {
        fgets(lineToRead, 150, file_input);
        tickIndex = atoi(lineToRead);
        fgets(lineToRead, 150, file_input);
        float t = atof(lineToRead);
        for(int i = 0; i < tickCount; i++)
        {
            tickArr[i].processTau[tickIndex] = t/*atof(lineToRead)*/;
        }
        //tickArr[tickIndex].processTau = atof(lineToRead);
        fgets(lineToRead, 150, file_input);
        float a = atof(lineToRead);
        for(int i = 0; i < tickCount; i++)
        {
            tickArr[i].processAlpha[tickIndex] = a/*atof(lineToRead)*/;
        }
        //tickArr[tickIndex].processAlpha = atof(lineToRead);
        //REMEMBER TO BEGIN READING IN THOSE OTHER FILE VALUES
        //storing process bursts in ticks
        for(int i = 0; i < tickCount; i++)
        {
            fgets(lineToRead, 150, file_input);
            tickArr[i].processT[tickIndex] = atof(lineToRead);
        }
    }
    //ATTEMPT AT TAU CALCULATION
    for(int i = 0; i < tickCount; i++)
    {
        for(int j = 0; j < processCount; j++)
        {
            if(i != 0)
            {
                tickArr[i].processTau[j] = (tickArr[i - 1].processAlpha[j] * tickArr[i - 1].processT[j]) + ((1 - tickArr[i - 1].processAlpha[j]) * tickArr[i - 1].processTau[j]);
            }
        }
    }
    //printf("nextTau: %f\n", tickArr[0].processT[0] * tickArr[0].processAlpha[0] + (1 - tickArr[0].processAlpha[0]) *);
    /*for(int i = 0; i < tickCount; i++)
    {
        printf("Alpha: %f\n", tickArr[i].processAlpha);
        printf("Tau: %f\n", tickArr[i].processTau);
    }*/
    /*printf("%d\n", tickCount);
    printf("%d\n", processCount);
    for(int i = 0; i < tickCount; i++)
    {
        printf("%f\n", tickArr[i].processT[0]);
    }
    for(int i = 0; i < tickCount; i++)
    {
        printf("%f\n", tickArr[i].processT[1]);
    }
    for(int i = 0; i < tickCount; i++)
    {
        printf("%f\n", tickArr[i].processT[2]);
    }*/

    // All the information is read correctly. Now I need to calculate the
    // turnaround times and the waiting times for the tick processes.

    printf("==Shortest-Job-First==\n");
    float time = 0;
    float turnaroundTime = 0;
    float waitTime = 0;
    /*printf("%f\n", tickArr[0].processT[0]);
    printf("%f\n", tickArr[0].processT[1]);*/
    for(int i = 0; i < tickCount; i++)
    {
        printf("Simulating tick %d of processes at time %f:\n", i, time);
        // needs to retrieve the information stored in the process arrays, compare them
        // with each other, and print them out in the order where the smallest burst
        // is printed first, the next smallest next, and so on.
        float* burstArr = (float*)malloc(sizeof(float) * processCount);
        int* processIdArr = (int*)malloc(sizeof(int) * processCount);
        float* processTurnaroundTimes = (float*)malloc(sizeof(float) * processCount);
        for(int j = 0; j < processCount; j++)
        {
            //printf("%f\n", tickArr[i].processT[j]);
            burstArr[j] = tickArr[i].processT[j];
            processIdArr[j] = j;
        }
        for(int k = 0; k < processCount - 1; k++)
        {
            for(int l = 0; l < processCount - k - 1; l++)
            {
                if(burstArr[l] > burstArr[l + 1])
                {
                    float tempTime = burstArr[l];
                    burstArr[l] = burstArr[l + 1];
                    burstArr[l + 1] = tempTime;

                    int tempId = processIdArr[l];
                    processIdArr[l] = processIdArr[l + 1];
                    processIdArr[l + 1] = tempId;
                }
            }
        }
        processTurnaroundTimes[0] = burstArr[0];
        for(int x = 1; x < processCount; x++)
        {
            processTurnaroundTimes[x] = burstArr[x] + processTurnaroundTimes[x - 1];
        }
        for(int x = 0; x < processCount; x++)
        {
            printf("\tProcess %d took %f.\n", processIdArr[x], burstArr[x]);
            time += burstArr[x];
            turnaroundTime += processTurnaroundTimes[x];
            if(x != processCount - 1)
            {
                waitTime += processTurnaroundTimes[x];
            }
        }
        free(burstArr);
        free(processIdArr);
        free(processTurnaroundTimes);
    }
    printf("Turnaround time: %f\n", turnaroundTime);
    printf("Waiting time: %f\n", waitTime);
    printf("==Shortest-Job-First-Live==\n");

    float timeLive = 0;
    float turnaroundTimeLive = 0;
    float waitTimeLive = 0;
    float estimationError = 0;
    float* tau = (float*)malloc(sizeof(float) * processCount);
    for(int i = 0; i < tickCount; i++)
    {
        printf("Simulating tick %d of processes at time %f:\n", i, timeLive);
        float* burstArr = (float*)malloc(sizeof(float) * processCount);
        int* processIdArr = (int*)malloc(sizeof(int) * processCount);
        float* processTurnaroundTimes = (float*)malloc(sizeof(float) * processCount);
        float* estimationErrors = (float*)malloc(sizeof(float) * processCount);
        //float* tau = (float*)malloc(sizeof(float) * tickCount);
        //tau[0] = tickArr[i].processTau;
        float* alpha = (float*)malloc(sizeof(float) * processCount);
        // stores the bursts and id's of the processes to be used later when
        // calculating the estimation error
        for(int j = 0; j < processCount; j++)
        {
            //printf("%f\n", tickArr[i].processT[j]);
            burstArr[j] = tickArr[i].processT[j];
            /*if(j != 0)
            {
                tau[j] = (alpha[j] * tau[j - 1]) + ((1 - alpha[j]) * tau[j - 1]);
            }*/
            alpha[j] = tickArr[i].processAlpha[j];
            tau[j] = tickArr[i].processTau[j];
            processIdArr[j] = j;
        }
        for(int k = 0; k < processCount; k++)
        {
            for(int l = 0; l < processCount - k - 1; l++)
            {
                if(tau[l] > tau[l + 1])
                {
                    float tempTau = tau[l];
                    tau[l] = tau[l + 1];
                    tau[l + 1] = tempTau;

                    float tempTime = burstArr[l];
                    burstArr[l] = burstArr[l + 1];
                    burstArr[l + 1] = tempTime;

                    int tempId = processIdArr[l];
                    processIdArr[l] = processIdArr[l + 1];
                    processIdArr[l + 1] = tempId;
                }
            }
        }
        processTurnaroundTimes[0] = tau[0]/*burstArr[0]*/;
        for(int x = 1; x < processCount; x++)
        {
            processTurnaroundTimes[x] = tau[x]/*burstArr[x]*/ + processTurnaroundTimes[x - 1];
        }
        for(int x = 0; x < processCount; x++)
        {
            printf("\tProcess %d was estimated for %f and took %f.\n", processIdArr[x], tau[x], burstArr[x]);
            timeLive += burstArr[x];
            turnaroundTimeLive += processTurnaroundTimes[x];
            estimationErrors[x] = tau[x] - burstArr[x];
            if(estimationErrors[x] < 0)
            {
                estimationErrors[x] = estimationErrors[x] * (-1);
            }
            estimationError += estimationErrors[x];
            if(x != processCount - 1)
            {
                waitTimeLive += processTurnaroundTimes[x];
            }
        }
        free(burstArr);
        free(processIdArr);
        free(processTurnaroundTimes);
        free(estimationErrors);
        free(alpha);
    }
    printf("Turnaround time: %f\n", turnaroundTimeLive);
    printf("Waiting time: %f\n", waitTimeLive);
    printf("Estimation Error: %f\n", estimationError);
    for(int i = 0; i < tickCount; i++)
    {
        free(tickArr[i].processAlpha);
        free(tickArr[i].processT);
        free(tickArr[i].processTau);
    }
    free(tickArr);
    return 0;
}
