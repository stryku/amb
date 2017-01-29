#include <utils/Observable.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace tests
{
    using Observable = Amb::Utils::Observable<int>;

    struct Observator
    {
        MOCK_METHOD1(changedCallback, void(Observable::CallbackParameterType));

        auto getCallback()
        {
            return [this](Observable::CallbackParameterType newVal)
            {
                changedCallback(newVal);
            };
        }
    };

    TEST(Observable, ExpectCallbackCall)
    {
        Observator observator;
        Observable observable{ observator.getCallback() };

        EXPECT_CALL(observator, changedCallback(1));
        observable.set(1);

        EXPECT_CALL(observator, changedCallback(-20));
        observable.set(-20);
    }
}
