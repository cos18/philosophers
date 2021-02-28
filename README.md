# Philosophers

This project handles the basics of threading a process, how to work on the same memory space and how to make threads. This project will discover the mutex, semaphore and shared memory.

### 🎯 Object

Implement [Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) in THREE different way!

#### `philo_one`
philosopher with threads and mutex

- One fork between each philosopher, therefore there will be a fork at the right and at the left of each philosopher.
- To avoid philosophers duplicating forks, you should protect the forks state with a mutex for each of them.
- Each philosopher should be a thread.

#### `philo_two`
philosopher with threads and semaphore

- All the forks are in the middle of the table.
- They have no states in memory but the number of available forks is represented by a semaphore.
- Each philosopher should be a thread.

#### `philo_three`
philosopher with processes and semaphore

- All the forks are in the middle of the table.
- They have no states in memory but the number of available forks is represented by a semaphore.
- Each philosopher should be a process and the main process should not be a philosopher.

### 💻 How to Run

> 🚨 Before running, `docker`, `minikube`, `kubectl` and `VirtualBox` are installed in local enviroment.

```bash
$ cd philo_x
$ make
$ ./philo_x number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
