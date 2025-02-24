// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    // if empty, the size must be 0
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    add_entries(1);

    // is the collection still empty?
    // if not empty, what must the size be?
    EXPECT_FALSE(collection->empty());
    EXPECT_EQ(collection->size(), 1);
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // collection should start empty
    ASSERT_TRUE(collection->empty());

    add_entries(5);

    // collection should npw not be empty. It should contain 5 values
    EXPECT_FALSE(collection->empty());
    EXPECT_EQ(collection->size(), 5);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeGreaterThanEqualToVariousSizes)
{
    // checking to make sure max size is greater than or equal to current size
    EXPECT_GE(collection->max_size(), collection->size());

    // clearing collection and checking to make sure max size is greater than or equal to current size after adding 1 value
    collection->clear();
    add_entries(1);
    EXPECT_GE(collection->max_size(), collection->size());

    // clearing collection and checking to make sure max size is greater than or equal to current size after adding 5 values
    collection->clear();
    add_entries(5);
    EXPECT_GE(collection->max_size(), collection->size());

    // clearing collection and checking to make sure max size is greater than or equal to current size after adding 10 values
    collection->clear();
    add_entries(10);
    EXPECT_GE(collection->max_size(), collection->size());
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityGreaterThanEqualToVariousSizes)
{
    // checking to make sure the capacity is greater than or equal to current size
    EXPECT_GE(collection->capacity(), collection->size());

    // clearing collection and checking to make sure the capacity is greater than or equal to current size after adding 1 value
    collection->clear();
    add_entries(1);
    EXPECT_GE(collection->capacity(), collection->size());

    // clearing collection and checking to make sure the capacity is greater than or equal to current size after adding 5 values
    collection->clear();
    add_entries(5);
    EXPECT_GE(collection->capacity(), collection->size());

    // clearing collection and checking to make sure the capacity is greater than or equal to current size after adding 10 values
    collection->clear();
    add_entries(10);
    EXPECT_GE(collection->capacity(), collection->size());
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizingIncreasesCollectionSize)
{
    // testing to make sure the collection starts at 0 and then increases to 10 after resizing
    ASSERT_EQ(collection->size(), 0);
    collection->resize(10);
    EXPECT_EQ(collection->size(), 10);
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizingDecreasesCollectionSize)
{
    // starting with size of 10 entries
    add_entries(10);
    ASSERT_EQ(collection->size(), 10);

    // sizing down to 5 and making sure the size decreased to 5 values
    collection->resize(5);
    EXPECT_EQ(collection->size(), 5);
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizingDecreasesSizeToZero)
{
    // starting with size of 10 entries
    add_entries(10);
    ASSERT_EQ(collection->size(), 10);

    // resizing to zero and verifying that the collection is empty
    collection->resize(0);
    EXPECT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearErasesCollection)
{
    // starting with size of 10 entries
    add_entries(10);
    ASSERT_EQ(collection->size(), 10);

    // clearing collection and verifying that the clear brought the size to 0
    collection->clear();
    EXPECT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseBeginEndErasesCollection)
{
    // starting with size of 10 entries
    add_entries(10);
    ASSERT_EQ(collection->size(), 10);

    // erasing the collection from beginning to end and verifiying that the collection size is now 0
    collection->erase(collection->begin(), collection->end());
    EXPECT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacityButNotSize)
{
    // starting with size of 10 entries
    // storing the size and capacity of this new collection into their own respective variables
    add_entries(10);
    int oldSize = collection->size();
    int oldCapacity = collection->capacity();

    // reserving 10 additional spots
    collection->reserve(oldCapacity + 10);

    // making sure the reserve call did not increase the size
    EXPECT_EQ(collection->size(), oldSize);

    // making sure the new capacity is equal to the old capacity + 10
    EXPECT_EQ(collection->capacity(), oldCapacity + 10);
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, InvalidIndexThrowsOutOfRangeException)
{
    // starting with size of 10 entries
    add_entries(10);

    // trying to get the value at index 15 which is out of bounds, expecting out of range exception
    EXPECT_THROW(collection->at(15), std::out_of_range);
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative

// positive test to check that the beck method returns the correct value
TEST_F(CollectionTest, BackReturnsCorrectValue) {
    // starting with size of 10 entries
    add_entries(10);

    // manually getting the "back" value (last value)
    int backElement = collection->at(9);

    // checking to make sure that the back method returns the same value as the manual method
    EXPECT_EQ(backElement, collection->back());
}

// negative test to ensure that values can't be accessed in an empty collection
TEST_F(CollectionTest, AccessingValuesInEmptyCollectionThrowsOutOfRangeException)
{
    // make sure the collection is empty
    ASSERT_TRUE(collection->empty());

    // try accessing an element at 0 in the collection and make sure an out of range exception is thrown
    EXPECT_THROW(collection->at(0), std::out_of_range);
}
