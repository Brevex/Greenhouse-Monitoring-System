package com.brevex.GreenhouseSystem.service;

import com.brevex.GreenhouseSystem.model.SensorData;
import com.brevex.GreenhouseSystem.model.SensorDataDTO;
import com.brevex.GreenhouseSystem.repository.SensorDataRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@Service
public class SensorDataService
{
    private final SensorDataRepository sensorDataRepository;

    @Autowired
    public SensorDataService(SensorDataRepository sensorDataRepository)
    {
        this.sensorDataRepository = sensorDataRepository;
    }

    public List<SensorDataDTO> getAllSensorData()
    {
        List<SensorData> sensorDataList = sensorDataRepository.findAll();
        return sensorDataList.stream().map(this::convertToDTO).collect(Collectors.toList());
    }

    private SensorDataDTO convertToDTO(SensorData sensorData)
    {
        if (sensorData == null) { return null; }

        SensorDataDTO dto = new SensorDataDTO();
        dto.setId(sensorData.getId());
        dto.setTopic(sensorData.getTopic());
        dto.setPayload(sensorData.getPayload());
        dto.setMinValue(sensorData.getMinValue());
        dto.setMaxValue(sensorData.getMaxValue());
        dto.setCurrentValue(sensorData.getCurrentValue());
        dto.setAlarmMessage(sensorData.getAlarmMessage());

        return dto;
    }

    private String getSensorName(String topic)
    {
        return switch (topic.toLowerCase())
        {
            case "temperature" -> "DHT22 - Temperature";
            case "humidity" -> "DHT22 - Humidity";
            case "luminosity" -> "Photoresistor (LDR)";
            default -> "Unknown Sensor";
        };
    }

    public void saveSensorData(SensorData sensorData)
    {
        Optional<SensorData> existingDataOptional = sensorDataRepository.findByTopic(sensorData.getTopic());

        if (existingDataOptional.isPresent())
        {
            SensorData existingData = existingDataOptional.get();
            sensorData.setMinValue(Math.min(existingData.getMinValue(), sensorData.getCurrentValue()));
            sensorData.setMaxValue(Math.max(existingData.getMaxValue(), sensorData.getCurrentValue()));
        }
        else
        {
            sensorData.setMinValue(sensorData.getCurrentValue());
            sensorData.setMaxValue(sensorData.getCurrentValue());
        }

        if (sensorData.getTopic().equalsIgnoreCase("temperature"))
        {
            if (sensorData.getCurrentValue() < 10 || sensorData.getCurrentValue() > 20)
            {
                sensorData.setAlarmMessage("Temperature out of range!");
            }
        }
        else if (sensorData.getTopic().equalsIgnoreCase("humidity"))
        {
            if (sensorData.getCurrentValue() > 60)
            {
                sensorData.setAlarmMessage("Humidity too high!");
            }
        }
        else if (sensorData.getTopic().equalsIgnoreCase("luminosity"))
        {
            if (sensorData.getCurrentValue() < 500)
            {
                sensorData.setAlarmMessage("Luminosity too low!");
            }
        }

        sensorDataRepository.save(sensorData);
    }
}