/**
 * The Load Balancer is responsible for accepting user threads and storing the user thread
 * data in a job list. Once enough jobs have been stored in the list, a host request is made
 * to process the thread data.
 * 7.5 hours total project
 * @author Jacob Hreshchyshyn
 * @version 1
 */
#include "LoadBalancer.h"
#include "InstanceHost.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct balancer{
    struct job_node* job_list;
    int batch_size;
    int batch_iterator;
    int added;
    pthread_mutex_t lock;
};

//Initializes load balancer
balancer* balancer_create(int batch_size)
{
    struct balancer* b = (balancer*)malloc(sizeof(balancer) * batch_size);
    for(int i = 0; i < batch_size; i++)
    {
        b[i].batch_size = batch_size;
        b[i].batch_iterator = batch_size;
        b[i].job_list = NULL;
        b[i].added = 0;
    }
    pthread_mutex_init(&b->lock, NULL);
    return b;
}

//Shuts down load balancer
void balancer_destroy(balancer** lb)
{
    struct balancer* b = *lb;
    for(int i = 0; i < b->batch_iterator; i++)
    {
        // creates host for job list if not already added
        if(b[i].batch_size > 0 && b[i].added == 0)
        {
            b[i].added = 1;
            //printf("LoadBalancer: Received batch and spinning up new instance.\n");
            host* h = host_create();
            host_request_instance(h, b[i].job_list);
            // prints results of job list while deallocating
            while(b[i].job_list != NULL)
            {
                struct job_node* tracker = b[i].job_list;
                //printf("User #%d: Received result from data=%d as result=%d.\n", (int)tracker->user_id, tracker->data, *(tracker->data_result));
                //free(tracker->data_result);
                b[i].job_list = b[i].job_list->next;
                free(tracker);
                tracker = NULL;
            }
            host_destroy(&h);
        }
        // deallocates job list if batch size = 0
        else if(b[i].batch_size <= 0)
        {
            while(b[i].job_list != NULL)
            {
                struct job_node* tracker = b[i].job_list;
                //free(tracker->data_result);
                b[i].job_list = b[i].job_list->next;
                free(tracker);
                tracker = NULL;
            }
        }
    }
}

//Adds job to load balancer
void balancer_add_job(balancer* lb, int user_id, int data, int* data_return)
{
    pthread_mutex_lock(&lb->lock);
    printf("LoadBalancer: Received new job from user #%d to process data=%d and store it at %p.\n", user_id, data, data_return);
    for(int i = 0; i < lb->batch_iterator; i++)
    {
        //printf("LoadBalancer: Received new job from user #%d to process data=%d and store it at %p.\n", user_id, data, data_return);
        if(lb[i].batch_size > 0)
        {
            lb[i].batch_size--;
            struct job_node* current = lb[i].job_list;
            if(current == NULL)
            {
                lb[i].job_list = (struct job_node*)malloc(sizeof(struct job_node));
                lb[i].job_list->user_id = user_id;
                lb[i].job_list->data = data;
                lb[i].job_list->data_result = data_return;
                break;
            }
            else
            {
                while(current != NULL)
                {
                    if(current->next == NULL)
                    {
                        current->next = (struct job_node*)malloc(sizeof(struct job_node));
                        current->next->user_id = user_id;
                        current->next->data = data;
                        current->next->data_result = data_return;
                        break;
                    }
                    else
                    {
                        current = current->next;
                    }
                }

            }
            if(lb[i].batch_size <= 0 && lb[i].added == 0)
            {
                lb[i].added = 1;
                printf("LoadBalancer: Received batch and spinning up new instance.\n");
                host* h = host_create();
                host_request_instance(h, lb[i].job_list);
                host_destroy(&h);
            }
            break;
        }
    }
    pthread_mutex_unlock(&lb->lock);
}