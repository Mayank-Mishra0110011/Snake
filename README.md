Snake Game in C++

Working:

Snake structure is defined which stores 2 pointers, a left pointer to self and a right pointer to self, x value of the node, y value of the node and the direction of the node.

Snake moves by default in 'd' or right direction and changes it's direction according to the user input. After an input direction is provided a new direction can only be entered when all the nodes of snake achieve a common direction.

Food is generated at random locations after every 50 iterations in while(1), making sure that the location of food does not collide with walls or the snake itself. Collision detection for both walls and food is possible. After a collision with food is encountered score increases by 100 and size of snake increases by 1. Collision detection with self is not implemented.

limitations:

  ==> Self collision of snake cannot be detected.
  
  ==> Snake cannot move from one wall to the other opposite wall.
  
  ==> Once a change in direction of snake is executed next change can only be exuted on the entire body of snake has achieved a uniform         direction.
  
