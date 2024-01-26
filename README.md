# Sokoban_extend
This game is an extension of the Sokoban game. If you don't know Sokoban, please refer to this link(https://en.wikipedia.org/wiki/Sokoban).

The winning condition of this game is to score points by putting the items that exist on the map into your base. 

Contributor
- Jeongwon: https://github.com/AlwaysEden?tab=repositories
- Sanghoon: https://github.com/DoBest20
- Jinju: https://github.com/leeejjju 
- Yeonhui: https://github.com/yeooooooni

## Build
- GNU Make
- cJSON.h
- Gtk 2.0
- gcc
- AFL(If you would like to fuzz)

## Software Background
The game is built based on the Server-Client network structure. The game also consists of MVC patterns, which are data in Json file format in Model, GUI in gtk in View, and Controller is a server that echoes with clients. Therefore, if you want to change the default settings for this game, you can change the Json file. 

Server is just Controller doing echo. Therefore, server receive the request from a client and send the received data to all client.  Client consists of Multi-thread. One thread receive the echo data from the server and another thread deals with the received data for Model.

You need to check the enviroment using gtk 2.0. We've checked X11 to play game in Mac OS. If you are Window user, you can play game with Mobaxterm.

## In Game
<img src= https://github.com/AlwaysEden/Sokoban_extend/blob/main/gamePlay.png>
