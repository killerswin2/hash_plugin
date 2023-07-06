#include <intercept.hpp>
#include "hash.hpp"
#include "commands.hpp"
#include <windows.h>

static intercept::types::registered_sqf_function function;

int intercept::api_version() { //This is required for the plugin to work.
    return INTERCEPT_SDK_API_VERSION;
}

void intercept::register_interfaces() {
    
}

extern "C" __declspec(dllexport) void __cdecl _intercept_pre_start()
{
    intercept::pre_start();
}

void intercept::pre_start() {
    //AllocConsole();
    //FILE* fp = new FILE();
    //freopen_s(&fp, "CONOUT$", "w", stdout);

    //TestFunction();

    pre_start_hashing();
}

void intercept::pre_init() {
    
}