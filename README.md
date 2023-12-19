<h1 align = "center"> Greenhouse Monitoring System ESP32 </h1><br>

<h2> &#128269; About the project </h2><br>

<p>A simple greenhouse monitoring system made in ESP32. The system detects possible risks for plants, such as: temperature, humidity and light. The 
user will be warned whenever one of the conditions is inappropriate.</p><br>

<p align = "center"><b>| TEST BY <a href="https://wokwi.com/projects/383967622942753793" target="_blank">CLICKING HERE</a> |</b></p><br>

<h2> &#128302; Technologies Used </h2><br>

<p align="center">
  <a href="https://skillicons.dev">
    <img src="https://skillicons.dev/icons?i=arduino,c" />
  </a>
</p>

<br><h2> &#128161; How it Works? </h2>

<br><p align="center">
  <img src="https://github.com/Brevex/Greenhouse-Monitoring-System-ESP32/blob/24614c531177b1da7a8cbb55fd4107524cb6a33b/readme%20images/circuit.png" alt="circuit">
</p><br>

<ul>
  <li>The system has 2 sensors: DHT22 for monitoring temperature and humidity and the Photoresistor (LDR) sensor for measuring luminosity;</li>
  <li>Alarm conditions:</li><br>
  
  <ol>
    <li>Temperature < 10º or Temperature > 20º</li>
    <li>Humidity > 60%</li>
    <li>Luminosity < 500</li>
  </ol><br>
  
  <li>The buzzer will sound whenever the system enters an alarm situation;</li>
  <li>If the system enters any alarm situation, the blue button next to the buzzer can be activated so the buzzer stops sounding;</li>
  <li>The button can also be pressed at any time to disable the alarm system if the user does not wish to be notified.</li>
</ul>

<br><h2> &#128295; Circuit Assembly </h2>

<br><div align="center">

  <h3>Using ESP32 devkit-c-v4 </h3>   
  
  | Compenent           | Component Pin | ESP32 Pin |
  |:-------------------:|:-------------:|:---------:|
  | Photoresistor (LDR) | ldr1:AO       | esp:34    |
  | Photoresistor (LDR) | ldr1:GND      | esp:GND.2 |
  | Photoresistor (LDR) | ldr1:VCC      | esp:VN    |
  | DHT22               | dht1:VCC      | esp:3V3   |
  | DHT22               | dht1:SDA      | esp:23    |
  | DHT22               | dht1:GND      | esp:GND.2 |
  | LCD 20x4 (I2C)      | lcd1:GND      | esp:GND.3 |
  | LCD 20x4 (I2C)      | lcd1:VCC      | esp:5V    |
  | LCD 20x4 (I2C)      | lcd1:SDA      | esp:21    |
  | LCD 20x4 (I2C)      | lcd1:SCL      | esp:22    |
  | Buzzer              | bz1:1         | esp:GND.1 |
  | Buzzer              | bz1:2         | esp:12    |
  | Pushbutton          | btn1:2.r      | esp:GND.1 |
  | Pushbutton          | btn1:1.r      | esp:14    |
  
</div>

<br><h3 align = "center"> - By <a href = "https://www.linkedin.com/in/breno-barbosa-de-oliveira-810866275/" target = "_blank">Breno</a> - </h3>
