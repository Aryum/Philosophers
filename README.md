# Philosophers

A 42 School project that solves the classic **Dining Philosophers** problem, tackling thread synchronization, mutexes, and race conditions in C.

## About

**Philosophers** is a concurrency and multithreading project from the 42 curriculum. The goal is to simulate a group of philosophers sitting around a table, alternating between eating, sleeping, and thinking, while sharing a limited number of forks with their neighbors.

The core challenge lies in coordinating access to shared resources (the forks) without causing:
- **Deadlocks** — philosophers waiting forever for a fork that will never become free
- **Data races** — unsynchronized access to shared state
- **Starvation** — a philosopher never getting the chance to eat

This project builds an understanding of process/thread management, mutexes, and precise timing — all implemented from scratch in C.

## How It Works

Each philosopher is represented by a thread. They repeatedly:
1. Pick up two forks (mutexes) — one on each side
2. Eat for a set duration
3. Put down the forks
4. Sleep
5. Think

A monitoring routine continuously checks whether any philosopher has starved (i.e., hasn't eaten within the allowed time) and stops the simulation if so.

## Usage

```bash
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Example:**
```bash
./philo 5 800 200 200
```

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) at the table |
| `time_to_die` (ms) | Time without eating before a philosopher dies |
| `time_to_eat` (ms) | Time it takes to eat |
| `time_to_sleep` (ms) | Time spent sleeping |
| `number_of_times_each_philosopher_must_eat` (optional) | Simulation stops once all philosophers have eaten this many times |
