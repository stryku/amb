#pragma once

#include "config/layout/health_heart/HealthHeartConfig.hpp"
#include "client/TibiaClientType.hpp"
#include "graphics/Image.hpp"
#include "config/layout/health_heart/HealthHeartConfigFactory.hpp"
#include "log/log.hpp"
#include "client/TibiaClientWindowInfo.hpp"
#include "capture/FrameCapturer.hpp"
#include "capture/CaptureMode.hpp"

namespace Amb
{
    namespace Client
    {
        namespace Finder
        {
            class HealthManaFinder
            {
            public:
                HealthManaFinder(const Client::TibiaClientWindowInfo &tibiaClientWindowInfo)
                    : tibiaClientWindowInfo{ tibiaClientWindowInfo }
                    , frameCapturer{ screen, tibiaClientWindowInfo }
                {}

                boost::optional<Config::Layout::HealthHeart::HealthHeartBasicConfig> find(TibiaClientType clientType)
                {
                    frameCapturer.captureRightStrip();
                    const auto lastCapturedRect = frameCapturer.getLastCaptureRect();

                    Config::Layout::HealthHeart::HealthHeartBasicConfig config;
                    RelativeRect captureRect;
                    captureRect.rect = getBasicRect(clientType);
                    captureRect.relationPoint = tibiaClientWindowInfo.corners.topRight;
                    Rect rect = captureRect.relativeToRect(lastCapturedRect);

                    config.relationPoint = lastCapturedRect.relationPoint;

                    screen.toCb();

                    for (rect.y = 0;
                         static_cast<size_t>(rect.y) < screen.h - 50;
                         ++rect.y)
                    {
                        if (screen.getSprite(rect) == Config::Layout::HealthHeart::Static::pixels)
                        {
                            config.pos.y = rect.y;
                            config.pos.x = rect.x - screen.w;
                            config.isSmall = true;

                            LOG_DEBUG("Found heart. offsetFromRight: {}, y: {}, isSmall: {}",
                                      config.pos.x,
                                      config.pos.y,
                                      config.isSmall ? "true" : "false");

                            return config;
                        }
                    }

                    LOG_DEBUG("Basic finding failed. Trying bruteforce");

                    return findBruteForce(clientType);
                }

                boost::optional<Config::Layout::HealthHeart::HealthHeartBasicConfig> findBruteForce(TibiaClientType clientType)
                {
                    RelativeRect captureRect;

                    captureRect.relationPoint = tibiaClientWindowInfo.corners.topLeft;
                    captureRect.rect.x = 0;
                    captureRect.rect.y = 0;
                    captureRect.rect.w = tibiaClientWindowInfo.corners.bottomRight.x - tibiaClientWindowInfo.corners.bottomLeft.x;
                    captureRect.rect.h = tibiaClientWindowInfo.corners.bottomLeft.y - tibiaClientWindowInfo.corners.topLeft.y;

                    LOG_DEBUG("Captiring screen. Rect: " LOG_RECT_TO_STRING(captureRect.rect));
                    frameCapturer.newFrame(captureRect.rect);
                    const auto lastCapturedRect = frameCapturer.getLastCaptureRect();

                    Config::Layout::HealthHeart::HealthHeartBasicConfig config;
                    Rect rect = captureRect.relativeToRect(lastCapturedRect);

                    for (; rect.x > static_cast<int>(screen.w / 2); --rect.x)
                    {
                        for (rect.y = 0;
                             static_cast<size_t>(rect.y) < screen.h - 50;
                             ++rect.y)
                        {
                            const auto sprite = screen.getSprite(rect);

                            if (sprite == Config::Layout::HealthHeart::Static::pixels)
                            {
                                config.pos.y = rect.y;
                                config.pos.x = rect.x - screen.w;
                                config.isSmall = true;

                                LOG_DEBUG("Found heart. offsetFromRight: {}, y: {}, isSmall: {}",
                                          config.pos.x,
                                          config.pos.y,
                                          config.isSmall ? "true" : "false");

                                return config;
                            }

                            if (sprite == Config::Layout::HealthHeart::Static::pixels_big)
                            {
                                config.pos.y = rect.y;
                                config.pos.x = rect.x - screen.w;
                                config.isSmall = false;

                                LOG_DEBUG("Found heart. offsetFromRight: {}, y: {}, isSmall: {}",
                                          config.pos.x,
                                          config.pos.y,
                                          config.isSmall ? "true" : "false");

                                return config;
                            }
                        }
                    }

                    LOG_DEBUG("Btureforce finding failed.");

                    return{};
                }

                void attachToNewWindow(HWND hwnd)
                {
                    frameCapturer.attachToNewWindow(hwnd);
                }

                void setCaptureMode(const Capture::Mode::CaptureMode newCaptureMode)
                {
                    frameCapturer.setCaptureMode(newCaptureMode);
                }


            private:
                Rect getBasicRect(TibiaClientType clientType) const
                {
                    Rect rect;

                    rect.w = Config::Layout::HealthHeart::Static::size.w;
                    rect.h = Config::Layout::HealthHeart::Static::size.h;

                    rect.y = 0;

                    switch (clientType)
                    {
                    case Amb::Client::TibiaClientType::Tibia10:
                        rect.x = - static_cast<int>(Config::Layout::HealthHeart::Static::offsetFromRight_10);
                        break;

                    case Amb::Client::TibiaClientType::Tibia11:
                        rect.x = - static_cast<int>(Config::Layout::HealthHeart::Static::offsetFromRight_11);
                        break;

                    case Amb::Client::TibiaClientType::Flash:
                    default:
                        assert(false);
                    }

                    return rect;
                }

                const Client::TibiaClientWindowInfo &tibiaClientWindowInfo;
                Graphics::Image screen;
                Capture::FrameCapturer frameCapturer;
            };
        }
    }
}
