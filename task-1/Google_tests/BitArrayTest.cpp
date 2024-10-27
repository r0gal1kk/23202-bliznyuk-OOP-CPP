#include "gtest/gtest.h"
#include "BitArray.h"

TEST(BitArrayTest, DefaultConstructor) {
    BitArray bitArray;
    EXPECT_EQ(bitArray.size(), 0);
    EXPECT_TRUE(bitArray.empty());
}

TEST(BitArrayTest, ConstructorWithValue) {
    BitArray bitArray1(9, 170);
    EXPECT_EQ(bitArray1.size(), 9);
    EXPECT_FALSE(bitArray1.empty());
    EXPECT_EQ(bitArray1.to_string(), "010101010");
    BitArray bitArray2(8, 0);
    EXPECT_EQ(bitArray2.size(), 8);
    EXPECT_EQ(bitArray2.to_string(), "00000000");
    BitArray bitArray3(20, 65535);
    EXPECT_EQ(bitArray3.size(), 20);
    EXPECT_EQ(bitArray3.to_string(), "00001111111111111111");
}

TEST(BitArrayTest, CopyConstructor) {
    BitArray ba1(8, 204);
    BitArray ba2(ba1);
    EXPECT_EQ(ba2.size(), ba1.size());
    EXPECT_EQ(ba2.to_string(), ba1.to_string());
    ba1[0] = 0; // Изменяем первый бит
    EXPECT_NE(ba1.to_string(), ba2.to_string());
}

TEST(BitArrayTest, Swap) {
    BitArray ba1(8, 170);
    BitArray ba2(8, 85);
    EXPECT_EQ(ba1.to_string(), "10101010");
    EXPECT_EQ(ba2.to_string(), "01010101");
    ba1.swap(ba2);
    EXPECT_EQ(ba1.to_string(), "01010101");
    EXPECT_EQ(ba2.to_string(), "10101010");
    EXPECT_EQ(ba1.size(), 8);
    EXPECT_EQ(ba2.size(), 8);
}

TEST(BitArrayTest, SwapWithEmpty) {
    BitArray ba1(8, 255);
    BitArray ba2;
    EXPECT_EQ(ba1.to_string(), "11111111");
    EXPECT_TRUE(ba2.empty());
    ba1.swap(ba2);
    EXPECT_TRUE(ba1.empty());
    EXPECT_EQ(ba2.to_string(), "11111111");
}

TEST(BitArrayTest, SwapWithBothEmpty) {
    BitArray ba1;
    BitArray ba2;
    EXPECT_TRUE(ba1.empty());
    EXPECT_TRUE(ba2.empty());
    ba1.swap(ba2);
    EXPECT_TRUE(ba1.empty());
    EXPECT_TRUE(ba2.empty());
}

TEST(BitArrayTest, ResizeIncreasingSize) {
    BitArray ba(8, 170);
    ba.resize(16, 0);
    EXPECT_EQ(ba.size(), 16);
    EXPECT_EQ(ba.to_string(), "1010101000000000");
}

TEST(BitArrayTest, ResizeIncreasingSizeWithOnes) {
    BitArray ba(7, 85);
    ba.resize(15, 1);
    EXPECT_EQ(ba.size(), 15);
    EXPECT_EQ(ba.to_string(), "101010111111111");
}

TEST(BitArrayTest, ResizeDecreasingSize) {
    BitArray ba(10, 255);
    ba.resize(8);
    EXPECT_EQ(ba.size(), 8);
    EXPECT_EQ(ba.to_string(), "00111111");
}

TEST(BitArrayTest, ResizeWithMixedData) {
    BitArray ba(10, 819);
    ba.resize(15, 1);
    EXPECT_EQ(ba.size(), 15);
    EXPECT_EQ(ba.to_string(), "110011001111111");
}

TEST(BitArrayTest, ResizeWithInvalidValue) {
    BitArray ba(8, 0);
    EXPECT_THROW(ba.resize(10, 2), std::invalid_argument);
    EXPECT_THROW(ba.resize(-10, 1), std::invalid_argument);
}

TEST(BitArrayTest, ResizeToSmallerSize) {
    BitArray ba(8, 0b11111111);
    ba.resize(5);
    EXPECT_EQ(ba.size(), 5);
    EXPECT_EQ(ba.to_string(), "11111");
}

TEST(BitArrayTest, ClearNonEmptyArray) {
    BitArray ba(8, 170);
    EXPECT_EQ(ba.size(), 8);
    EXPECT_FALSE(ba.empty());
    EXPECT_EQ(ba.to_string(), "10101010");
    ba.clear();
    EXPECT_EQ(ba.size(), 0);
    EXPECT_TRUE(ba.empty());
}

TEST(BitArrayTest, ClearAlreadyEmptyArray) {
    BitArray ba;
    EXPECT_EQ(ba.size(), 0);
    EXPECT_TRUE(ba.empty());
    ba.clear();
    EXPECT_EQ(ba.size(), 0);
    EXPECT_TRUE(ba.empty());
}

TEST(BitArrayTest, PushBackIntoEmptyArray) {
    BitArray ba;
    EXPECT_EQ(ba.size(), 0);
    EXPECT_TRUE(ba.empty());
    ba.push_back(1);
    EXPECT_EQ(ba.size(), 1);
    EXPECT_EQ(ba.to_string(), "1");
}

TEST(BitArrayTest, PushBackMultipleBits) {
    BitArray ba;
    ba.push_back(1);
    ba.push_back(0);
    ba.push_back(1);
    ba.push_back(1);
    EXPECT_EQ(ba.size(), 4);
    EXPECT_EQ(ba.to_string(), "1011");
}

TEST(BitArrayTest, PushBackAndResize) {
    BitArray ba(8, 255);
    ba.push_back(0);
    EXPECT_EQ(ba.size(), 9);
    EXPECT_EQ(ba.to_string(), "111111110");
}

TEST(BitArrayTest, OperatorAndEqual) {
    BitArray ba1(10, 204);
    BitArray ba2(10, 170);
    ba1 &= ba2;
    EXPECT_EQ(ba1.to_string(), "0010001000");
}

TEST(BitArrayTest, OperatorOrEqual) {
    BitArray ba1(10, 204);
    BitArray ba2(10, 170);
    ba1 |= ba2;
    EXPECT_EQ(ba1.to_string(), "0011101110");
}

TEST(BitArrayTest, OperatorXorEqual) {
    BitArray ba1(10, 204);
    BitArray ba2(10, 170);
    ba1 ^= ba2;
    EXPECT_EQ(ba1.to_string(), "0001100110");
}

TEST(BitArrayTest, OperatorsWithDifferentSizes) {
    BitArray ba1(10, 204);
    BitArray ba2(15, 170);
    EXPECT_THROW(ba1 &= ba2, std::invalid_argument);
    EXPECT_THROW(ba1 |= ba2, std::invalid_argument);
    EXPECT_THROW(ba1 ^= ba2, std::invalid_argument);
}

TEST(BitArrayTest, OperatorLeftShiftEqual) {
    BitArray ba(15, 4545); // 001 0001 1100 0001
    ba <<= 3;
    EXPECT_EQ(ba.count(), 4);
    EXPECT_EQ(ba.to_string(), "000111000001000");
    ba <<= 40;
    EXPECT_EQ(ba.count(), 0);
    EXPECT_EQ(ba.to_string(), "000000000000000");
}

TEST(BitArrayTest, OperatorRightShiftEqual) {
    BitArray ba(15, 4545); // 001 0001 1100 0001
    ba >>= 4;
    EXPECT_EQ(ba.count(), 4);
    EXPECT_EQ(ba.to_string(), "000000100011100");
    ba >>= 40;
    EXPECT_EQ(ba.count(), 0);
    EXPECT_EQ(ba.to_string(), "000000000000000");
}

TEST(BitArrayTest, OperatorLeftShift) {
    BitArray ba(15, 4545);
    BitArray result = ba << 3;
    EXPECT_EQ(result.count(), 4);
    EXPECT_EQ(result.to_string(), "000111000001000");
}

TEST(BitArrayTest, OperatorRightShift) {
    BitArray ba(15, 4545); // 170 в десятичном
    BitArray result = ba >> 4;
    EXPECT_EQ(result.count(), 4);
    EXPECT_EQ(result.to_string(), "000000100011100");
}

TEST(BitArrayTest, ShiftByZero) {
    BitArray ba(8, 0b10101010); // 170 в десятичном
    ba <<= 0; // Сдвиг влево на 0
    EXPECT_EQ(ba.count(), 4);
    EXPECT_EQ(ba.to_string(), "10101010");
    ba >>= 0; // Сдвиг вправо на 0
    EXPECT_EQ(ba.count(), 4);
    EXPECT_EQ(ba.to_string(), "10101010");
}

TEST(BitArrayTest, NegativeShift) {
    BitArray ba(15, 4545);
    EXPECT_THROW(ba <<= -2, std::invalid_argument);
    EXPECT_THROW(ba >>= -2, std::invalid_argument);
    BitArray result;
    EXPECT_THROW(result = ba << -2, std::invalid_argument);
    EXPECT_THROW(result = ba >> -2, std::invalid_argument);
}

TEST(BitArrayTest, Set) {
    BitArray ba(15);
    ba.set();
    EXPECT_EQ(ba.count(), 15);
    EXPECT_EQ(ba.size(), 15);
    EXPECT_EQ(ba.to_string(), "111111111111111");
}

TEST(BitArrayTest, Reset) {
    BitArray ba(13, 8191); // 1 1111 1111 1111
    EXPECT_EQ(ba.count(), 13);
    ba.reset();
    EXPECT_EQ(ba.count(), 0);
    EXPECT_EQ(ba.size(), 13);
    EXPECT_EQ(ba.to_string(), "0000000000000");
    ba.resize(17, 1);
    EXPECT_EQ(ba.count(), 4);
    EXPECT_EQ(ba.to_string(), "00000000000001111");
    ba.reset();
    EXPECT_EQ(ba.count(), 0);
    EXPECT_EQ(ba.to_string(), "00000000000000000");
}

TEST(BitArrayTest, AnyTrue) {
    BitArray ba1(8, 5);
    BitArray ba2(8);
    EXPECT_TRUE(ba1.any());
    EXPECT_FALSE(ba2.any());
    EXPECT_TRUE(ba2.none());
    EXPECT_FALSE(ba1.none());
    BitArray ba3;
    EXPECT_TRUE(ba3.none());
    EXPECT_FALSE(ba3.any());
}

TEST(BitArrayTest, OperatorNot) {
    BitArray ba(12, 1252);
    BitArray result = ~ba;
    EXPECT_EQ(result.size(), 12);
    EXPECT_EQ(result.to_string(), "101100011011");
}

TEST(BitArrayTest, IndexOperator) {
    BitArray ba(8);
    ba[0] = 1;
    ba[3] = 1;
    bool a = ba[0];
    EXPECT_EQ(a, 1);
    EXPECT_EQ(ba[0], 1);
    EXPECT_EQ(ba[1], 0);
    EXPECT_EQ(ba[3], 1);
    EXPECT_EQ(ba[7], 0);
    EXPECT_THROW(ba[-1], std::out_of_range);
    EXPECT_THROW(ba[8], std::out_of_range);
}

TEST(BitArrayTest, AssignmentOperator) {
    BitArray ba1(8, 170);
    BitArray ba2(8);
    ba2 = ba1;
    EXPECT_EQ(ba2[0], 1);
    EXPECT_EQ(ba2[1], 0);
    EXPECT_EQ(ba2[2], 1);
    EXPECT_EQ(ba2[3], 0);
    EXPECT_EQ(ba2[4], 1);
    EXPECT_EQ(ba2[5], 0);
    EXPECT_EQ(ba2[6], 1);
    EXPECT_EQ(ba2[7], 0);
    ba1[0] = 0;
    EXPECT_EQ(ba1[0], 0);
    EXPECT_EQ(ba2[0], 1);
}

TEST(BitArrayTest, EqualityOperators) {
    BitArray a(8, 170);
    BitArray b(8, 170);
    BitArray c(8, 255);
    BitArray d(9, 255);
    EXPECT_FALSE(a == d);
    EXPECT_FALSE(b == d);
    EXPECT_TRUE(a != d);
    EXPECT_TRUE(b != d);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_TRUE(a != c);
    EXPECT_FALSE(a != b);
}

TEST(BitArrayTest, BitwiseOperators) {
    BitArray a(8, 170);
    BitArray b(8, 204);
    BitArray c(9, 100);
    BitArray and_result = a & b; // 0b10001000
    BitArray or_result = a | b;  // 0b11101110
    BitArray xor_result = a ^ b; // 0b01100110
    EXPECT_THROW(BitArray result = a & c, std::invalid_argument);
    EXPECT_THROW(BitArray result = a | c, std::invalid_argument);
    EXPECT_THROW(BitArray result = a ^ c, std::invalid_argument);
    EXPECT_EQ(and_result.to_string(), "10001000");
    EXPECT_EQ(or_result.to_string(), "11101110");
    EXPECT_EQ(xor_result.to_string(), "01100110");
}
