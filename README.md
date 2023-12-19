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
  <li>If the temperature drops below 10º or above 20º, the system will will be in temperature alarm condition;</li>
  <li>If the humidity is greater than 60%, the system will be in humidity alarm condition;</li>
  <li>If the brightness drops below 500, the system will be in brightness alarm condition;</li>
  <li>The buzzer will sound whenever the system enters an alarm situation;</li>
  <li>If the system enters any alarm situation, the blue button next to the buzzer can be activated so the buzzer stops sounding;</li>
  <li>The button can also be pressed at any time to disable the alarm system if the user does not wish to be notified.</li>
</ul>

<br><h3 align = "center"> - By <a href = "https://www.linkedin.com/in/breno-barbosa-de-oliveira-810866275/" target = "_blank">Breno</a> - </h3>
