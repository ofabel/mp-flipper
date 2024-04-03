import time
import flipperzero

color = False

for x in range(0, 128):
  color = not color

  for y in range(0, 64):
    flipperzero.canvas_draw_dot(x, y, color)

    color = not color

flipperzero.canvas_update()

time.sleep(2)
