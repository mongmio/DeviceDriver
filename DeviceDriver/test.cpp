#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "DeviceDriver.h"

class FlashMemoryDeviceMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long), (override));
	MOCK_METHOD(void, write, (long, unsigned char), (override));
};

class DeviceDriverTest : public testing::Test
{
protected:
	FlashMemoryDeviceMock deviceMock{};
	DeviceDriver driver{ &deviceMock };
};
TEST_F(DeviceDriverTest, Read5TimesAndVerifyData) {
	EXPECT_CALL(deviceMock, read(testing::_)).Times(5);
	constexpr long TEST_ADDRESS = 0x1234;
	driver.read(TEST_ADDRESS);
}

TEST_F(DeviceDriverTest, VerifyEmptyBeforeWirte) {

}