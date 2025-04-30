/**
 * Unit Tests for the class
**/

/*#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Example "smoke test" (can be deleted)
TEST(GuesserTest, smoke_test)
{
  Guesser object("Secret");
  ASSERT_EQ( 1+1, 2 );
}
*/
#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
protected:
    GuesserTest() {}
    virtual ~GuesserTest() {}
    virtual void SetUp() {}
    virtual void TearDown() {}
};

// Test that a correct guess returns true
TEST(GuesserTest, CorrectGuessReturnsTrue)
{
    Guesser g("apple");
    ASSERT_TRUE(g.match("apple"));
}

// Test that an incorrect guess returns false
TEST(GuesserTest, IncorrectGuessReturnsFalse)
{
    Guesser g("apple");
    ASSERT_FALSE(g.match("banana"));
}

// Test that remaining() starts at 3
TEST(GuesserTest, RemainingStartsAtThree)
{
    Guesser g("apple");
    ASSERT_EQ(g.remaining(), 3);
}

// Test that remaining() decreases after a close wrong guess
TEST(GuesserTest, RemainingDecreasesOnCloseWrongGuess)
{
    Guesser g("apple");
    g.match("applo"); // Only 1 character off – considered a "close" guess
    ASSERT_EQ(g.remaining(), 2);
}

// Test that correct guess does not decrease remaining
TEST(GuesserTest, CorrectGuessDoesNotDecreaseRemaining)
{
    Guesser g("apple");
    g.match("apple");
    ASSERT_EQ(g.remaining(), 3);
}

// Test that match returns false when out of attempts after close wrong guesses
TEST(GuesserTest, LockedAfterThreeCloseWrongGuesses)
{
    Guesser g("apple");
    g.match("applo"); // Close
    g.match("appld"); // Close
    g.match("applf"); // Close
    ASSERT_EQ(g.remaining(), 0);
    ASSERT_FALSE(g.match("apple")); // Should be locked now
}

// Test case sensitivity
TEST(GuesserTest, CaseSensitiveFail)
{
    Guesser g("Apple");
    ASSERT_FALSE(g.match("apple")); // Case mismatch
}

// Test that repeated correct guesses don’t reduce remaining
TEST(GuesserTest, RepeatedCorrectGuessesKeepRemaining)
{
    Guesser g("apple");
    g.match("apple");
    g.match("apple");
    ASSERT_EQ(g.remaining(), 3);
}
