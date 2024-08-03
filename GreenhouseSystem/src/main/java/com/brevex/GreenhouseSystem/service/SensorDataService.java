package com.brevex.GreenhouseSystem.service;

import com.brevex.GreenhouseSystem.model.SensorData;
import com.brevex.GreenhouseSystem.model.SensorDataDTO;
import com.brevex.GreenhouseSystem.repository.SensorDataRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
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

        return sensorDataList
                .stream()
                .map(this::convertToDTO)
                .collect(Collectors.toList());
    }

    public SensorDataDTO getSensorDataById(Long id)
    {
        SensorData sensorData = sensorDataRepository
                .findById(id)
                .orElse(null);

        return convertToDTO(sensorData);
    }

    private SensorDataDTO convertToDTO(SensorData sensorData)
    {
        if (sensorData == null) { return null; }

        SensorDataDTO dto = new SensorDataDTO();
        dto.setId(sensorData.getId());
        dto.setTopic(sensorData.getTopic());
        dto.setPayload(sensorData.getPayload());

        return dto;
    }

    public void saveSensorData(SensorData sensorData)
    {
        sensorDataRepository.save(sensorData);
    }
}
