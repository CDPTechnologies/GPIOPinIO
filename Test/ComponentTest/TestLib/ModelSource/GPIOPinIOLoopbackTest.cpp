#include "GPIOPinIOLoopbackTest.h"

using namespace std;

void GPIOPinIOLoopbackTest::Create(const char* fullName)
{
  CDPComponent::Create(fullName);
  WriteSignal.Create("WriteSignal",this);
  ReadSignal.Create("ReadSignal",this);
}

void GPIOPinIOLoopbackTest::Configure(const char* xml)
{
  CDPComponent::Configure(xml);
}

void GPIOPinIOLoopbackTest::sendValueWithGPIOPin_isReceivedByAnotherGPIOPin()
{
  ValuePropagationTest<CDPSignal<bool>,bool>("Bool CDPChannel does not propagate value between virtual nodes.", WriteSignal, ReadSignal);
}

template<typename OBJ, typename TYPE>
void GPIOPinIOLoopbackTest::ValuePropagationTest(const char* message, OBJ& fromObj, OBJ& toObj)
{
  const int delay = 500;
  SetValue(fromObj,true);
  OSAPISleep(delay);
  AssertValue(message,toObj,true);

  SetValue(fromObj,false);
  OSAPISleep(delay);
  AssertValue(message,toObj,false);

  SetValue(fromObj,false);
  OSAPISleep(delay);
  AssertValue(message,toObj,false);
  
  SetValue(fromObj,true);
  OSAPISleep(delay);
  AssertValue(message,toObj,true);
}

template<typename OBJ, typename TYPE>
void GPIOPinIOLoopbackTest::SetValue(OBJ& obj, TYPE value)
{
  OSAPIMutexLocker lock(this->GetMemberAccessMutex());
  obj = value;
}

template<typename OBJ, typename TYPE>
void GPIOPinIOLoopbackTest::AssertValue(const char* message, OBJ& obj, TYPE expectedValue)
{
  OSAPIMutexLocker lock(this->GetMemberAccessMutex());
  CPPUNIT_ASSERT_EQUAL_MESSAGE(message,expectedValue,static_cast<TYPE>(obj));
}
