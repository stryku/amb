#pragma once

#include "screencapturer.hpp"
#include "tibiascreenreader.hpp"

#include <QtDebug>

namespace AMB
{
    namespace Readers
    {
        namespace details
        {
            class TibiaReader
            {
            public:
                TibiaReader()
                    : reader{ screen }
                    , screenCapturer{ screen }
                {}

                size_t getHpPercent()
                {
                    qDebug("Reading hp\n");
                    return reader.getHpPercent();
                }

                size_t getManaPercent()
                {
                    qDebug("Reading mana\n");
                    return reader.getManaPercent();
                }

                void newFrame()
                {
                    screenCapturer.recapture();
                }

                bool isVisible() const
                {
                    screen.toCb();
                    return reader.isHearthVisible();
                }

            private:
                Image screen;
                TibiaScreenReader reader;
                ScreenCapturer screenCapturer;
            };
        }
    }
}
