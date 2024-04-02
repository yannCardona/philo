# PHILOSOPHERS PROJECT

![An_illustration_of_the_dining_philosophers_problem](https://github.com/yannCardona/philo/assets/119678666/70cc28a0-ffd2-497c-b927-5462329ce001)

here is the full subject description: [Uploading en.subject.pdf…]()

"Five philosophers dine together at the same table. Each philosopher has his own plate at the table. There is a fork between each plate. The dish served is a kind of spaghetti which has to be eaten with two forks. Each philosopher can only alternately think, eat and sleep. Moreover, a philosopher can only eat his spaghetti when he has both a left and right fork. Thus two forks will only be available when his two nearest neighbors are not eating. After an individual philosopher finishes eating, he will put down both forks. The problem is how to design a regimen (a concurrent algorithm) such that any philosopher will not starve."

The Project is written in C. I have implemented two solutions - one using threads and mutexes and one using child processes and semafores.

The Program takes the following arguments:
number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
- number_of_philosophers: The number of philosophers and also the number
of forks.
- time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
- time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
- number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.
  
  allowed functions for solution with Threads: memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create,
  pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock,
  pthread_mutex_unlock

  allowed functions for solution with Child Processes: memset, printf, malloc, free, write, fork, kill,
  exit, pthread_create, pthread_detach, pthread_join, usleep, gettimeofday, waitpid, sem_open, sem_close,
  sem_post, sem_wait, sem_unlink
  
