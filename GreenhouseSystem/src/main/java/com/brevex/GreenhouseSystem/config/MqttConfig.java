package com.brevex.GreenhouseSystem.config;

import com.brevex.GreenhouseSystem.model.SensorData;
import com.brevex.GreenhouseSystem.service.SensorDataService;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.integration.annotation.ServiceActivator;
import org.springframework.integration.channel.DirectChannel;
import org.springframework.integration.core.MessageProducer;
import org.springframework.integration.mqtt.core.DefaultMqttPahoClientFactory;
import org.springframework.integration.mqtt.core.MqttPahoClientFactory;
import org.springframework.integration.mqtt.inbound.MqttPahoMessageDrivenChannelAdapter;
import org.springframework.integration.mqtt.support.DefaultPahoMessageConverter;
import org.springframework.messaging.MessageChannel;
import org.springframework.messaging.MessageHandler;

import java.util.Objects;

@Configuration
public class MqttConfig
{
    private final SensorDataService sensorDataService;

    public MqttConfig(SensorDataService sensorDataService)
    {
        this.sensorDataService = sensorDataService;
    }

    @Bean
    public MqttPahoClientFactory mqttClientFactory()
    {
        DefaultMqttPahoClientFactory factory = new DefaultMqttPahoClientFactory();
        MqttConnectOptions options = new MqttConnectOptions();

        options.setServerURIs(new String[]{"tcp://192.168.0.100:1883"});
        options.setUserName("seu-usuario");
        options.setPassword("sua-senha".toCharArray());
        factory.setConnectionOptions(options);

        return factory;
    }

    @Bean
    public MessageChannel mqttInputChannel()
    {
        return new DirectChannel();
    }

    @Bean
    public MessageProducer inbound()
    {
        MqttPahoMessageDrivenChannelAdapter adapter =
                new MqttPahoMessageDrivenChannelAdapter(
                        "clientId", mqttClientFactory(),
                        "topico-dos-sensores/temperature",
                        "topico-dos-sensores/humidity",
                        "topico-dos-sensores/luminosity"
                );

        adapter.setCompletionTimeout(5000);
        adapter.setConverter(new DefaultPahoMessageConverter());
        adapter.setQos(1);
        adapter.setOutputChannel(mqttInputChannel());

        return adapter;
    }

    @Bean
    @ServiceActivator(inputChannel = "mqttInputChannel")
    public MessageHandler handler()
    {
        return message -> {
            String topic = Objects.requireNonNull(message.getHeaders().get("mqtt_receivedTopic")).toString();
            String payload = message.getPayload().toString();

            System.out.println("Mensagem recebida [" + topic + "]: " + payload);

            SensorData sensorData = new SensorData();
            sensorData.setTopic(topic);
            sensorData.setPayload(payload);
            sensorDataService.saveSensorData(sensorData);
        };
    }
}
