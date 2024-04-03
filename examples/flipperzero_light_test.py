import time
import flipperzero

is_red = True

for i in range(0, 20, 1):
  brightness = i * 10
  is_red = not is_red

  flipperzero.light_set(flipperzero.LIGHT_RED, brightness if is_red else 0)
  flipperzero.light_set(flipperzero.LIGHT_GREEN, brightness if not is_red else 0)
  flipperzero.light_set(flipperzero.LIGHT_BLUE, 0)
  flipperzero.light_set(flipperzero.LIGHT_BACKLIGHT, brightness)

  time.sleep_ms(200)
