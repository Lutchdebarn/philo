*This project has been created as part of the 42 curriculum by Lutchdebarn.*

# Philosophers

## Description
The **Philosophers** project is an introduction to the basics of process threading and the use of mutexes. It is a simulation based on the "Dining Philosophers Problem," a classic synchronization puzzle.

The goal is to manage multiple threads (representing philosophers) sitting at a round table, alternating between eating, thinking, and sleeping. The challenge lies in distributing limited resources (forks) represented by mutexes to prevent **deadlocks** and **data races**, ensuring that no philosopher dies of starvation during the simulation.

## Instructions

### Compilation
The project includes a `Makefile` that supports the standard rules. To compile the mandatory part, run:

```bash
make
If you wish to compile the bonus part, use:

Bash

make bonus
Execution
The program is executed with the following arguments:

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

Example:
./philo 5 800 200 200

number_of_philosophers: The number of philosophers and also the number of forks.

time_to_die (in ms): If a philosopher hasn't started eating within this time since their last meal, they die.

time_to_eat (in ms): The time it takes for a philosopher to eat.

time_to_sleep (in ms): The time a philosopher spends sleeping.

number_of_times_each_philosopher_must_eat (optional): If all philosophers eat at least this many times, the simulation stops.

Resources
References
The Little Book of Semaphores (Allen B. Downey) - Theoretical background on synchronization.

Philosophers 42 Guide (ruinadd on Medium) - Conceptual approach to the problem.

CodeQuoi - Documentation on threads, mutexes, and concurrent programming in C.

Oceano's Notion - Comprehensive guide on the project logic.

CodeVault & Oceano (YouTube) - Video tutorials on pthread functions and implementation strategies.

AI Usage
Artificial Intelligence was used during this project for the following tasks:

Conceptual Understanding: Clarifying the behavior of system functions such as pthread_create, pthread_mutex_lock, and gettimeofday.

Debugging: Assisting in the identification of potential data races and edge cases.

Documentation: Structuring and refining the content of this README file to meet the subject requirements.

Features
One thread per philosopher.

Mutexes to protect each fork and shared data.

Precise timestamping of every state change (eating, sleeping, thinking, or dying).

Optimized to prevent unnecessary CPU usage.
