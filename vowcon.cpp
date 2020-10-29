/*
CPSC 351 - 02
Project 2: Part B - Determine if word starts with a vowel or consonant. 
*/
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <ostream>
#include <pthread.h>

//global variable, phrase is shared by the other threads
std::vector<std::string> phrase;
void *consonants(void * arg);
void *vowels(void *arg);
bool isVowel(char c);
int main(int argc, char * argv[]){

    if(argc < 2){
        std::cerr << "Invalid argument size.\n";
        return 1;
    }

    for(size_t i = 1; i < argc; i++){
        phrase.push_back(argv[i]);
    }

    for(const std::string &s : phrase){
        std::cout << s << " ";
    }
    std::cout << std::endl;
    //create two threads
    pthread_t vowelThread;
    pthread_t consonantThread;

    pthread_create(&vowelThread, NULL, vowels, &phrase);
    pthread_create(&consonantThread, NULL, consonants, &phrase);

    pthread_join(vowelThread, NULL);
    pthread_join(consonantThread, NULL);

}
bool isVowel(char c){
    if(c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'I' || c == 'i' || 
            c == 'O' || c == 'o' || c == 'U' || c == 'u'){
                return true;
    }else{
        return false;
    }
}

void *consonants(void * arg){
    //sched_yield();
    std::vector<std::string> * v = static_cast<std::vector<std::string> *>(arg);

    for(const std::string &s : *v){
         if(!isVowel(s[0])){
                 std::cout << "Consonant: " << s << std::endl;
        }
        else{
            usleep(1);
            
        }
        
    }
    pthread_exit(0);
}

void *vowels(void * arg){
    //sched_yield();
    std::vector<std::string> * v = static_cast<std::vector<std::string> *>(arg);
    
    for(const std::string &s : *v){
         if(isVowel(s[0])){
                 std::cout << "Vowel: " << s << std::endl;
        }
        
        else{
            usleep(1);
        }
        
    }
    pthread_exit(0);
}

/*
#include <unistd.h>
usleep() - this function suspends executing of the calling thread for a at least (usec) microsecond. 
*/