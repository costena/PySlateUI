// #pragma optimize("", off)
// #define PYBIND11_DETAILED_ERROR_MESSAGES
// #undef check
#include "Python.h"
#include "StandaloneRenderer.h"
#include "Framework/Application/SlateApplication.h"
#include "Misc/CommandLine.h"
#include "Modules/ModuleManager.h"
#include "Widgets/SWindow.h"
#include "Windows/WindowsHWrapper.h"
#include "LaunchEngineLoop.h"

IMPLEMENT_APPLICATION(PySlate, "PySlate");

#define IDEAL_FRAMERATE 60

#include "Runtime/Launch/Private/LaunchEngineLoop.cpp"

class MyClass {
public:
	void sayHello() {
		printf("Hello from C++!\n");

		const TCHAR* CmdLine = GetCommandLineW();
		CmdLine = FCommandLine::RemoveExeName(CmdLine);

		const TCHAR* CommandLine = CmdLine;

		FQueuedThreadPool::OverrideStackSize = 256 * 1024;
		FCommandLine::Set(CommandLine);
		GEngineLoop.PreInit(CommandLine);

		FCoreStyle::ResetToDefault();
		FSlateApplication::InitializeAsStandaloneApplication(GetStandardStandaloneRenderer());
		FSlateApplication::Get().AddWindow(SNew(SWindow));

		// Enter main loop.
		double DeltaTime = 0.0;
		double LastTime = FPlatformTime::Seconds();
		const float IdealFrameTime = 1.0f / IDEAL_FRAMERATE;

		while (!IsEngineExitRequested())
		{
			FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread);

			FSlateApplication::Get().PumpMessages();
			FSlateApplication::Get().Tick();
			FTicker::GetCoreTicker().Tick(DeltaTime);

			// Throttle frame rate.
			FPlatformProcess::Sleep(FMath::Max<float>(0.0f, IdealFrameTime - (FPlatformTime::Seconds() - LastTime)));

			double CurrentTime = FPlatformTime::Seconds();
			DeltaTime = CurrentTime - LastTime;
			LastTime = CurrentTime;

			FStats::AdvanceFrame(false);

			GLog->FlushThreadedLogs(); //im: ???
		}

		printf("Bye!\n");
	}
};

// 定义 Python 封装类
static PyObject* wrap_sayHello(PyObject* self, PyObject* args) {
	MyClass* myClass = new MyClass();
	myClass->sayHello();
	delete myClass;
	Py_RETURN_NONE;
}

static PyMethodDef PySlateMethods[] = {
	{"sayHello", wrap_sayHello, METH_VARARGS, "Call the sayHello method"},
	{NULL, NULL, 0, NULL} // 结尾标记
};

static struct PyModuleDef PySlate = {
	PyModuleDef_HEAD_INIT,
	"PySlate",
	"PySlate doc",
	-1,
	PySlateMethods,
	nullptr,
	nullptr,
	nullptr,
	nullptr
};

PyMODINIT_FUNC PyInit_PySlate() {
	return PyModule_Create(&PySlate);
}
