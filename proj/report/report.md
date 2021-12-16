
## Introduction
The computation that was chosen was that of a simulation.
This simulation is a Pulse Aptitude Modulation (PAM) with a AWGN channel.
This was chosen as it was a simple but also embarrassingly parallel.
The simulation is embarrassingly parallel because the is no interdependencies between simulations.
Each simulation is independent, this allows for any number of different simulations to be ran at once.    
 
## Overview of pthreads in simulation
![alt text](pthreads-PerSNR.drawio.png "Title")  
As seen in the above figure the simulation is broken down into a per snr basis. 

![alt text](pthreads-pthreads.drawio.png "Title")  
In the above figure one can see that each thread gets a que of signals to process.

The pthread specific functions that are used are *pthread_create()*, *pthread_barrier_init()* and *pthread_barrier_wait()*.
* *pthread_create()* is called with _pthread_create(&threads[i], NULL, Sim, (void *)&data[i])_.
  * Gives the function the thread to execute instructions on, the function to call and the data to pass it
  * Here the data is a que of signals to simulate
  * Here each thread will process each que it is given
* The *pthread_barrier_init()* is called with _pthread_barrier_init(&barrier, NULL, num_threads + 1)_.
  * This initializes the barrier with the number of times to call the barrier before the simulation is allowed to continue.
  * Initialized to be the number of threads + 1 to allow the all the threads to finish and for the program to wait until this happens
* The *pthread_barrier_wait()* is called with _pthread_barrier_wait(&barrier)_.
  * Calls the barrier and has the thread wait until the barrier has been called enough times
  * This makes sure all the simulations finish before the results print

In order to vary the number threads each thread gets a que of simulations (signal structure) to execute.
Each que has approximately the same number of simulations as each simulation is assigned based on the modulus of the index and the number of threads.
This type of queuing allows to only spawn the number threads specified versus in previous implementations spawning the number of different simulations but only allowing the number of threads to execute at once.



## Overview of mpi in simulation
## Results
![alt text](r5.png "Title")
There was only one consistent non negative scaling.
I believe this was due to clock speed scaling on my laptop.
It would not boost unless it had at least 2 threads running.     

## Discussion
