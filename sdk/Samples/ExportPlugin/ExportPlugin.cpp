#include "stdafx.h"

#include "ExportPlugin.h"
#include "CLOAPIInterface.h"

#include <string>
#include <vector>

// Qt includes for minimal test
#include <QObject>
#include <QString>
#include <QDebug>
#include <QCoreApplication> // Needed for signal/slot event loop
#include <QMetaObject>      // Needed for QueuedConnection invokeMethod
#include <QThread>          // For QThread::msleep and getting thread ID

// Standard C++ thread
#include <thread>

// --- Minimal Qt Signal/Slot Test --- 

// 1. Receiver Object (lives in main CLO thread)
class ReceiverObject : public QObject {
    Q_OBJECT
public:
    ReceiverObject(QObject* parent = nullptr) : QObject(parent) {}
    ~ReceiverObject() { qDebug() << "ReceiverObject destroyed"; }

public slots:
    void onTestSignalReceived(const QString& message) {
        qDebug() << "ReceiverObject::onTestSignalReceived in thread:" << QThread::currentThreadId();
        std::string msg = "Qt Signal Received in Main Thread: " + message.toStdString();
        // Use CLO API to show message - proves we are in the right context
        if (UTILITY_API) {
            UTILITY_API->DisplayMessageBox(msg);
        }
        // Clean up receiver ONLY after receiving the signal in this test
        // In a real app, lifetime management needs to be more robust
        deleteLater(); 
    }
};

// 2. Emitter Object (intended to live in std::thread)
class EmitterObject : public QObject {
    Q_OBJECT
public:
    EmitterObject(QObject* parent = nullptr) : QObject(parent) {}
    ~EmitterObject() { qDebug() << "EmitterObject destroyed"; }

    // Function to be called from the std::thread
    void run() {
         qDebug() << "EmitterObject::run() starting in thread:" << QThread::currentThreadId();
         // Wait a tiny bit to ensure connection is likely established
         QThread::msleep(100); 
         QString msg = QString("Hello from thread %1").arg((quintptr)QThread::currentThreadId());
         qDebug() << "EmitterObject emitting signal:";
         emit testSignal(msg);
         qDebug() << "EmitterObject signal emitted.";
         // Note: No deleteLater or finished signal for absolute minimum test
    }

signals:
    void testSignal(const QString& message);
};

// Globals for the test (simplistic, manage carefully in real app)
static ReceiverObject* g_receiver = nullptr;
static std::thread*    g_emitterThread = nullptr;
static bool            g_testRunning = false; // Prevent multiple runs without cleanup

void RunMinimalQtSignalSlotTest()
{
    if (g_testRunning) {
        if (UTILITY_API) UTILITY_API->DisplayMessageBox("Minimal Test Already Running or Receiver Pending");
        return;
    }
    
    qDebug() << "RunMinimalQtSignalSlotTest() starting in thread:" << QThread::currentThreadId();

    // --- CRITICAL/RISKY PART --- 
    // Ensure QCoreApplication exists. Static instance is dangerous in a DLL!
    if (!QCoreApplication::instance()) {
        if (UTILITY_API) UTILITY_API->DisplayMessageBox("WARNING: QCoreApplication::instance() is null. Creating static instance (Risky!).");
        int argc = 0; 
        char **argv = nullptr;
        // Use static - app lifetime matches DLL lifetime (problematic unload?)
        static QCoreApplication app(argc, argv); 
        if (UTILITY_API) UTILITY_API->DisplayMessageBox("Static QCoreApplication created.");
    } else {
         if (UTILITY_API) UTILITY_API->DisplayMessageBox("QCoreApplication instance already exists.");
    }
    // --- END CRITICAL/RISKY PART --- 

    // Create receiver in the main thread
    // g_receiver is used to prevent restarting while waiting for signal
    g_receiver = new ReceiverObject(); 
    g_testRunning = true; // Set flag: test is running/receiver active

    // Start the emitter thread
    g_emitterThread = new std::thread([](){
        // This lambda runs in the new std::thread
        qDebug() << "std::thread lambda starting in thread:" << QThread::currentThreadId();
        EmitterObject emitter; // Stack object lives only in this thread

        // Connect emitter signal to receiver slot QUEUED
        QObject::connect(&emitter, &EmitterObject::testSignal,
                         g_receiver, &ReceiverObject::onTestSignalReceived,
                         Qt::QueuedConnection);
        qDebug() << "Signal/Slot connection made.";

        // Run the emitter's logic
        emitter.run();

        qDebug() << "std::thread lambda finishing.";
        // Emitter object is destroyed when lambda scope ends
    });

    // Detach thread - we are not joining/cleaning up in this minimal test
    g_emitterThread->detach(); 
    delete g_emitterThread; // Delete thread handle (doesn't stop detached thread)
    g_emitterThread = nullptr;

    if (UTILITY_API) UTILITY_API->DisplayMessageBox("Minimal test thread launched (detached). Waiting for signal...");

     // Receiver will be deleted via deleteLater() in its slot
     // We set g_testRunning = false there (implicitly via g_receiver deletion check later)
}

// Reset flag/cleanup should happen here ideally, triggered by CLO unload
// void CleanupMinimalTest() { ... }

// --- End Minimal Test --- 


// Original DoFunction is now just a trigger for the minimal test
extern CLO_PLUGIN_SPECIFIER void DoFunction()
{
    // Basic check to prevent overlap if receiver hasn't been deleted yet
    if (g_receiver != nullptr) {
         if (UTILITY_API) UTILITY_API->DisplayMessageBox("Minimal Test Receiver still exists. Waiting for signal or cleanup.");
         return;
    }
    RunMinimalQtSignalSlotTest();
}

// Make sure CLO API is available for the test
using namespace CLOAPI;

// Include the MOC file generated by CMake for signal/slot definitions
// CMakeLists.txt needs: set(CMAKE_AUTOMOC ON)
#include "ExportPlugin.moc"

// --- Keep other functions needed for plugin structure --- 

extern CLO_PLUGIN_SPECIFIER void DoFunctionAfterLoadingCLOFile(const char* fileExtenstion)
{
	// Optional: Implement functionality needed after loading a file
}

extern CLO_PLUGIN_SPECIFIER const char* GetActionName()
{
	const char* actionName = "Minimal Qt Signal/Slot Test";
	return actionName;
}

extern CLO_PLUGIN_SPECIFIER const char* GetObjectNameTreeToAddAction()
{
	const char* objetNameTree = "menuPlugins / menuPlug_In";
	return objetNameTree;
}

extern CLO_PLUGIN_SPECIFIER int GetPositionIndexToAddAction()
{
	return 1; // 0: Above, 1: below (default = 1)
}