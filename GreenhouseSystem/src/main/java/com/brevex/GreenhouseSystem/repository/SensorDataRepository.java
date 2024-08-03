package com.brevex.GreenhouseSystem.repository;

import com.brevex.GreenhouseSystem.model.SensorData;
import org.springframework.data.jpa.repository.JpaRepository;

public interface SensorDataRepository extends JpaRepository<SensorData, Long> {}
