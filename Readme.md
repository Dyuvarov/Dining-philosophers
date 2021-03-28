# Introduction
Dining philosophers problem illustrates synchronization issues in concurrent algorithm. Here you can see how different threads or processes works with same resources in the same time.
Here the detailed article on [Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

## What about
* Thread
* Mutex
* Semaphore

# Follow me:stuck_out_tongue_winking_eye:
inst: [@dyuvarov](www.instagram.com/dyuvarov/)

# Main Part
Philosophers can eat, sleep and think. Each philosopher can do only one action in the same time (cant eat and think at the same time or sleep and think etc.).

Each philosopher needs 2 forks to eat.
If philosopher able to take 2 forks, he starts eating. 
After eating he will sleep.
After sleeping he will think until he can take 2 forks and start eating.
If a philosopher starves too long he will die.

##### :fork_and_knife: philo_one: 
* There are one fork between 2 philosophers (number of philosophers == number of forks)
* Each philosopher - thread
* Each fork - mutex

##### :fork_and_knife: philo_two:
* All forks in the middle of table (number of philosophers == number of forks)
* Each philosopher - thread
* Forks controlling by semaphore

##### :fork_and_knife: philo_three:
* All forks in the middle of table (number of philosophers == number of forks)
* Each philosopher - separate process (not thread now)
* Forks controlling by semaphore

The difference between philo_two and philo_three is in philosophers creation.
Threads works with the same data and if you will change something in one thread, another thread will see changes.
But different processes works with their own data and if you will change, for example, status of one philosopher in current process, 
another philosopher (in his own process) will not see this changes. 

# How to launch
There are three different cases: philo_one, philo_two, philo_three (read explanation in main part). 

There is Makefile in each directory to create launch file. You can use command "make" to compile and create the launch file.

To start simulation run the launch file (./philo_one/ or ./philo_two or ./philo_three) with following arguments:
1) number of philosophers - how many philosophers will sit around the table.
2) lifetime (milliseconds) - how long philosopher can live since the start of last meal.
3) time to eat (milliseconds) - how long does it take for a philosopher to eat
4) time to sleep (milliseconds) - how long does it take for a philosopher to sleep
5) (OPTIONAL) number of times each philosopher must eat - if all philosophers eat at least the "number of times each philosopher must eat" simulation will stop. If not specified, the simulation will stop only at the death of a philosopher. 