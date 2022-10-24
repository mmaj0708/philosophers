# philosophers
Philosophers is an individual project designed by 42 School to introduce to the concept of multi-threading.
How does multiple proccesses work on the same memory space ? What are mutexs ? Semaphores ? and shared memory ?
## Introduction
In computer science, the dining philosophers problem is often used to illustrate
synchronization issues and techniques for resolving them.

It was originally formulated in 1965 by Edsger Dijkstra as a student exam exercise, presented in terms of computers competing to access to tape drive peripherals.
Soon after, Tony Hoare gave the problem its present formulation.

## The simulation (Project duration : 2 week ⏳)
Philosophers are sitting at a round table with a big spaghetti plate in the middle and one fork for each of them.
They are either eating, thinking or sleeping. They need two forks to eat, so they need to borrow one from their neighboor.
Once done eating, they drop the forks to start sleeping. A philosopher is thinking whenever he is not eating or sleeping.
Communicating between them is forbidden, and they should avoid dying at any cost if they are not suppposed to.

### Installation 🖥
To test the project, cd to one of the folders philo_one, philo_two or philo_three and run make. Then, you can test the project using an executable.

usage :
```
./philo_one number_philosopher time_to_die time_to_eat time_to_sleep [number_of_time_each_philosophers_must_eat]
```
arguments in square brackets are not required

exemple :
```
./philo_one 3 500 200 200
```
output :

![output example](https://github.com/mmaj0708/philosophers/blob/master/output_test.png)
