# Boids!

![image](https://github.com/user-attachments/assets/66ef5566-07d5-40ed-b016-910c960030c2)
### [Watch the demo on youtube](https://youtu.be/TdexYwXqdPY)

### Main features
- **Multiple families of boids hunting one another**
- **Create and delete obstacles using your mouse**
- **BoundingBox implementation for better performances**
- **Keep track of team scores**

## Boids
Boids follow the standard rules of boids, however they also hunt one another according to a given team.
- When a boid reaches its prey, it grows in size, the prey shrinks and joins the hunter's team
- Size affects a boid's view range, speed, and steering speed

## Obstacles
Obstacles prevent boids from reaching a given area. The user can easily:
1. Add a new obstacle using left click
2. Delete an existing one using right click
   
![image](https://github.com/user-attachments/assets/94c7b50a-ea40-48d7-94ef-e4b997c79fd3)

## Optimisations

![image](https://github.com/user-attachments/assets/551fbbe2-08e7-43b9-a12d-52ac065e89a9)

### Toggle debug mode using *D*
By using a bounding box, boids only need look at their neighbouring boids by fetching the neighbouring boxes and their children.
As they move around, boids regularly ping the neighbouring cells to check if they have switched position.
This sytem means a much better runtime performance at higher boid counts.

Moreover, boids only need 8-9 checks to have a direction approximating the more accurate one. Since we still need to check all boids in case we can eat one, we only look at boids from neighboring cells until we reach 8 succcesful checks.
After which we only look at boids from the current cell.

| Boid count | Framerate |
| ---------- | --------- |
| 1          | 8500      |
| 10         | 8300      |
| 100        | 7200      |
| 1000       | 600       |
| 2000       | 190       |
| 3000       | 94        |
| 4000       | 56        |
| 5000       | 39        |
| 10000      | 11        |

