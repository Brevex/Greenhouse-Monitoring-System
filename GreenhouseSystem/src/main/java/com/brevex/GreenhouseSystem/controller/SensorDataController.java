package com.brevex.GreenhouseSystem.controller;

import com.brevex.GreenhouseSystem.model.SensorDataDTO;
import com.brevex.GreenhouseSystem.service.SensorDataService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
@RequestMapping("/api/sensor-data")
public class SensorDataController
{
    private final SensorDataService sensorDataService;

    @Autowired
    public SensorDataController(SensorDataService sensorDataService)
    {
        this.sensorDataService = sensorDataService;
    }

    @GetMapping
    public List<SensorDataDTO> getAllSensorData()
    {
        return sensorDataService.getAllSensorData();
    }

    @GetMapping("/{id}")
    public ResponseEntity<SensorDataDTO> getSensorDataById(@PathVariable Long id)
    {
        SensorDataDTO sensorData = sensorDataService.getSensorDataById(id);
        return ResponseEntity.ok(sensorData);
    }
}
