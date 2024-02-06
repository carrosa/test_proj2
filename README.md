# Run
Make sure you have cmake (version >= 3.27) installed on your system.
Hopefully everything else you need to run this should be fixed by cmake.
```bash
mkdir build && cd build && cmake -S .. -B . && make && ./primality_tests && ./find_primes
```