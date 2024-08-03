package com.brevex.GreenhouseSystem.model;

import lombok.Data;

@Data
public class SensorDataDTO
{
    private Long id;
    private String topic;
    private String payload;
}
