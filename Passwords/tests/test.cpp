#include <gtest/gtest.h>
#include "libpasswords.h"

TEST(PasswordTest, TestName){
    Password password("MatsueSS");
    EXPECT_EQ(password.getName(), "MatsueSS");
}

TEST(LibPasswordsTest, TestAdd_NAME){
    Password psw("MatsueSS");
    psw.generatePassword();
    LibPasswords lib;
    lib.addPassword(psw.getName(), psw);
    EXPECT_EQ(lib[0], psw.getName());
}

TEST(LibPasswordsTest, TestAdd_PASSWORD){
    Password psw("MatsueSS");
    psw.generatePassword();
    LibPasswords lib;
    lib.addPassword(psw.getName(), psw);
    EXPECT_EQ(lib.findPassword(lib[0]).getPassword(), psw.getPassword());
}