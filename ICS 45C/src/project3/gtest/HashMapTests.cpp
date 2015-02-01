// HashMapTests.cpp
//
// ICS 45C Fall 2014
// Project #3: Maps and Legends
//
// Write unit tests for your HashMap class here.  I've provided one test already,
// though I've commented it out, because it won't compile until you've implemented
// three things: the HashMap constructor, the HashMap destructor, and HashMap's
// size() member function.

#include <gtest/gtest.h>
#include "HashMap.hpp"


TEST(TestHashMap, sizeOfNewlyCreatedHashMapIsZero)
{
    HashMap empty;
    ASSERT_EQ(0, empty.size());
}

TEST(TestHashMap, bucketCountOfNewlyCreatedHashMapIsTen)
{
    HashMap empty;
    ASSERT_EQ(10, empty.bucketCount());
}

TEST(TestHashMap, shouldAddNewKeyValuePair)
{
    HashMap hm;
    hm.add("hello", "world");
    ASSERT_EQ(1, hm.size());
}

TEST(TestHashMap, shouldContainAddedKeyValuePair)
{
    HashMap hm;
    hm.add("hello", "world");
    ASSERT_TRUE(hm.contains("hello"));
}

TEST(TestHashMap, shouldNotContainNonexistingKeyValuePair)
{
    HashMap hm;
    hm.add("octo", "cat");
    ASSERT_FALSE(hm.contains("world"));
}

TEST(TestHashMap, shouldGetValueFromExistingKeyValuePair)
{
    HashMap hm;
    hm.add("hello", "world");
    ASSERT_EQ(hm.value("hello"), "world");
}

TEST(TestHashMap, shouldReturnEmptyStringForNonExistingKeyValuePair)
{
    HashMap hm;
    hm.add("hello", "world");
    ASSERT_EQ(hm.value("cat"), "");
}

TEST(TestHashMap, shouldNotUpdateExistingKeyValuePair)
{
    HashMap hm;
    hm.add("hello", "world");
    hm.add("hello", "cat");
    ASSERT_EQ(hm.value("hello"), "world");
}

TEST(TestHashMap, bucketShouldExpandWhenNearlyFull)
{
    HashMap hm;
    for (unsigned int i = 0; i < 8; i++) {
        hm.add(std::to_string(i), std::to_string(i));
    }
    ASSERT_EQ(10, hm.bucketCount());
    hm.add("should expand", "after this one");
    ASSERT_EQ(21, hm.bucketCount());
}

TEST(TestHashMap, loadFactorShouldNeverExceedFourFifth)
{
    HashMap hm;
    for (unsigned int i = 0; i < 1024; i++) {
        hm.add(std::to_string(i), std::to_string(i));
        ASSERT_LE(hm.loadFactor(), .8);
    }
}

TEST(TestHashMap, maxBucketSizeShouldBeSmall) // Non-Fatal
{
    HashMap hm;
    for (unsigned int i = 0; i < 1024; i++) {
        hm.add(std::to_string(i), std::to_string(i));
        EXPECT_LE(hm.maxBucketSize(), 5);
    }
}

TEST(TestHashMap, copyConstructorShouldWork)
{
    HashMap hm;
    hm.add("You", "review");
    HashMap hm_copy = hm;
    ASSERT_TRUE(hm_copy.contains("You"));
    ASSERT_FALSE(hm_copy.contains("I"));
}


TEST(TestHashMap, assignOperatorShouldWork)
{
    HashMap hm;
    hm.add("I", "code");
    HashMap hm_assign;
    hm_assign = hm;
    ASSERT_TRUE(hm_assign.contains("I"));
    ASSERT_FALSE(hm_assign.contains("you"));
}
