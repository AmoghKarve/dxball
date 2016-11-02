Amogh Karve
111508008
SY IT

# DxBall

This is a classic brick breaker game implemented in C using ncurses library.
The game involves the user to control a paddle present to prevent a ball from falling down.
The screen has a set of bricks present.
Objective of the game is to hit as many bricks as possible.
A ball moves around the screen.
Players score increases when the ball hits a brick.
The bricks are of different types:
Green Brick:
  Does not add to score.
  Does not disappear when hit.
Blue Brick:
  Adds to score.
  Becomes a yellow brick when hit.
Yellow Brick:
  Adds to score.
  Disappears when hit.
The game end when either all the bricks disappear or you are unable to stop the ball from falling.

A power-up also timely fall down.
Catching a power-up with the paddle enables you to shoot bullets from the paddle.
Bullet work similar to balls.
Once you catch a power-up, more power-ups will stop falling down.


Instructions for use:
run ./program to start the game.
A menu appears in which you can navigate around the game.
Controls:
  LEFT_ARROW:  Move Paddle to Left.
  RIGHT_ARROW:  Move Paddle to Right.
  UP_ARROW: Fire Bullet if Power-Up Enabled.
  SPACE: Start Game.
  
