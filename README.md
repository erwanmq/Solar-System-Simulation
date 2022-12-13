# Solar System Simulation

![image](https://user-images.githubusercontent.com/93351393/206564100-893620eb-44a4-4a0f-b4c5-0f67377b737e.png)

## What is my project?
The project is a Solar system simulation using SFML, for now we can just zoom, dezoom from a planet we choosed, see the time and change the speed of it. 
The scale is **the real scale** of the universe. The distance are respected and the size of the planets are the real values.
There are the 8 planets and pluto.
The numbers next to the planet are the distance to the Sun in AU (astronomical unit)

## How works my simulation?
The simulation use **the real values** in the space (real size and real distance). To draw them on a window I had to scale them. I used a basic formula to draw the earth at 250 pixels to the sun. 
The size can be modify by using the scroll wheel, we can see how huuuge is the solar system.
![image](https://user-images.githubusercontent.com/93351393/206922344-dadb1edf-6742-4506-be3c-53e2f4c12549.png)
![image](https://user-images.githubusercontent.com/93351393/206921919-effa8a5b-9464-438c-9837-73de0cf89611.png)
Each frame, the program calcul the forces applied to each planet and with the Newton laws we can set the speed of each planets. But if we increase the timestep at a big value, the program can't calculate each forces and causes problems to the simulation.

## What are the next updates?
My project is to have a HUD where we could choose a mass, a size, a color or anything else, place it on the solar system and see what do our planet. Destroy our orbits? See the Earth leave? The sun go at 100km/s?
So for the next updates I will had some buttons to create our own planet and see how works our solar system.
I want to add some design like real planet image (because for the moment it's just circles :unamused:)

## What are the problems?
There is still some bugs that I need to work on.
For this moment there is a major bug, when we zoom in, the planet is further than the view. But if we stop the time it works.
The drawings of the orbits far from the sun are ugly but I will work on it soon.
      


![image](https://user-images.githubusercontent.com/93351393/206564147-c38b1863-fd1f-4c46-8ad2-aab89a69515e.png)
