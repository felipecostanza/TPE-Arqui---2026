#include <time.h>
#include <stdint.h>
#include <keyboard.h>

static void int_20();
static void int_21();
static void (*interrupt_arr[])(void) = {int_20, int_21};

void irqDispatcher(uint64_t irq) {
	interrupt_arr[irq]();
	/*
	switch (irq) {
		case 0:
			int_20();
			break;
		case 1:
			int_21();
			break;
			
	}*/
	return;
}

void int_20() {
	timer_handler();
	print_every_five_secs();
}

void int_21(){
	printPressedKey();
}
