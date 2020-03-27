/*******************************************************************************
 The block below describes the properties of this PIP. A PIP is a short snippet
 of code that can be read by the Projucer and used to generate a JUCE project.

 BEGIN_JUCE_PIP_METADATA

  name:             TestRunner
  version:          0.0.1
  vendor:           Tracktion
  website:          www.tracktion.com
  description:      This simply runs the unit tests within Tracktion Engine.

  dependencies:     juce_audio_basics, juce_audio_devices, juce_audio_formats, juce_audio_processors, juce_audio_utils,
                    juce_core, juce_data_structures, juce_dsp, juce_events, juce_graphics,
                    juce_gui_basics, juce_gui_extra, juce_osc, tracktion_engine
  exporters:        linux_make, vs2017, xcode_iphone, xcode_mac

  moduleFlags:      JUCE_STRICT_REFCOUNTEDPOINTER=1, JUCE_PLUGINHOST_AU=1, JUCE_PLUGINHOST_VST3=1
  defines:          TRACKTION_UNIT_TESTS=1

<<<<<<< HEAD
  type:             Component
=======
  type:             Console
>>>>>>> 9e2c201b3d8118502745ce9100279d7f484b16a4
  mainClass:        TestRunner

 END_JUCE_PIP_METADATA

*******************************************************************************/

#pragma once

<<<<<<< HEAD

//==============================================================================
class TestRunner  : public Component
{
public:
    //==============================================================================
    TestRunner()
    {
        setSize (600, 400);
=======
using namespace tracktion_engine;

//==============================================================================
//==============================================================================
class TestUIBehaviour : public UIBehaviour
{
public:
    TestUIBehaviour() = default;
    
    void runTaskWithProgressBar (ThreadPoolJobWithProgress& t) override
    {
        TaskRunner runner (t);

         while (runner.isThreadRunning())
             if (! MessageManager::getInstance()->runDispatchLoopUntil (10))
                 break;
    }

private:
    //==============================================================================
    struct TaskRunner  : public Thread
    {
        TaskRunner (ThreadPoolJobWithProgress& t)
            : Thread (t.getJobName()), task (t)
        {
            startThread();
        }

        ~TaskRunner()
        {
            task.signalJobShouldExit();
            waitForThreadToExit (10000);
        }

        void run() override
        {
            while (! threadShouldExit())
                if (task.runJob() == ThreadPoolJob::jobHasFinished)
                    break;
        }

        ThreadPoolJobWithProgress& task;
    };
};


//==============================================================================
//==============================================================================
class TestEngineBehaviour : public EngineBehaviour
{
public:
    TestEngineBehaviour() = default;
    
    bool autoInitialiseDeviceManager() override
    {
        return false;
    }
};


//==============================================================================
//==============================================================================
struct CoutLogger : public Logger
{
    void logMessage (const String& message) override
    {
        std::cout << message << "\n";
    }
};


//==============================================================================
//==============================================================================
namespace TestRunner
{
    int runTests()
    {
        CoutLogger logger;
        Logger::setCurrentLogger (&logger);

        tracktion_engine::Engine engine { ProjectInfo::projectName, std::make_unique<TestUIBehaviour>(), std::make_unique<TestEngineBehaviour>() };
>>>>>>> 9e2c201b3d8118502745ce9100279d7f484b16a4

        UnitTestRunner testRunner;
        testRunner.setAssertOnFailure (false);
        testRunner.runTestsInCategory ("Tracktion");
        testRunner.runTestsInCategory ("Tracktion:Longer");

        int numFailues = 0;

        for (int i = 0; i <= testRunner.getNumResults(); ++i)
            if (auto result = testRunner.getResult (i))
                numFailues += result->failures;

<<<<<<< HEAD
        if (numFailues > 0)
            JUCEApplication::getInstance()->setApplicationReturnValue (1);

        JUCEApplication::getInstance()->quit();        
    }

    //==============================================================================
    void paint (Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    }

private:
    //==============================================================================
    tracktion_engine::Engine engine { ProjectInfo::projectName };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestRunner)
};
=======
        Logger::setCurrentLogger (nullptr);

        return numFailues > 0 ? 1 : 0;
    }
}


//==============================================================================
//==============================================================================
int main (int, char**)
{
    ScopedJuceInitialiser_GUI init;
    return TestRunner::runTests();
}
>>>>>>> 9e2c201b3d8118502745ce9100279d7f484b16a4
