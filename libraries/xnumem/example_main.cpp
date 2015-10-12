#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "xnumem.h"

void TestProcessMemory( xnu_proc *process );
void TestProcessModules( xnu_proc *process );

int main (int argc, const char * argv[]) {
    
    // Create new xnu_proc instance
    xnu_proc *Process = new xnu_proc();
    
    // Attach to pid (or process name)
    Process->Attach(getpid());
    
    // Manipulate memory
    TestProcessMemory(Process);
    
    // Test modules
    TestProcessModules(Process);

    // Detach from process
    Process->Detach();
    
    return 0;
}

void TestProcessModules( xnu_proc *process )
{
    // Get module by name
    const ModuleData_t *BaseModule = process->modules().GetModule("xnumem");
    if(BaseModule != nullptr)
    {
        // modules[0] should be the xnumem module
        if( BaseModule->imageLoadAddress == process->modules().modules()[0].imageLoadAddress)
            printf("Success : modules().GetModule\n");
        else
            printf("Error : modules().GetModule\n");
    }else{
        printf("Error : modules().GetModule\n");
    }
    
}

void TestProcessMemory(xnu_proc *process)
{
    int i = 1337;
    int i2 = 0;
    int i3 = 4141;
    const char * TestString = "Hello Xnumem";
    
    // read int
    i2 = process->memory().Read<int>((uintptr_t)&i);
    if(i2 == i)
        printf("Success : memory().Read\n");
    else
        printf("Error : memory().Read\n");
    
    // write int
    process->memory().Write<int>((uintptr_t)&i2, i3);
    if(i2 == i3)
        printf("Success : memory().Write\n");
    else
        printf("Error : memory().Write\n");
    
    // Allocate memory block
    uintptr_t pBlockAddr = process->memory().Allocate(1024);
    
    // Create buffer
    int * buffer = (int *)malloc(sizeof(int));
    *buffer = 1337;
    
    // Write buffer to newly created memory block
    process->memory().Write(pBlockAddr, sizeof(int), buffer);
    
    // Free the buffer
    free(buffer);
    
    // Read from new memory block
    int IntFromBlock = process->memory().Read<int>(pBlockAddr);
    if(IntFromBlock == 1337)
        printf("Success : memory().Allocate\n");
    else
        printf("Error : memory().Allocate\n");
    
    // Free allocated memory
    process->memory().Free(pBlockAddr, 1024);
    
    // Read string
    const char * readstring = process->memory().ReadString((uintptr_t)TestString);
    if(strcmp(readstring, TestString)   == 0)
        printf("Success : memory().ReadString\n");
    else
        printf("Error : memory().ReadString\n");
    
    // print all segments
    process->memory().PrintSegments();
}