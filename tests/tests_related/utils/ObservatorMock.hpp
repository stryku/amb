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
            WrappedType value;

            MOCK_METHOD1_T(changedCallback, void(typename Observable::CallbackParameterType));

            auto getCallback()
            {
                return [this](Observable::CallbackParameterType newVal)
                {
                    if(shouldCall)
                        changedCallback(newVal);

                    value = newVal;
                };
            }

            void setCallbackCallPolicy(bool newShouldCall)
            {
                shouldCall = newShouldCall;
            }

        private:
            bool shouldCall{ true };
        };
    }
}
