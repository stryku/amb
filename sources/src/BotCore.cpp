#include "BotCore.hpp"

namespace Amb
{
    BotCore::BotCore(const Config::GlobalConfig &config,
                     Amb::Module::Factory &modulesFactory,
                     Monitor::Mouse::MouseMonitorFactory& mousMonitorFactory) :
        modulesManager(config,
                       simulator,
                       modulesFactory,
                       mousMonitorFactory)
    {}

    void BotCore::startModule( Module::ModuleId moduleId )
    {
        modulesManager.run( moduleId );
    }

    void BotCore::attachNewProcess( DWORD pid )
    {
        auto hwnd = Utils::TibiaFinder::pidToHwnd(pid);
        simulator.attachToNewWindow(hwnd);
        modulesManager.attachToNewWindow(hwnd);
        modulesManager.attachToNewProcess(pid);

        attachedProcess = pid;
    }

    void BotCore::toggleModule( Amb::Module::ModuleId modId )
    {
        modulesManager.toggle( modId );
    }

    bool BotCore::isModuleRunning( Module::ModuleId modId )
    {
        return modulesManager.isRunning( modId );
    }

    BotCore::EnableDebugLogsObserver BotCore::getEnableDebugLogsObserver()
    {
        return [this](bool enabled)
        {
            modulesManager.setEnableDebugLogs(enabled);
        };
    }
}
