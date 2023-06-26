from machine import Pin
import utime as time

# Definir los pines del teclado
row_pins = [Pin(5, Pin.IN, Pin.PULL_UP), Pin(4, Pin.IN, Pin.PULL_UP), Pin(21, Pin.IN, Pin.PULL_UP)]
col_pins = [Pin(16, Pin.OUT), Pin(17, Pin.OUT), Pin(18, Pin.OUT), Pin(19, Pin.OUT)]

# Definir los caracteres del teclado
keypad = [
    ['1', '2', '3'],
    ['4', '5', '6'],
    ['7', '8', '9'],
    ['*', '0', '#']
]

# Definir los pines de salida
correct_pin = Pin(12, Pin.OUT)
incorrect_pin = Pin(14, Pin.OUT)
reset_pin = Pin(27, Pin.OUT)

# Definir la clave
clave = ['1', '2', '3', '4']
clave_ingresada = []

# Variables de estado
esperando_clave = False
esperando_reset = False
clave_correcta = False

# Función para leer el teclado
def read_key():
    # Escaneo de las columnas
    for col_pin in col_pins:
        col_pin.value(0)
        for row_pin in row_pins:
            if row_pin.value() == 0:
                # Buscar la posición del botón presionado en el keypad
                col_pin.value(1)
                return keypad[col_pins.index(col_pin)][row_pins.index(row_pin)]
        col_pin.value(1)
    return None

# Función para el mecanismo de debounce
def debounce():
    for _ in range(10):
        time.sleep(0.001)  # Retardo de 1 ms

# Loop principal
while True:
    key = read_key()
    if key is not None:
        if key == '#':
            if not esperando_clave and not esperando_reset and not clave_correcta:
                clave_ingresada = []
                esperando_clave = True
                print("Ingrese la clave:")
                inicio_tiempo = time.ticks_ms()  # Obtener el tiempo de inicio
        elif key == '*':
            if esperando_reset:
                esperando_reset = False
                reset_pin.off()
                clave_ingresada = []  # Restablecer la clave ingresada
            else:
                esperando_reset = True
                reset_pin.on()
                print("Sistema reiniciado")
                esperando_clave = False  # Restablecer el estado de esperando_clave
                clave_correcta = False  # Restablecer el estado de clave_correcta
                correct_pin.off()  # Apagar la salida permanente en el pin 12
                incorrect_pin.off()  # Apagar la señal de clave incorrecta
                debounce()  # Aplicar mecanismo de debounce
                continue  # Volver al inicio del bucle sin procesar más teclas

        elif esperando_clave:
            clave_ingresada.append(key)
            print("Clave ingresada:", "".join(clave_ingresada))
            if len(clave_ingresada) == 4:
                esperando_clave = False
                if clave_ingresada == clave:
                    clave_correcta = True
                    correct_pin.on()
                    print("Clave correcta")
                else:
                    incorrect_pin.on()
                    print("Clave incorrecta")
                    time.sleep(2)  # Mantener la salida en el pin 14 encendida por 2 segundos
                    incorrect_pin.off()  # Apagar la señal de clave incorrecta

                debounce()  # Aplicar mecanismo de debounce

    if clave_correcta:
        continue  # No procesar más teclas si la clave es correcta y la salida en el pin 12 está encendida
    
    time.sleep(0.1)  # Ajustar el tiempo de espera para una mejor lectura del teclado
