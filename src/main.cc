#include "julia.h"
#include "renderer.h"

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}

int main(int argc, char *argv[]) {
  RGBMatrix::Options defaults;
  defaults.hardware_mapping = "regular";  // or e.g. "adafruit-hat"
  defaults.rows = 32;
  defaults.chain_length = 1;
  defaults.parallel = 1;
  defaults.show_refresh_rate = true;
  defaults.disable_hardware_pulsing = true;
  
  Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
  if (canvas == NULL)
    return 1;

  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

  Julia* julia = new Julia(-0.7, 0.27015, defaults.rows, defaults.cols);
  Renderer* renderer = new Renderer(canvas);

  while(!interrupt_received)
  {
    julia->AddHueShift(-1);
    julia->Zoom(0.0005f);
    julia->Calculate();
    julia->Draw(renderer);
  }

  canvas->Clear();
  delete renderer;
  delete julia;

  return 0;
}
