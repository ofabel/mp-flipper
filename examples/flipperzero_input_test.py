import time
import flipperzero

@flipperzero.on_input_back
def on_back(_):
  print('on back')

@flipperzero.on_input_ok
def on_ok(_):
  print('on ok')

for _ in range(1,1000):
  time.sleep_ms(10)
