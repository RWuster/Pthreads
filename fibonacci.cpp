/*
Richard Vu
Dr. Lakhanpal
CPSC 351 - 02
Project 2: Fibonacci Sequence using multithreading
*/
#include <iostream>
#include <vector>
#include <pthread.h>


int fiboRange;
size_t size;

void *fiboSequence(void * arg);

int main(int argc, char *argv[]){

    //first verify argument list
    if(argc < 2){
        std::cerr << "Wrong number of input.\n";
        return 1; 
    }
    size = atoi(argv[1]);
    std::vector<int> fiboList;
    //fiboList.reserve(size + 1);

    pthread_t fiboThread;

    pthread_create(&fiboThread, NULL, fiboSequence, &fiboList);

    pthread_join(fiboThread, NULL);

    for(size_t i = 0; i < fiboList.size(); i++){
        std::cout << fiboList.at(i) << " "; 
    }
    std::cout << std::endl;
}


void *fiboSequence(void * arg){
    std::vector<int> * v = static_cast<std::vector<int> *>(arg);
    int first = 0;
    int second = 1;

    //first add first, second into list
    v->push_back(first);
    v->push_back(second);
    int nextNum;
    int count = v->size();
    while(count < size){
        nextNum = first + second;
        first = second;
        second = nextNum;
        v->push_back(nextNum);
        count++;
    }

}