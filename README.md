<h1 align = "center"> Greenhouse Monitoring System ESP32 </h1><br>

<h2> &#128269; About the project </h2><br>

<p>A Simon Game made using the ESP32-Arduino platform in the Wokwi IoT project simulation environment. The game 
consists of memorizing a sequence of colors that is increased by +1 each round.</p><br>

<h2> &#127918; How to Play </h2><br>

<p align = "center"><b>| PLAY BY <a href="https://wokwi.com/projects/379952160077169665" target="_blank">CLICKING HERE</a> |</b></p><br>

<p>Conventionally, the Simon Game repeats the sequence from the previous round and increases it, but to increase the challenge, this version uses a completely new sequence each round.</p><br>

<ul>
    <li>The game has 10 rounds of random colors;</li>
    <li>To win, get each round correct by entering the correct sequence;</li>
    <li>If you get the sequence wrong, the game will end and display your score.</li>
</ul><br>

<h2> &#128302; Technologies Used </h2><br>

<p align="center">
  <a href="https://skillicons.dev">
    <img src="https://skillicons.dev/icons?i=arduino" />
  </a>
</p>

<br><h2> &#128161; Program Functions </h2>

<br>
<details>
	<summary>circuit</summary><br>
  	<img align = "center" src="https://github.com/Brevex/Simon-Game-ESP32/blob/10970f59c60db01da064faede70820c7adb676b0/readme%20images/circuit.png" alt="circuit"><br><br>
	<p>Project circuit. Build on Wokwi.</p>
</details>

<details>
	<summary>variables</summary><br>
  	<img align = "center" src="https://github.com/Brevex/Simon-Game-ESP32/blob/7e130177e10c060f21411417d523ab1dce414511/readme%20images/variables.png" alt="variables"><br><br>
	<ul>
	    <li><code>leds [ ]</code>: It's an array that stores the pins of the LEDs used in the game</li>
	    <li><code>bts [ ]</code>: It's an array that stores the button pins corresponding to the LEDs</li>
	    <li><code>labels [ ]</code>: It's an array of strings that contains the labels (colors) associated with the LEDs</li>
	    <li><code>sequenceQueue</code>: It's a queue used to send and receive information about the sequence of buttons pressed</li>
	    <li><code>mutex</code>: It's a mutex (binary semaphore) used to guarantee exclusive access to resources shared between tasks</li>
   	</ul>
</details>

<details>
	<summary>leds</summary><br>
	<img align = "center" src="https://github.com/Brevex/Simon-Game-ESP32/blob/main/readme%20images/led.png" alt="leds"><br><br>
	<p>This task is responsible for controlling the LEDs and detecting button presses. A for loop is used to turn off all LEDs. 
  	Another for loop checks whether a button corresponding to an LED has been pressed. If yes, the LED is lit, a message is 
  	printed on the console (Serial), and the index of the pressed button is sent to the sequenceQueue queue.</p>
</details>

<details>
	<summary>simonGame</summary><br>
	<img align = "center" src="https://github.com/Brevex/Simon-Game-ESP32/blob/main/readme%20images/game.png" alt="game"><br><br>
  	<p>The simonGame task controls the Simon game. Generates a random sequence of buttons for each round and displays this sequence by flashing the corresponding LEDs. 
  	Uses the sequenceQueue queue to receive the buttons pressed by the user and checks if the sequence is correct. Prints the score and ends the game if the sequence is incorrect. 
  	Increments the score, waits 2 seconds before the next round and increments the round number.</p>
</details>

<details>
	<summary>setup</summary><br>
	<img align = "center" src="https://github.com/Brevex/Simon-Game-ESP32/blob/main/readme%20images/setup.png" alt="setup"><br><br>
  	<p>Configures serial communication and initializes the queue and mutex. Configures the LED pins as outputs and the button pins as pull-up inputs. 
  	Creates and starts the led and simonGame tasks.</p>
</details>

<details>
	<summary>loop</summary><br>
	<img align = "center" src="https://github.com/Brevex/Simon-Game-ESP32/blob/main/readme%20images/loop.png" alt="loop"><br><br>
  	<p>The loop function is empty because the main logic of the program is in the tasks created in setup.</p>
</details>

<br><h3 align = "center"> - By <a href = "https://www.linkedin.com/in/breno-barbosa-de-oliveira-810866275/" target = "_blank">Breno</a> - </h3>
