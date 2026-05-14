#include <naiveConsole.h>
#include <keyboard.h>

static int shift = 0;
static int capsLock = 0;

static char conversion[] = {0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
                                '-', '=', 0, '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 
                                'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's', 'd', 'f', 'g', 
                                'h', 'j', 'k', 'l', ';', '\'', '\`', 0, '\\', 'z', 'x', 'c', 'v',
                                'b', 'n', 'm', ',', '.', '/', 0, 0, 0, ' '};

static char shiftConversion[] = {0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
                                '_', '+', 0, 0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 
                                'I', 'O', 'P', '{', '}', '|', 0, 'A', 'S', 'D', 'F', 'G', 
                                'H', 'J', 'K', 'L', ':', '\"', '~', 0, '\\', 'Z', 'X', 'C', 'V',
                                'B', 'N', 'M', '<', '>', '?', 0, 0, 0, ' '};                                

void printPressedKey(){
    unsigned int pressed = readFromKeyboard();

    switch (pressed)
    {
    case 0x2A:
    case 0x36:
        shift = 1;
        return;
        break;
    case 0xAA:
    case 0xB6:
        shift = 0;
        return;
        break;
    case 0x3A:
        capsLock = !capsLock;
        return;
    default:
        break;
    }

    if (pressed & 0x80){
        return;
    }

    char c = conversion[pressed];

    int uppercase = shift ^ capsLock;

    if(uppercase && c >= 'a' && c <= 'z'){
        ncPrintChar(shiftConversion[pressed]);
        return;
    }

    else if(shift && c != 0){
        ncPrintChar(shiftConversion[pressed]);
        return;
    }

    if(c != 0){
        ncPrintChar(c);
    }
    
}
