# Arduino-Maze-Solving-Robot

An Arduino micro controller based robot which first analyzes the maze in the dry run by following lines through IR sensors and then calculates the shortest path from the source to the destination.

![Maze](https://user-images.githubusercontent.com/73630123/115738487-b9171e80-a3aa-11eb-8f36-94386b456330.jpg)

The new array of now 6 sensors is mounted out of which only 5 sensors are used for better precision. If one sensor is centered with relation to the black line, only that specific sensor will produce a HIGH. The possible 5 original sensor array output when following a line are:
[1 1 1 1 1, 0 0 0 0 0, 0 0 0 0 1, 0 0 0 1 1, 0 0 0 1 0, 0 0 1 1 0, 0 0 1 0 0 , 0 1 1 0 0 , 0 1 0 0 0, 1 1 0 0 0, 1 0 0 0 0]

![Screenshot_20210422-183759](https://user-images.githubusercontent.com/73630123/115738403-a6044e80-a3aa-11eb-8a28-ddb5c98389ec.jpg)

The maze solver bot code is split in two parts:

1. (First Part): The robot finds its way out from a "non-known perfect maze". Does not matter where you put it inside the maze, it will find a "solution".
2. (Second Part): Once the robot found a possible maze solution, it should optimize its solution finding the "shortest path from start to finish".

To find the solution of the maze, the bot uses "Right Hand Rule". If in the maze all its walls are connected together maze's outer boundary, then by keeping one hand in contact with one wall of the maze, the solver will not to get lost and will reach the exit. Steps in Left Hand Rule are:

1. At "Cross": Go to Right
2. At "T": Go to Right
3. At "Right Only": Go to Right
4. At "Left Only": Go to Left
5. At "Straight or Left": Go Straight
6. At "Straight or Right": Go Right
7. At "Dead End": Go back ("U turn")
8. At the "End of Maze": Stop
