# IndieStudio
The IndieStudio is a remake of bomberman which is made in C++ and using SFML, it allows you to play against AI on differents maps which can be automaticaly generated with a simple click so you won't be playing twice on the same map.

The goal was to work on the generation part of the world only with the use of **SFML** and **GLFW** and **Irrlicht**.

*The project works with the use of make so only for Linux*


To compile the project you will have to install dependancies first:

Install **make**:

```
sudo apt-get install make
```

Install **cmake**:

```
sudo apt-get install cmake
```

Install **g++**:

```
sudo apt-get install g++
```

Install **SFML**:

```
sudo apt-get install libsfml-dev libsfml-doc
```

Install **build-essential**:

```
sudo apt-get install build-essential
```

Install **Glfw**:

```
sudo apt-get install libgl1-mesa-dev xorg-dev
```

Install **Irrlicht**:

```
sudo apt-get install libirrlicht-dev
```

After all the installations you can *compile* with:
```
sh clean_cache.sh
cmake .
make
```

Now just launch and have fun with:
```
./bomberman
```
