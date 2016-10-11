Download Brian's SRT implementation using wget, which then saves
srt.tgz into whatever directory you want
unzip this file using
tar -xvf srt.tgz
which then makes a new directory in the home directory (or wherever)
Now we have all the files needed. We'll work with Makefile and main.c
edit the Makefile, adding -lpthread into the LDLIBS section next to -lm

Next, work on editing the main.c program to make multithreading possible
First, remove the code relate to
if (nthreads != 1)
bc we want to be able to make multiple threads to work on our process

All the work from
Vec3 camera_pos;
until
for (int i=0; i<3; i++)
    scaled_color[i] = max(min(scaled_color[i], 255) ,);

is the work that will be done by each thread, so put this into a new function
call this new function everytime pthread_create is called

two variables nthreads and scene are declared within main, but used by the
function I just made, so make these global variables (their values do not
matter, since they will be defined in main before this function is called)

for the code that the threads do, only changes needed is to specify the
scaled_color[pixel x][pixel y][0,1,2]
because the threads are working on different areas, not just row by row
which is what I think the current process is doing (and within that row doing
pixel by pixel)
fixing this, and then having the function return NUll makes it usable in main()

now edit the main function

allocate memory for the threads, and then call the threads passing in the
new function I made thread_work as parameter 3, and an integer as param 4
to keep track of what row to make the thread work on
join the threads
print (this is done using the old code, but scaled_color is modified)

upon running the make clean check
there seems to be a lot of differences between 1-test.ppm and baseline.ppm
BUT the differences are off by 1 digit, and the images themselves appear to
be almost identical (I cannot differentiate between the two) so I call this
a success

The real time (output by make clean check) for each thread as it compares
1,2,4,8 threads decreases dramatically as number of threads increase. As such,
the code apparently works, and accurately reflects that threads help increase
the speed at which processes are done. However, the number of threads would
eventually lead to diminishing returns, as the amount of time saved decreases
with every new thread made. 
