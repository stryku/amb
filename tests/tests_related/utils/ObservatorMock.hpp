#include <utils/Observable.hpp>

#include <gmock/gmock.h>

namespace tests
{
    namespace Mock
    {
        template <typename WrappedType>
        struct Observator
        {
            using Observable = Amb::Utils::Observable<WrappedType>;
            MOCK_METHOD1_T(changedCallback, void(typename Observable::CallbackParameterType));

            auto getCallback()
            {
                return [this](Observable::CallbackParameterType newVal)
                {
                    changedCallback(newVal);
                };
            }
        };
    }
}
