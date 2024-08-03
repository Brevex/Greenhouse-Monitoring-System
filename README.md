<h1 align = "center"> Greenhouse Monitoring System</h1><br>

<h2> &#128269; About the project </h2><br>

<p>A simple greenhouse monitoring system made with ESP32. The system detects possible risks for plants, such as: temperature, humidity and light. The 
user will be warned whenever one of the conditions is inappropriate. The system also sends the data to a full stack application via an MQTT connection.</p><br>

<h2> &#128302; Technologies Used </h2><br>

<p align="center">
  <a href="https://skillicons.dev">
    <img src="https://skillicons.dev/icons?i=java,spring,postgres,arduino" />
  </a>
</p>

<br><h2> &#128161; How it Works? </h2>

<br><p align="center">
  <img src="https://github.com/Brevex/Greenhouse-Monitoring-System/blob/521fa1abdf33985420350e1e8c14eb7994b2fd9c/Readme%20Images/circuit.png" alt="circuit">
</p><br>

<ul>
  <li>The system has 2 sensors: DHT22 for monitoring temperature and humidity and the Photoresistor (LDR) sensor for measuring luminosity;</li>
   <li>The buzzer will sound whenever the system enters an alarm situation;</li>
  <li>Alarm situations:</li><br>
  
  <ol>
    <li>Temperature < 10º or Temperature > 20º</li>
    <li>Humidity > 60%</li>
    <li>Luminosity < 500</li>
  </ol><br>
  
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
