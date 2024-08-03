package com.brevex.GreenhouseSystem.model;

import lombok.Data;

@Data
public class SensorDataDTO
{
    private Long id;
    private String name;
    private String topic;
    private String payload;
    private Double minValue;
    private Double maxValue;
    private Double currentValue;
    private String alarmMessage;
}
