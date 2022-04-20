
void printf(const char* string)
{

    unsigned short* videoMemory = 
        (unsigned short*)0xb8000;

    for(int index = 0; string[index] != '\0'; ++index)
        videoMemory[index] = 
            (videoMemory[index] & 0xFF00) | 
            string[index];

}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" void callConstructors()
{

    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();

}

extern "C" void kernelMain(void* multibootStructure, unsigned int magicNumber)
{

    printf("Welcome to Rhana OS");

    while(1);

}
