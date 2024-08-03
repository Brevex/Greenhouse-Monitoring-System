package com.brevex.GreenhouseSystem.controller;

import com.brevex.GreenhouseSystem.service.SensorDataService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("/sensor-data")
public class SensorDataController
{
    private final SensorDataService sensorDataService;

    @Autowired
    public SensorDataController(SensorDataService sensorDataService)
    {
        this.sensorDataService = sensorDataService;
    }

    @GetMapping
    public String getAllSensorData(Model model)
    {
        model.addAttribute("sensorData", sensorDataService.getAllSensorData());
        return "index";
    }
}