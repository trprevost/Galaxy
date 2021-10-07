# 2D Solar Systems multithreading simulation 

This project works with SDL2 and OpenMP.\
to compile easily: \
gcc *.c -o galaxy.out -fopenmp -lm $(sdl2-config --cflags --libs -ldl )

## Summary
## 1. Why this project
## 2. Keys
## 3. Optimizations, Tests and Results
&nbsp;\
&nbsp;\
&nbsp;


## 1. Why this project
With this project I wanted to work on a small 2D graphical simulation, then to be able to optimize and accelerate it.
## 2. Keys
- pause: P
- move: arrows keys
- zoom / dezoom: z / s or + / - from keypad
## 3. Optimizations, Tests and Results
Once the project was functional, I wanted to parallelize the gravitation calculations.
How to do it?
First of all we need to calculate the time when the program is calculated on a single thread.\
Each test is done on the same pc with an Intel Core i5-8300 2.30GHz. 
A test computes 2000 iterations of 600 stars, each star computes its acceleration thanks to the 599 other stars: it is a O(n²) complexity

### Tests:
1 thread, basic algorithm: 19.15"

### OpenMP and Optimizations
With omp task\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;    1 thread : 20.17"\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;    4 threads : 26.61"\
it seems that the extra cost of the creation and distribution of tasks is more important than the computation time of these tasks: this approach does not seem interesting in our case.

With omp for\
The Schedule: static is the best: each iteration represent the same amount of computation.\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;    1 thread: 16.85"\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;    2 threads: 13.41"\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;    4 threads: 10.58"\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;    6 threads: 10.12"\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;    8 threads: 9.82"  -> best one\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;    10 threads: 9.90"

Fine, we divided the time by two. But we can do better.\
We could parallelize the display, however it is better to avoid displaying a maximum of them by displaying only the stars whose coordinates are on the screen.
With this and 8 threads, we reach 8.60"\

Planets don't have a huge mass, so between 2 planets which are far away from each other, their attraction is close to 0. Let's add a pseudo tile optimization: before computing attraction between 2 planets the program compute in which tile the two planets are, if they are in the same tile or a &nbsp;neibor, we compute attraction, otherwise we don't. 
The speedup is significant: 5.73", we have a 3.34 speedup
 



