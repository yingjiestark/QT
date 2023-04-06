#include "arvapi.h"
#include <gtest/gtest.h>

TEST(arv_add,add_h_a){
    int res =arv_add(5,6);
    EXPECT_EQ(res, 11);
}
