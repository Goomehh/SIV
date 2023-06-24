import time
import machine
import adafruit_fingerprint

# Configuración del puerto UART
uart = machine.UART(1, baudrate=57600, tx=17, rx=16)

# Crear objeto de sensor de huellas dactilares
finger = adafruit_fingerprint.Adafruit_Fingerprint(uart)

# Enrollar nueva huella
print("Coloque el dedo en el sensor para registrar una nueva huella")
while not finger.enroll():
    pass
print("Huella registrada correctamente")

# Verificar huella
print("Coloque el dedo en el sensor para verificar su huella")
while True:
    if finger.read_templates() and finger.verify():
        print("Huella verificada correctamente")
    else:
        print("La huella no coincide")
    time.sleep(1)