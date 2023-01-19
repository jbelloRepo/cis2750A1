# Project Title
> C Molecule Manipulation Library

The C library implements a number of functions to represent and manipulate molecules

## Description

Game suite Application Features
* XO Tic Tac Toe can be viewed and played either with a GUI (GameUI) or in the terminal (TextUI)
* The players can choose to quit one game and start another game without exiting the application
* The user may exit the GUI at anytime and quit an unfinished Game
* The user may save in a game  in progress or load an existing game from a csv file
* A saved game is saved with a *".txt"* file extension

##### TicTacToe Versions:
*XO TicTacToe* <br>
The XO Tic Tac Toe is the "base" tic tac toe. You are presented with a 3x3 board and each user have to select
a symbol: "X" or "O". The game in ended when there is a win or tie condition. Each player must connect three of their symbols
to win the game. The game is a tie if the board is full and there a no winner

*Numeric TicTacToe* <br>
Numerical Tic Tac Toe is a game of evens vs odds. player 1 plays with odds and Player 2 plays with even.
odds always go first. On your turn you place one of your numbers on the tic-tac-toe board. Each number can only be used once.
The winner is the first player to complete a line (horizontal, vertical, or diagonal) with a sum of 15.

### Dependencies
To run the program have the latest JDK version installed on your local machine

### Executing program
* How to build and run the program
change directory into the A3 folder in the terminal
1. Run Gradle clean
```
gradle clean
```
2. Run Gradle build
```
gradle build
```
3. Run Gradle Run
```
gradle run
> Task :run
To run the TextUI program:
java -cp build/classes/java/main tictactoe.TextUI
To run the GUI program:
java -jar build/libs/a3.jar
```


## Limitations
##### *Development environment*
The Docker container (scioer) cannot run GUI programs <br>
**Recommended**: Run program locally <br>

##### *Game Design*
* Loading the game assumes player 1 goes first
* By default player 1 is assigned "X" and player 2 is assigned "O"


## Author Information
Author: Jubril Bello <br>
Student ID: 095776 <br>
Email: Jbello@uoguelph.ca <br>
Course: CIS 2430 (Winter 2023) <br>
Professor: Stefan Kremer <br>


## Acknowledgments
* Much of the videos, starter files and examples throughout the course




