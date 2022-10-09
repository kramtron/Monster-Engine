#pragma once


#include <string>
#include <vector>

using namespace std;

enum class ConsoleType
{
	WARNING,
	SYSTEM,
	MSG,
};

struct DebugConsole
{
	DebugConsole(string st, string f, ConsoleType ty) : st(st), repts(1), type(ty), file(f) {};

	string st;
	string file;
	int repts;
	ConsoleType type;
};

class Console
{
public:

	static void PrintDebug();
	static void ConsolDebug(string format, string file, ConsoleType type = ConsoleType::MSG);
	static void CollapseDebug();
	static void UnCollapseDebug();
	static void ButtonsType();

private:

	
	static bool warnignDebug;
	static bool systemDebug;
	static bool msgDebug;


	static float colorEdit[3];

	static int countWarn;
	static int countSyst;
	static int countDebug;

	static bool isCollapsed;
	static bool showPath;

	

	static vector<DebugConsole> logs;
	static vector<DebugConsole> logsCopy;

};
