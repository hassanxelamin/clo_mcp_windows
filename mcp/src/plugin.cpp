#include "stdafx.h"

#include "plugin.h"
#include "CLOAPIInterface.h"

#include <string>
#include <vector>

// Qt includes needed for signal/slot mechanism and debugging
#include <QObject>
#include <QString>
#include <QDebug>
#include <QCoreApplication> // Required for Qt event loop handling
#include <QMetaObject>      // For queued signal/slot connections
#include <QThread>          // For thread management and sleep

// For native threading
#include <thread>

// --- Qt Signal/Slot Test Implementation ---

/*
This code demonstrates cross-thread communication using Qt's signal/slot mechanism.
The pattern involves:
1. A receiver object in the main CLO thread that handles messages
2. An emitter object in a separate thread that sends signals
3. Thread-safe communication between them using Qt's event system
*/

// Receiver lives in main CLO thread and handles incoming signals
class ReceiverObject : public QObject {
    Q_OBJECT
public:
    ReceiverObject(QObject* parent = nullptr) : QObject(parent) {}
    ~ReceiverObject() { qDebug() << "ReceiverObject destroyed"; }

public slots:
    // Slot that receives and processes signals from the emitter
    void onTestSignalReceived(const QString& message) {
        qDebug() << "ReceiverObject::onTestSignalReceived in thread:" << QThread::currentThreadId();
        std::string msg = "Qt Signal Received in Main Thread: " + message.toStdString();
        // Display message using CLO API to verify we're in main thread context
        if (UTILITY_API) {
            UTILITY_API->DisplayMessageBox(msg);
        }
        // Self-cleanup after handling signal
        deleteLater(); 
    }
};

// Emitter runs in separate thread and generates signals
class EmitterObject : public QObject {
    Q_OBJECT
public:
    EmitterObject(QObject* parent = nullptr) : QObject(parent) {}
    ~EmitterObject() { qDebug() << "EmitterObject destroyed"; }

    // Main logic executed in separate thread
    void run() {
         qDebug() << "EmitterObject::run() starting in thread:" << QThread::currentThreadId();
         // Small delay to ensure connection setup
         QThread::msleep(100); 
         QString msg = QString("Hello from thread %1").arg((quintptr)QThread::currentThreadId());
         qDebug() << "EmitterObject emitting signal:";
         emit testSignal(msg);
         qDebug() << "EmitterObject signal emitted.";
    }

signals:
    // Signal that will be emitted to communicate with receiver
    void testSignal(const QString& message);
};

// Global state management (simplified for demo)
static ReceiverObject* g_receiver = nullptr;
static std::thread*    g_emitterThread = nullptr;
static bool            g_testRunning = false;

// Main test function that sets up the signal/slot communication
void RunMinimalQtSignalSlotTest()
{
    // Prevent multiple concurrent test runs
    if (g_testRunning) {
        if (UTILITY_API) UTILITY_API->DisplayMessageBox("Minimal Test Already Running or Receiver Pending");
        return;
    }
    
    qDebug() << "RunMinimalQtSignalSlotTest() starting in thread:" << QThread::currentThreadId();

    // Ensure Qt application context exists
    // WARNING: Static QCoreApplication in DLL is risky but used here for demo
    if (!QCoreApplication::instance()) {
        if (UTILITY_API) UTILITY_API->DisplayMessageBox("WARNING: QCoreApplication::instance() is null. Creating static instance (Risky!).");
        int argc = 0; 
        char **argv = nullptr;
        static QCoreApplication app(argc, argv);
        if (UTILITY_API) UTILITY_API->DisplayMessageBox("Static QCoreApplication created.");
    } else {
         if (UTILITY_API) UTILITY_API->DisplayMessageBox("QCoreApplication instance already exists.");
    }

    // Initialize receiver in main thread
    g_receiver = new ReceiverObject(); 
    g_testRunning = true;

    // Launch emitter in separate thread
    g_emitterThread = new std::thread([](){
        qDebug() << "std::thread lambda starting in thread:" << QThread::currentThreadId();
        EmitterObject emitter;

        // Connect signal/slot with queued connection for thread safety
        QObject::connect(&emitter, &EmitterObject::testSignal,
                         g_receiver, &ReceiverObject::onTestSignalReceived,
                         Qt::QueuedConnection);
        qDebug() << "Signal/Slot connection made.";

        emitter.run();

        qDebug() << "std::thread lambda finishing.";
    });

    // Detach thread (simplified cleanup for demo)
    g_emitterThread->detach(); 
    delete g_emitterThread;
    g_emitterThread = nullptr;

    if (UTILITY_API) UTILITY_API->DisplayMessageBox("Minimal test thread launched (detached). Waiting for signal...");
}

// Plugin interface implementation
extern CLO_PLUGIN_SPECIFIER void DoFunction()
{
    // Guard against multiple runs while receiver exists
    if (g_receiver != nullptr) {
         if (UTILITY_API) UTILITY_API->DisplayMessageBox("Minimal Test Receiver still exists. Waiting for signal or cleanup.");
         return;
    }
    RunMinimalQtSignalSlotTest();
}

using namespace CLOAPI;

// Generated Qt meta-object code inclusion
#include "plugin.moc"

// Required plugin interface implementations
extern CLO_PLUGIN_SPECIFIER void DoFunctionAfterLoadingCLOFile(const char* fileExtenstion)
{
    // Optional post-file-load functionality
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
    return 1; // Position in menu (0: Above, 1: Below)
}