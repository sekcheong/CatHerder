#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>   
#include <fcntl.h>
#include <semaphore.h> 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 4096

// Signal Handler for SIGINT 
void sigint_handler(int sig_num)
{
    // Reset handler to catch SIGINT next time.
    // Refer http://en.cppreference.com/w/c/program/signal 
    printf("\n User provided signal handler for Ctrl+C \n");

    // Do a graceful cleanup of the program like: free memory/resources/etc and exit 
    exit(0);
}


int main(int argc, char *argv[])
{
	signal(SIGINT, sigint_handler);

    // ftok to generate unique key 
    key_t key = ftok("dbgview", 75); 
  
    // shmget returns an identifier in shmid 
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT); 
  
    // shmat to attach to shared memory 
    char *str = (char*) shmat(shmid,(void*)0,0); 

    // initialize semaphores for shared processes 
    sem_t* sem = sem_open ("dbgview", O_CREAT | O_EXCL, 0666, 1); 
    if (sem==SEM_FAILED) {
    	printf("sem failed!\n");
    }
    // name of semaphore is "pSem", semaphore is reached using this name */
    sem_unlink ("dbgview");      
  
    std::cout << "Write Data : "; 
    gets(str); 
  
    printf("Data written in memory: %s\n",str); 
      
    //detach from shared memory  
    shmdt(str); 

    while (1) {
    	//printf("Inside program logic loop\n");
    }
  
    return 0; 
}


//Reader
// #include <iostream> 
// #include <sys/ipc.h> 
// #include <sys/shm.h> 
// #include <stdio.h> 
// using namespace std; 
  
// int main() 
// { 
//     // ftok to generate unique key 
//     key_t key = ftok("shmfile",65); 
  
//     // shmget returns an identifier in shmid 
//     int shmid = shmget(key,1024,0666|IPC_CREAT); 
  
//     // shmat to attach to shared memory 
//     char *str = (char*) shmat(shmid,(void*)0,0); 
  
//     printf("Data read from memory: %s\n",str); 
      
//     //detach from shared memory  
//     shmdt(str); 
    
//     // destroy the shared memory 
//     shmctl(shmid,IPC_RMID,NULL); 
     
//     return 0; 
// } 



// #include <stdio.h>          /* printf()                 */
// #include <stdlib.h>         /* exit(), malloc(), free() */
// #include <unistd.h>
// #include <sys/types.h>      /* key_t, sem_t, pid_t      */
// #include <sys/wait.h>
// #include <sys/shm.h>        /* shmat(), IPC_RMID        */
// #include <errno.h>          /* errno, ECHILD            */
// #include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
// #include <fcntl.h>          /* O_CREAT, O_EXEC          */

// #define SHARED_MEM_SIZE 64

// int main (int argc, char **argv){
//     int i;                        //loop variables 
//     key_t shmkey;                 //shared memory key       
//     int shmid;                    //shared memory id
//     sem_t *sem;                   //synch semaphore
//     pid_t pid;                    //fork pid                
//     int *p;                       //shared variable       
//     unsigned int n;               //fork count      
//     unsigned int value;           //semaphore value  

//     // initialize a shared variable in shared memory 
//     // valid directory name and a number 
//     shmkey = ftok ("/dev/null", 5);      
//     printf ("shmkey for p = %d\n", shmkey);
//     shmid = shmget (shmkey, SHARED_MEM_SIZE, 0644 | IPC_CREAT);

// 	// shared memory error check */
//     if (shmid < 0){                           
//         perror ("shmget\n");
//         exit (1);
//     }

// 	//attach p to shared memory */
//     p = (int *) shmat (shmid, NULL, 0);   
//     *p = 0;
//     printf ("p=%8x is allocated in shared memory.\n\n", *p);

//     /********************************************************/

//     // printf ("How many children do you want to fork?\n");
//     // printf ("Fork count: ");
//     // scanf ("%u", &n);

//     // printf ("What do you want the semaphore value to be?\n");
//     // printf ("Semaphore value: ");
//     // scanf ("%u", &value);

//     // initialize semaphores for shared processes */
//     sem = sem_open ("cat_dbg_view", O_CREAT | O_EXCL, 0644, value); 
//     // name of semaphore is "pSem", semaphore is reached using this name */
//     sem_unlink ("cat_dbg_view");      
//     /* unlink prevents the semaphore existing forever */
//     /* if a crash occurs during the execution         */
//     printf ("semaphores initialized.\n\n");

//     // /* fork child processes */
//     // for (i = 0; i < n; i++){
//     //     pid = fork ();
//     //     if (pid < 0)              /* check for error      */
//     //         printf ("Fork error.\n");
//     //     else if (pid == 0)
//     //         break;                  /* child processes */
//     // }


//     // /******************************************************/
//     // /******************   PARENT PROCESS   ****************/
//     // /******************************************************/
//     // if (pid != 0){
//     //     /* wait for all children to exit */
//     //     while (pid = waitpid (-1, NULL, 0)){
//     //         if (errno == ECHILD)
//     //             break;
//     //     }

//     //     printf ("\nParent: All children have exited.\n");

//     //      shared memory detach 
//     //     shmdt (p);
//     //     shmctl (shmid, IPC_RMID, 0);

//     //     /* cleanup semaphores */
//     //     printf("sem_destroy return value:%d\n", sem_destroy (sem));
//     //     exit (0);
//     // }

//     // /******************************************************/
//     // /******************   CHILD PROCESS   *****************/
//     // /******************************************************/
//     // else{
//     //     sem_wait (sem);           /* P operation */
//     //     printf ("  Child(%d) is in critical section.\n", i);
//     //     sleep (1);
//     //     *p += i % 3;              /* increment *p by 0, 1 or 2 based on i */
//     //     printf ("  Child(%d) new value of *p=%d.\n", i, *p);
//     //     sem_post (sem);           /* V operation */
//     //     exit (0);
//     // }
// }