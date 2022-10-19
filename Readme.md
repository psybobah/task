General info
------------
The repository contains a task needed to apply for a job.

Build
------------

#### Installation of Environment on Linux PC

- Install environment using commands bellow:
```
sudo apt install g++
sudo apt-get install cmake
sudo apt-get install libgtest-dev
sudo apt-get install libgmock-dev
```

- Build project
```
cmake -S . -B build && cmake --build build
```

Run
------------

Run unit tests using following command:
```
cd build && ctest -V && cd -
```

Run task usng command:
```
build/task
```

Good luck!
