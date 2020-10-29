#include <iostream>
#include <vector>
#include <pthread.h>
#include <string>


int listRange;
void *listPrimes(void *arg);
int main(int argc, char *argv[]){

     if(argc < 2){
       std::cerr << "Wrong values of input: ";
       return 1;
   }
    std::vector<int> primes;
    listRange = atoi(argv[1]);
    pthread_t primeThread;

    pthread_create(&primeThread, NULL, listPrimes, &primes);
    pthread_join(primeThread, NULL);

    for(size_t i = 0; i < primes.size(); i++){
        std::cout << primes.at(i) << " ";
    }
    std::cout << std::endl;
    return 0;
}

void *listPrimes(void *arg){
    std::vector<int> * v = static_cast<std::vector<int> *>(arg);
    int num, i, count;
    
    for(num = 1; num <= listRange; num++){
        count = 0;
        for(i = 2; i <= num / 2; i++){
            //std::cout << num << "    " << i << std::endl;
            if(num % i == 0){
                //count++, so if its a composite number, the print function on line 21 does not run. 
                count++;
                break;
            }
        }
        if(count == 0 && num != -1){  
            v->push_back(num);
        }
    }
}




/*
num = 1;
inner loop: (i = 2; i <= 1 / 2; i++) => evaulates to false since 2 <= 1 is false, so adds 1
num = 2:
inner loop: (i = 2; i <= 2/2; i++) => evaulates to 2 <= 1, false, so adds 2
num = 3:
inner loop: I = 2; i <= 3/2; i++) => evaluates to 2 <= 1, false, so adds 3
num = 4:
inner loop: i = 2, i <= 4/2; i++ => evaulates to true, so count++; count = 1; fails to if(count == 0), so does not add 4
num = 5;
inner loop: i = 2; i <= 5/2; i++ => evaluates to true. if(num % i == 0) => (5 % 2 == 0), false, (5%3 == 0), false, so adds 5 since count does not incrememnt.

num = 17;
inner loop: i = 2; i <= 17/2; i++; i<= 8; check (17 % 2 ), (17 % 3), (17 % 4), (17 % 5), (17 % 6), (17 % 7), (17 % 8); all of this test case fails, so count stays 0.
        - therefore its printed out.

if its a composite, or divisble by 2, count is incremented and breaks out of the loop. checks to see if(count == 0), which is not so moves on. 
*/