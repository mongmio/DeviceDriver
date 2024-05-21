#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "DeviceDriver.h"
#include "Exceptions.h"

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

TEST_F(DeviceDriverTest, VerifyExceptionBeforeWirte) {
	EXPECT_CALL(deviceMock, read(testing::_))
		.WillRepeatedly(testing::Return(0x1234));

	constexpr long TEST_ADDRESS = 0x1234;
	EXPECT_THROW(driver.write(TEST_ADDRESS, 0x1234), WriteFailException);
}

TEST_F(DeviceDriverTest, VerifyEmptyBeforeWirte) {
	EXPECT_CALL(deviceMock, read(testing::_))
		.WillOnce(testing::Return(0xFF));
	EXPECT_CALL(deviceMock, write(testing::_, testing::_))
		.Times(1);

	constexpr long TEST_ADDRESS = 0x1234;
	driver.write(TEST_ADDRESS, 0x1234);
}