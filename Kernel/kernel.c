#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include "time.h"
#include <videoDriver.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;
extern void test(uint64_t rax, ...);

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	ncPrint("[x64BareBones]");
	ncNewline();

	ncPrint("CPU Vendor:");
	ncPrint(cpuVendor(buffer));
	ncNewline();

	ncPrint("[Loading modules]");
	ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
	ncNewline();
	return getStackBase();
}

int main()
{	

	putPixel(0x00FF0000, 100, 3);
	putPixel(0x00FF0000, 101, 3);
	putPixel(0x00FF0000, 102, 3);
	putPixel(0x00FF0000, 103, 3);
	putPixel(0x00FF0000, 104, 3);

	for(int k = 0; k < 7; k++){
		for(int i = 0; i < 100; i++){
			for(int j = 0; j < 100; j++){
				putPixel((j + i) * k, (k*150) + i, j);
			}
		}
	}

	load_idt();

	ncPrint("[Kernel Main]");
	ncNewline();
	ncPrint("  Sample code module at 0x");
	ncPrintHex((uint64_t)sampleCodeModuleAddress);
	ncNewline();
	ncPrint("  Calling the sample code module returned: ");
	ncPrintHex(((EntryPoint)sampleCodeModuleAddress)());
	ncNewline();
	ncNewline();

	ncPrint("  Sample data module at 0x");
	ncPrintHex((uint64_t)sampleDataModuleAddress);
	ncNewline();
	ncPrint("  Sample data module contents: ");
	ncPrint((char*)sampleDataModuleAddress);
	ncNewline();

	ncPrint("[Finished]");
	ncNewline();

	ncUpdateColor(0xF4);
	ncPrint("Arquitectura de computadoras");
	ncUpdateColor(0x0F);
	ncNewline();

	ncPrint("Hora: ");
	ncPrintDec(bcd_to_int(getRTC(4)));
	ncPrint(" Minutos: ");
	ncPrintDec(bcd_to_int(getRTC(2)));
	ncPrint(" Segundos: ");
	ncPrintDec(bcd_to_int(getRTC(0)));
	ncNewline();


	

	ncClear();

	int i = 0;

	while(1){
		i++;
		if(i % 1000000 == 0){
			const char * buf = "Hola";
			test(1, 2, buf, 4);
		}
		
	}

	return 0;
}
