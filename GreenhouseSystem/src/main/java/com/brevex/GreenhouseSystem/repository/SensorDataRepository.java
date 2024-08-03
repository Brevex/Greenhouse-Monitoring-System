package com.brevex.GreenhouseSystem.repository;

import com.brevex.GreenhouseSystem.model.SensorData;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;

public interface SensorDataRepository extends JpaRepository<SensorData, Long>
{
    Optional<SensorData> findByTopic(String topic);
}
