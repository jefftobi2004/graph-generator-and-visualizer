#include "Grafuri.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThread] // Add this attribute to mark the main thread as STA
void main(cli::array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    GRAPHS::Grafuri form;
    Application::Run(% form);
}

