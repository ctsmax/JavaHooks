#include "pch.h"
#include "../vendors/minhook/MinHook.h"

void (*origInterpretedEntry)();
void methodHandler()
{
	auto rbx = (Method*)GetRegister("rbx");
	if (!rbx) return;

	auto cst = rbx->_constMethod;
	if (!cst) return;

	auto constants = cst->_constants;
	if (!constants) return;

	auto callerName = constants->_pool_holder->_name->AsString();
	auto methodName = constants->symbol_at(cst->_name_index)->AsString();
	if (methodName == "func_71165_d") {
		/* args ids start from the last
		* eg: void method(String str, Entity entity);
		* str == 1
		* entity == 0
		*/
		auto GetArgument = [](uintptr_t r13, int idx) { 
			uintptr_t addr = (uintptr_t)r13 + (idx * 8);
			return addr;
		};

		auto r13 = GetRegister("r13");
		if (!r13) return;

		Jstring* arg = *(Jstring**)GetArgument((uintptr_t)r13, 0);
		std::wstring wstr(arg->str, arg->size);
		printf("[!] %s:%s(%s) called, with the following arg: %S!\n", 
			constants->_pool_holder->_name->AsString().data(),
			constants->symbol_at(cst->_name_index)->AsString().data(), 
			constants->symbol_at(cst->_signature_index)->AsString().data(),
			wstr.data()
		);

	}
}

void interpretedEntryHook()
{
	__asm {
		call methodHandler
		jmp origInterpretedEntry
	}
}

void thread(HMODULE hModule)
{
	AllocConsole();
	FILE* fStream;
	freopen_s(&fStream, "conin$", "r", stdin);
	freopen_s(&fStream, "conout$", "w", stdout);

	const auto entityPlayerSPClazz = FindClass("net.minecraft.client.entity.EntityPlayerSP");
	const auto sendChatMsgMethodPtr = entityPlayerSPClazz->GetMethod("func_71165_d", "(Ljava/lang/String;)V");

	MH_Initialize();
	MH_STATUS status = MH_CreateHook(reinterpret_cast<void*>(sendChatMsgMethodPtr->_from_interpreted_entry), interpretedEntryHook, reinterpret_cast<void**>(&origInterpretedEntry));

	if (status == MH_OK) {
		printf("[!] enabling hooks\n");
		status = MH_EnableHook(MH_ALL_HOOKS);
		if (status == MH_OK) {
			printf("[!] successfully enabled hooks\n");
		}
	}

	while (true) {
		if (GetAsyncKeyState(0x72) & 0x8000)
			break;

		Sleep(1);
	}

	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		if (const auto handle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)thread, hModule, 0, nullptr); handle != NULL)
			CloseHandle(handle);
	}
    return TRUE;
}

