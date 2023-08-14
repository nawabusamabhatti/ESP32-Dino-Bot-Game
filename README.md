# ESP32-Dino-Bot-Game
This Arduino LCD game lets players control a jumping character to avoid obstacles. A keypad is used for actions, and LEDs add flair. It features a splash screen, access code, "Best Score" storage, combining electronics, programming, and gaming in an engaging project.

![Board Image](https://github.com/nawabusamabhatti/ESP32-Dino-Bot-Game/assets/69959257/38cddc1d-0ff6-45bb-b917-e54f6559c6e2)




This project is a simple game implemented on an Arduino using a character-based LCD display and keypad. The game is reminiscent of the popular "Chrome Dino" game you might find in the Chrome browser when there's no internet connection. The player controls a character that can jump to avoid obstacles. The LCD display simulates the game's environment, while the keypad allows the player to control the character.

Here's a breakdown of the project:

Components Used:

Arduino board (specifically, ESP32)
Character LCD display
Keypad
Various resistors and wires
Gameplay:

The LCD screen shows the game environment, which scrolls from right to left.
The player controls a character that starts at the left edge of the screen.
The character automatically moves forward, and the player's goal is to avoid obstacles.
The player can make the character jump by pressing the "Up" button on the keypad.
Obstacles include cacti and birds. The player must time their jumps to avoid collision.
The game keeps track of the player's score, which increases as the character moves forward.
Additional Features:

There's a splash screen displayed at startup with the developer's name and a brief introduction.
An access code is required to configure the game. The user needs to enter the correct code using the keypad to gain access.
The game maintains a "Best Score" in EEPROM memory.
LEDs on the Arduino board blink to add visual appeal.
How It Works:

The Arduino reads keypad input to control the character's actions (jumping).
The LCD screen is used to display the scrolling game environment and the character.
Obstacles are randomly generated, and the game checks for collisions to determine if the player hit an obstacle or successfully jumped over it.
The game keeps track of the player's score and updates it on the LCD.
Access control is implemented using an access code that the user needs to input using the keypad.
Purpose:
This project is a creative implementation that combines electronics, programming, and gaming. It provides a basic and fun gaming experience while showcasing various Arduino functionalities, such as interacting with peripherals like the LCD and keypad, generating random events, and storing data in EEPROM memory. It's a great way to learn about input handling, graphical simulation, and basic game mechanics on a microcontroller platform.
