# Boids!

![image](https://github.com/user-attachments/assets/5118439e-85c4-49b9-b842-fd1a856c46c1)

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
   
![image](https://github.com/user-attachments/assets/b20bc9e4-4ad4-4c0d-8e7d-5c180b8b27a1)

## Optimisations

![image](https://github.com/user-attachments/assets/c10b9958-cb22-491c-a109-230a013ff679)

### Toggle debug mode using *D*
By using a bounding box, boids only need look at their neighbouring boids by fetching the neighbouring boxes and their children.
As they move around, boids regularly ping the neighbouring cells to check if they have switched position.
This sytem means a much better runtime performance at higher boid counts.

Moreover, boids only need 8-9 checks to have a direction approximating the more accurate one. Since we still need to check all boids in case we can eat one, we only look at boids from neighboring cells until we reach 8 succcesful checks.
After which we only look at boids from the current cell.

| Boid count | Framerate |
| ---------- | --------- |
| 1          | 8500      |
| 10         | 9000      |
| 100        | 4700      |
| 500        | 550       |
| 1000       | 200       |
| 2000       | 60        |
| 3000       | 30        |
| 4000       | 18        |
| 5000       | 11        |

