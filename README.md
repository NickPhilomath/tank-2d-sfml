# tank-2d-sfml
online tank game made with C++ libraries SFML and eNet

![image_2023-06-04_09-21-48](https://github.com/NickPhilomath/tank-2d-sfml/assets/123894019/9a1cca2e-ae46-46f4-9d01-98c7e1029ce3)

## how it works 
repository includes 2 projects: server and client 

player communicates as `Peer-to-Peer` client , sends input updates to server and server side world will be updated

server takes snapshot of the world and shares with players 30 times per second 

## how to install 

unfortunately project is designed in windows platform. 

to run the code, simply clone the repository `git clone https://github.com/NickPhilomath/tank-2d-sfml` 

and open `tank-2d-online.sln` solution file


feel free to play around with!
### @NickPhilomath
