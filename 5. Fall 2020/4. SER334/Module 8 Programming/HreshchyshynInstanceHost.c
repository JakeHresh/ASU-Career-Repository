/**
 * The Instance Host is responsible for processing requests from the Load Balancer
 * as threads. Each generated thread iterates over the sent job list and calculates
 * the square of the data contained in each job.
 * 7.5 hours total project
 * @author Jacob Hreshchyshyn
 * @version 1
 */
#include "InstanceHost.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
struct host{
    struct job_node* job_list;
    pthread_mutex_t lock;
};

//Initializes host environment
host* host_create()
{
    host* h = (host*)malloc(sizeof(host));
    pthread_mutex_init(&h->lock, NULL);
    return h;
}

//Shuts down host environment
void host_destroy(host** h)
{
    free(*h);
}
//Runner function to compute thread batch values
void* runner(void* param)
{
    host* server_instance = (host*)param;
    pthread_mutex_lock(&server_instance->lock);
    struct job_node* current = server_instance->job_list;
    while(current != NULL)
    {
        *(current->data_result) = current->data * current->data;
        current = current->next;
    }
    pthread_mutex_unlock(&server_instance->lock);
}

//Creates new server instance in batch
void host_request_instance(host* h, struct job_node* batch)
{
    host* server_instance = h;
    server_instance->job_list = batch;
    pthread_t thread;
    pthread_create(&thread, NULL, &runner, (void*)server_instance);
    pthread_join(thread, NULL);
}