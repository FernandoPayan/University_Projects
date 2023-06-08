all: thread-create thread-create2 revised primes detached

thread-create: thread-create.c
	gcc -o thread-create thread-create.c -pthread

thread-create2: thread-create2.c
	gcc -o thread-create2 thread-create2.c -pthread

revised: thread-create2_revised.c
	gcc -o revised thread-create2_revised.c -pthread

primes: primes.c
	gcc -o primes primes.c -pthread

detached: detached.c
	gcc -o detached detached.c -pthread