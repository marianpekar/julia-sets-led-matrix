#include "julia.h"
#include "renderer.h"

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <termios.h>

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}

static char getch() {
  static bool is_terminal = isatty(STDIN_FILENO);

  struct termios old;
  if (is_terminal) {
    if (tcgetattr(0, &old) < 0)
      perror("tcsetattr()");

    // Set to unbuffered mode
    struct termios no_echo = old;
    no_echo.c_lflag &= ~ICANON;
    no_echo.c_lflag &= ~ECHO;
    no_echo.c_cc[VMIN] = 1;
    no_echo.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &no_echo) < 0)
      perror("tcsetattr ICANON");
  }

  char buf = 0;
  if (read(STDIN_FILENO, &buf, 1) < 0)
    perror ("read()");

  if (is_terminal) {
    // Back to original terminal settings.
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
      perror ("tcsetattr ~ICANON");
  }

  return buf;
}

int main(int argc, char *argv[]) {
  RGBMatrix::Options defaults;
  defaults.hardware_mapping = "regular";  // or e.g. "adafruit-hat"
  defaults.rows = 32;
  defaults.chain_length = 1;
  defaults.parallel = 1;
  defaults.disable_hardware_pulsing = true;
  
  Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
  if (canvas == NULL)
    return 1;

  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

  Julia* julia = new Julia(-0.7, 0.27015, defaults.rows, defaults.cols);
  Renderer* renderer = new Renderer(canvas);

  julia->Zoom(2.f);

  const float move_step = 0.0001f;
  const float zoom_step = 0.01f;

  bool running = true;
  while(!interrupt_received && running)
  {
    julia->Calculate();
    julia->Draw(renderer);

    const char c = tolower(getch());
    switch (c) {
      case 'a':
        julia->MoveReal(-move_step);
        break;
      case 'd':
        julia->MoveReal(move_step);
        break;
      case 'w':
        julia->MoveImag(move_step);
        break;
      case 's':
        julia->MoveImag(-move_step);
        break;
      case 'q':
        julia->Zoom(-zoom_step);
        break;
      case 'e':
        julia->Zoom(zoom_step);
        break;
      case 'h':
        julia->AddHueShift(1);
        break;
      case 'g':
        julia->AddHueShift(-1);
        break;
      case 0x1B:           // Escape
      case 0x04:           // End of file
      case 0x00:           // Other issue from getch()
      running = false;
      break;
    }
  }

  canvas->Clear();
  delete renderer;
  delete julia;

  return 0;
}
