#include <iostream>
#include <pthread.h>

int average;
int min;
int max;

int size = 0;
void *calcMin(void *arg);
void *calcAvg(void *arg);
void *calcMax(void *arg);

int main(int argc, char *argv[]){

    //initialize an aray of the integers to be ppassed
    //using malloc in c is equivalent to "new int" in c++
    int * nums = (int *)malloc((argc - 1)*sizeof(int));
    //i = 1, since argument list includes the name of the executable
    int i = 1;

    std::cout << "Argument list is: ";
    for(i; i < argc; i++){
        std::cout << argv[i] << " ";
        nums[i - 1] = atoi(argv[i]);
        size++;
    }
    std::cout << std::endl;
    //thread identifier
    pthread_t avgThread;
    pthread_t minThread;
    pthread_t maxThread;

    pthread_create(&minThread, NULL, calcMin, (void *)nums);
    pthread_create(&avgThread, NULL, calcAvg, (void *)nums);
    pthread_create(&maxThread, NULL, calcMax, (void *)nums);

    pthread_join(minThread, NULL);
    pthread_join(avgThread, NULL);
    pthread_join(maxThread, NULL);

    printf("Average = %d\n", average);
    printf("Min = %d\n", min);
    printf("Max = %d\n", max);
    free(nums);

}

void *calcAvg(void * arg){
    int *val_p = (int *) arg;

    int sum = 0;
    int i = 0;

    for(i; i < size; i++){
        sum += val_p[i];
    }
    std::cout << "Sum is " << sum << std::endl;
    average = sum / size;
    pthread_exit(0);
}

void *calcMin(void * arg){
    int *val_p = (int *)arg;

    min = val_p[0];

    int i = 1;

    for(i; i < size; i++){
        if(min > val_p[i]){
            min = val_p[i];
        }
    }
}

void *calcMax(void * arg){
    int *val_p = (int *)arg;

    max = val_p[0];

    int i = 1;

    for(i; i < size; i++){
        if(val_p[i] > max){
            max = val_p[i];
        }
    }
}