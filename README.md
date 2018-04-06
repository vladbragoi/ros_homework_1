# ros_homework_1 #
##### Homework 1 [Laboratorio Ciberfisico] - University of Verona #####

### Rules (in italian) ###
*1.* Lo studente deve svolgere individualmente le attività previste nel testo dell’homework

*2.* Il codice dell’homework deve essere clonabile dal docente tramite un server Git

*3.* Il codice deve essere accompagnato da un file README.md contenente una descrizione della soluzione adottata per risolvere l’homework

### What it should do (in italian) ###
Si realizzi un package ROS contenente degli opportuni nodi 
per poter svolgere i compiti seguenti

* Un nodo pubblica, 1 volta al secondo, un messaggio contenente un nome, una età, e un corso di laurea 
* Un nodo permette di selezionare da tastiera quale parte del messaggio verrà mostrata a video (si veda la pagina seguente per i dettagli) 
* Un nodo mostra a video la parte del messaggio selezionata 

### Some information ###
**Before starting, you need to compile the package using the following command:**
```sh
catkin_make --pkg ros_homework_1
```
**Launch nodes using roslaunch command from your shell:**
```sh
roslaunch ros_homework_1 ros_tutorial1.launch
```
**or in addition (from your catkin_ws workspace) using a bash script:**
```sh
src/ros_homework_1/launch/launch.sh
```
Publisher, selector and visualizer nodes communicate with each other using topics as you see in the picture: <br/>

![](images/msg_vis_nodes.svg)
I used also another topic to send a "kill" message from selector node to publisher and visualizer nodes because of I want to stop them if user choose [q] option (just to quit from the program): <br/>

![](images/killtopic.svg)
<br/>...and then the final graph of the nodes execution is: 

![](images/full_process.svg)

### Author ###

* `Vladislav Bragoi`, University of Verona (Italy) [vladislav.bragoi@studenti.univr.it](mailto:vladislav.bragoi@studenti.univr.it)

### License ###

> MIT License
>
> Copyright (c) 2018 Vladislav Bragoi
> 
> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:
> 
> The above copyright notice and this permission notice shall be included in all
> copies or substantial portions of the Software.
> 
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
> AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
> LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
> OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
> SOFTWARE.
 