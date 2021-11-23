# 42HN_Philosophers

A 42 project that involes threading a process with mutexes to solve <a href="https://en.wikipedia.org/wiki/Dining_philosophers_problem">dining phisolosophers problem</a>.

## Run Project on MAC
* Clone or fork this repository
* Type ```make``` command in the terminal
* Execute program with the created variable and appropriate argument values

## Meaning of arguments

* 1st argument: numbers of philosophers
* 2nd argument: time to start eating after the beginning of the last meal (or start of the program) in order to survive
* 3rd argument: time to eat
* 4th argument: time to sleep
* 5th argument (optional): number of required meals per philosopher (program stops after the number is reached)

Example: ```./philo 2 410 201 200 3``` <br>
Explanation: 2 philosophers would try to fit eating (201ms) and sleeping (200ms) in 410ms. The program would terminate after <br> 
  both philosophers have eaten for three times or the occurence of the first death (inability to fit eating and sleeping in a given time).
