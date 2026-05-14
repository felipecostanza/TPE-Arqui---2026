#include <time.h>
#include <naiveConsole.h>

static unsigned long ticks = 0;
static unsigned long last = 0;

void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void print_every_five_secs(){
	if(seconds_elapsed() % 5 == 0 && seconds_elapsed() != last){
		ncPrint("Pasaron 5s");
		ncNewline();
		last = seconds_elapsed();
	}
}