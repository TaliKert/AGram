# AGram

Competition "entry"

Unfinished. Leaky memory. Out of time.

build with
```
gcc main.c
```

My idea was assinging letters a prime number and calculating their hash by multiplying them. Holding them in an array and accessing them by the character byte value as index should have great potential to keeping any access times low and the operations simple.

Ideally there should be no overlap for the hashes, as different combinations of letters shouldn't get the same hash because of the mathematical property of prime numbers to not be a product of any other numbers but themselves and 1. That should also apply for the products of used primes.

Java was my first choice but yielded a slow speed.

This C implementation has a promising execution time but I couldn't make it before the deadline for my poor skills in the language.
