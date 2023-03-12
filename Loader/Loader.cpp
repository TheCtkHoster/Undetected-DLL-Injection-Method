#include "includes.h"
#include "functions.h"
#include <cstdlib>

void Cleanup(const std::string message) {
    std::cout << message << std::endl;
    std::terminate();
}

int main()
{
    SetConsoleTitleA("Injector V2");

    DWORD ProcessId = Functions::GetProcessId("RobloxPlayerBeta.exe");

    if (!ProcessId)
        Cleanup("Roblox not Found!");

    HANDLE Game = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);
    uintptr_t ModuleBase = Functions::GetModuleBaseAddress(ProcessId, "why are you deobfuscating/decompiling this? :/");

    if (Functions::DoesFileExist("cheat.dll")) {

        if (!Functions::Internal::ExecuteBypass(Game)) {
            Cleanup("Cannot Bypass...");
        }

        if (Functions::LoadLibraryInject(ProcessId, "cheat.dll")) {

            Functions::Internal::Backup(Game);
            std::cout << "Injecting..." << std::endl;
            Sleep(2000);
            Cleanup("Injected!");
        }
        else
        {
            Functions::Internal::Backup(Game);
            Cleanup("Injection Failed.");
        }

    }



    return 0;
}