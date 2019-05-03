#include "gtest/gtest.h"
#include "hashtable.h"

class hashtable : public testing::Test {

protected:
    virtual void TearDown(){

    }

    virtual void SetUp(){

    }

public:


};

TEST_F(hashtable, constructor){
    EXPECT_EQ("", "");

}
