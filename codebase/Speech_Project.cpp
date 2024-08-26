// Speech_Project.cpp : main project file.

#include "stdafx.h"
#pragma comment(lib, "winmm.lib")

#include "Form1.h"

using namespace Speech_Project;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Form1());
	return 0;
}
