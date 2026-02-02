# Philosophers
A thread management exercise, to learn about data races, dead locks and multhreading logic. Based on the dining philosophers we are supposed to simulate a dinner, where a variable ammount of philosophers need to stay alive by not starving, the catch? There is only one fork per philosopher, which they share with the philosopher in their right and need two to begining eating not being able to talk to each other. If one of them die or they have eaten enough times, the simulation ends.

## Main Logic
First we need to parse the arguments that the program takes:
  - Number of philosophers
  - Time to die
  - Time to eat
  - Time to sleep
  - (optional) number of times each philosopher must eat

In this exercise a philosopher is a thread and a fork is a mutex.

Since only one philosopher can have a fork at a time, each time a philosopher wants to eat we lock their forks, each in a different order so we dont end up causing a dead lock. When they have both forks the philosopher starts eating, releasing them after for the other philosphers. After eating they go to sleep, and when they wake up the cycle repeats.

Since locking a mutex it makes the thread wait if the mutex is not availale it makes the thread behaviour quite simple, just lock and unlock when they start/finish eating. 

**But how we check if any of them has died?**

For this we use the main thread to check if the time since last they ate isn't bigger than the time to die, if it is we finish the simulation, by setting a end flag to true. This end flag is also checked before printing and in each iteration of the philo loop logic to ensure that the simuation ends when one of them dies. 
