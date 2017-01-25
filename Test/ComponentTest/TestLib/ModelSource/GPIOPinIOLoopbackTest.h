#ifndef GPIOPINIOLOOPBACKTEST_H
#define GPIOPINIOLOOPBACKTEST_H

#include <CDPSystem/Base/CDPComponent.h>
#include <CDPUnit/CDPUnit.h>
#include <cppunit/TestFixture.h>

class GPIOPinIOLoopbackTest
    : public CDPComponent
    , public CDPUnit::DynamicTestInterface
    , public CppUnit::TestFixture
{
  CDP_UNIT_TEST_SUITE_DYNAMIC( GPIOPinIOLoopbackTest );
  CDP_UNIT_TEST_DYNAMIC( sendValueWithGPIOPin_isReceivedByAnotherGPIOPin );
  CDP_UNIT_TEST_SUITE_END_DYNAMIC();
  CDP_UNIT_TEST_SUITE_REGISTER_DYNAMIC();

public:
  void Create(const char* fullName) override;
  void Configure(const char* xml) override;
  void sendValueWithGPIOPin_isReceivedByAnotherGPIOPin();

private:
  template<typename OBJ, typename TYPE> void ValuePropagationTest(const char* message, OBJ& fromObj, OBJ& toObj);
  template<typename OBJ, typename TYPE> void SetValue(OBJ& obj, TYPE value);
  template<typename OBJ, typename TYPE> void AssertValue(const char* message, OBJ& obj, TYPE expectedValue);

  CDPSignal<bool> WriteSignal;
  CDPSignal<bool> ReadSignal;
};

#endif

