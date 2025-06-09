video demostración carrito: https://youtu.be/hkrh3oQgusk

# Carrito controlado con ROS 2 y ESP8266

Este proyecto permite controlar un carrito de dos ruedas mediante Wi-Fi usando comandos del teclado (`W`, `A`, `S`, `D`) a través de ROS 2. El ESP8266 recibe los comandos y controla los motores mediante un driver L298N. El carrito también cuenta con un sensor ultrasónico que lo detiene automáticamente si detecta un obstáculo a menos de 5 cm.

## Requisitos

### Hardware
- 1 × ESP8266 (Wemos D1 R1)
- 1 × Driver L298N
- 2 × Motores DC
- 1 × Sensor ultrasónico (HC-SR04)
- Fuente de alimentación para motores (ej. baterías)
- Cables y protoboard

## Software
- ROS 2 
- Python
- PlatformIO o Arduino IDE
- Paquete personalizado: `cmd_vel`

## Controles (WASD)

- `W`: Avanzar
- `S`: Retroceder
- `A`: Giro a la izquierda
- `D`: Giro a la derecha
- `E`: Detenerse
- `Q`: Salir del control manual

---

## Cómo correr el sistema

1. **Carga el código del ESP8266** con PlatformIO (`main.cpp`) que:
   - Se conecta al Wi-Fi
   - Escucha comandos por TCP
   - Mide distancia con el sensor
   - Controla los motores

2. **Conecta el ESP8266 a tu hotspot Wi-Fi**

3. Desde ROS 2 (en tu PC):

```bash
source install/setup.bash
ros2 run cmd_vel vel_subscriber
ros2 run cmd_vel wasd_publisher

