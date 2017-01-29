#include <utils/Observable.hpp>
#include <tests/tests_related/utils/ObservatorMock.hpp>

#include <gtest/gtest.h>

namespace tests
{
    using Observable = Amb::Utils::Observable<int>;
    using Observator = Mock::Observator<int>;

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
