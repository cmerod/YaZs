# YaZs
School project, creating a multiplayer game


The task was given at the end of the first year of my education at KTH.

The requirements was to create a multiplayer computer game that implemented either TCP or UDP.
A team of six students used C with the SDL library to create the game in less than three moenths.

The result was YaZs or Yes another Zombie shooter. A 2d top down zombie horde survival. 
Up to four players are tasked with surviving hordes of zombies for a set amount of time. 
The players have a close combat weapon and a limited supply of hitpoints. Surviving the horde 
moves the players to the next map.

The Server and Client folders contain the c and h files. Feel free to look at the code.

YaZs_MAC and YaZs_WIN folders contain compiled versions of the game. You try out the game using one of these folders. 
You launch the game by executing YaZsClient. This will bring you to the menu. Press play to start a session. It is possible to play solo, just press host when given the option. This will start the server in the background. A maximum of three more players can join in by entering the hosts IPv4 address. Recommended to try out multiplayer within a private network since we never took the time to make the game work accross different networks. 
