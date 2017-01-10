set (AMB_inc
            ${inc_dir}/Bot.hpp
            ${inc_dir}/BotCore.hpp
            ${inc_dir}/ConfigFromUiGenerator.hpp
            ${inc_dir}/Configs.hpp
            ${inc_dir}/ModulesManager.hpp
            ${inc_dir}/ScreenCapturer.hpp
            ${inc_dir}/Simulator.hpp
            ${inc_dir}/TibiaFinder.hpp
            ${inc_dir}/TibiaReader.hpp
            ${inc_dir}/TibiaScreenReader.hpp
            ${inc_dir}/utils.hpp
            
            ${inc_dir}/capture/CaptureMode.hpp
            ${inc_dir}/capture/ConstPixels.hpp
            ${inc_dir}/capture/CoveredWindowCapturer.hpp
            ${inc_dir}/capture/ItemCapturer.hpp
            ${inc_dir}/capture/ItemsWindowReader.hpp
            ${inc_dir}/capture/NotCoveredWindowCapturer.hpp
            ${inc_dir}/capture/WindowCapturer.hpp
            ${inc_dir}/capture/FrameCapturer.hpp
            
            ${inc_dir}/client/TibiaClientType.hpp
            
            ${inc_dir}/client/window/TibiaWindow.hpp
            ${inc_dir}/client/window/TibiaItemsWindow.hpp
            
            ${inc_dir}/client/reader/HealthManaReader.hpp
            
            ${inc_dir}/client/TibiaClientWindowRectObserver.hpp
            ${inc_dir}/client/TibiaClientRectCornersObserver.hpp
            
            ${inc_dir}/client/window/finder/TibiaWindowsFinder.hpp
            ${inc_dir}/client/window/finder/DeadCreatureWindowFinder.hpp
            ${inc_dir}/client/window/finder/DeadCreatureWindowFinderFactory.hpp
            
            ${inc_dir}/config/ConfigFileManager.hpp
            
            ${inc_dir}/config/layout/PixelsLayoutConfig.hpp
            
            ${inc_dir}/config/layout/health_heart/HealthHeartConfig.hpp
            ${inc_dir}/config/layout/health_heart/HealthHeartConfigFactory.hpp
            ${inc_dir}/config/layout/health_heart/StaticValues.hpp
            
            ${inc_dir}/config/layout/health_mana_bars/HealthManaBars.hpp
            ${inc_dir}/config/layout/health_mana_bars/HealthManaBarsConfigFactory.hpp

            ${inc_dir}/db/Database.hpp
            ${inc_dir}/db/Items.hpp
            ${inc_dir}/db/Containers.hpp
            
            ${inc_dir}/db/static/containers/ContainersDbItem.hpp
            ${inc_dir}/db/static/containers/ContainersDbData.hpp
            
            ${inc_dir}/db/static/items/ItemsDbItem.hpp
            ${inc_dir}/db/static/items/ItemsDbData.hpp
            
            ${inc_dir}/graphics/Image.hpp
            
            ${inc_dir}/log/log.hpp
            
            ${inc_dir}/log/details/Logger.hpp
            
            ${inc_dir}/module/Module.hpp
            ${inc_dir}/module/ModuleCore.hpp
            ${inc_dir}/module/ModuleCore.hpp
            ${inc_dir}/module/ModulesFactory.hpp
            
            ${inc_dir}/module/modules/Healer.hpp
            ${inc_dir}/module/modules/LooterModule.hpp
            
            ${inc_dir}/module/ui_remover/LooterUiRemover.hpp
            
            ${inc_dir}/ui/UiControls.hpp
            
            ${inc_dir}/ui/controls/Table.hpp
            
            ${inc_dir}/ui/modules/healer/HealerRulesTable.hpp
            ${inc_dir}/ui/modules/healer/HealRule.hpp
            
            ${inc_dir}/ui/modules/looter/Category.hpp
            ${inc_dir}/ui/modules/looter/LooterCategoriesTable.hpp
            ${inc_dir}/ui/modules/looter/LooterItemsTable.hpp
            ${inc_dir}/ui/modules/looter/LootItem.hpp
            ${inc_dir}/ui/modules/looter/ToOnto.hpp
            
            ${inc_dir}/ui/updaters/AdvancedSettingsUiUpdater.hpp
            ${inc_dir}/ui/updaters/HealerUiUpdater.hpp
            ${inc_dir}/ui/updaters/LooterUiUpdater.hpp
            ${inc_dir}/ui/updaters/UiUpdater.hpp
            ${inc_dir}/ui/updaters/MainWindowTitleUpdater.hpp
            
            ${inc_dir}/ui/updaters/details/MainWindowTitleBuilder.hpp
            
            ${inc_dir}/utils/log.hpp
            ${inc_dir}/utils/PropertyTreeBuilder.hpp
            ${inc_dir}/utils/Structs.hpp
            ${inc_dir}/utils/ToString.hpp
            ${inc_dir}/utils/Observable.hpp
            ${inc_dir}/utils/ThreadWorker.hpp
            ${inc_dir}/utils/ForwardDeclarePos.hpp
            
            ${inc_dir}/utils/random/RandomBetween.hpp
            ${inc_dir}/utils/random/RandomOffset.hpp
            
            ${inc_dir}/utils/traits/traits.hpp
            
            ${inc_dir}/security/debug/DebugModeChecker.hpp
            ${inc_dir}/security/debug/DebugModeCheckerFactory.hpp
            
            ${inc_dir}/simulate/MouseSimulator.hpp
                    
            PARENT_SCOPE)
					
set (AMB_src 
            ${src_dir}/Bot.cpp
            ${src_dir}/BotCore.cpp
            ${src_dir}/ConfigFromUiGenerator.cpp
            ${src_dir}/Healer.cpp
            ${src_dir}/ModulesManager.cpp
            ${src_dir}/Simulator.cpp
            ${src_dir}/TibiaFinder.cpp
            ${src_dir}/utils.cpp
            
            ${src_dir}/capture/ItemCapturer.cpp
            ${src_dir}/capture/ItemsWindowReader.cpp
            ${src_dir}/capture/FrameCapturer.cpp
            
            ${src_dir}/client/TibiaClientType.cpp
            
            ${src_dir}/client/reader/HealthManaReader.cpp
            
            ${src_dir}/client/TibiaClientWindowRectObserver.cpp
            ${src_dir}/client/TibiaClientRectCornersObserver.cpp
            
            ${src_dir}/client/window/finder/TibiaWindowsFinder.cpp
            ${src_dir}/client/window/finder/DeadCreatureWindowFinder.cpp
            ${src_dir}/client/window/finder/DeadCreatureWindowFinderFactory.cpp
            
            ${src_dir}/config/ConfigFileManager.cpp
            
            ${src_dir}/config/layout/health_heart/HealthHeartConfigFactory.cpp
            
            ${src_dir}/config/layout/health_mana_bars/HealthManaBarsConfigFactory.cpp
            
            ${src_dir}/db/Containers.cpp
            
            ${src_dir}/db/static/containers/ContainersDbData.cpp
            
            ${src_dir}/db/static/items/ItemsDbData.cpp
            
            ${src_dir}/log/details/Logger.cpp
            
            ${src_dir}/module/Module.cpp
            ${src_dir}/module/ModuleCore.cpp
            ${src_dir}/module/ModulesFactory.cpp
            
            ${src_dir}/module/modules/LooterModule.cpp
            
            ${src_dir}/module/ui_remover/LooterUiRemover.cpp
            
            ${src_dir}/ui/modules/healer/HealRule.cpp
            
            ${src_dir}/ui/modules/looter/Items.cpp
            
            ${src_dir}/utils/ThreadWorker.cpp
            
            ${src_dir}/ui/updaters/MainWindowTitleUpdater.cpp
            
            ${src_dir}/ui/updaters/details/MainWindowTitleBuilder.cpp

            ${src_dir}/security/debug/DebugModeChecker.cpp
            ${src_dir}/security/debug/DebugModeCheckerFactory.cpp
            
            ${src_dir}/simulate/MouseSimulator.cpp
            
            PARENT_SCOPE)