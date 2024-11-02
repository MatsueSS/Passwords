#include <gtest/gtest.h>
#include "libpasswords.h"
#include "passwordfilemanager.h"
#include "libpasswordsfilemanager.h"
#include "errorvalues.h"

TEST(PasswordTest, TestName){
    Password password("MatsueSS");
    EXPECT_EQ(password.getName(), "MatsueSS");
}

TEST(PasswordTest, TestRead){
    Password password("");
    password.read("../resources/file.txt");
    EXPECT_NE(password.getName(), "");
    EXPECT_NE(password.getPassword(), "");
}

TEST(PasswordTest, TestWrite){
    Password password("MatsueSS"), checkpsw("");
    password.generatePassword();
    password.write("../resources/file.txt");
    checkpsw.read("../resources/file.txt");
    EXPECT_EQ(password.getName(), checkpsw.getName());
    EXPECT_EQ(password.getPassword(), checkpsw.getPassword());
}

TEST(PasswordManagerTestException, TestReadException){
    Password password("MatsueSS");
    PasswordFileManager file(&password);
    EXPECT_THROW(file.read("../resources/exampleError.txt"), ErrorValues);
}

TEST(PasswordManagerTest, TestRead){
    Password password("MatsueSS");
    PasswordFileManager file(&password);
    EXPECT_NO_THROW(file.read("../resources/file.txt"));
}

TEST(PasswordManagerTest, TestWrite){
    Password password("MatsueSS");
    password.generatePassword();
    PasswordFileManager file(&password);
    EXPECT_NO_THROW(file.write("../resources/file.txt"));
}

TEST(LibPasswordsManagerTest, TestReadException){
    LibPasswords lib;
    LibPasswordsFileManager file(&lib);
    EXPECT_THROW(file.read("../resources/exampleError.txt"), ErrorValues);
}

TEST(LibPasswordsManagerTest, TestRead){
    LibPasswords lib;
    LibPasswordsFileManager file(&lib);
    EXPECT_NO_THROW(file.read("../resources/testlib.txt"));
}

TEST(LibPasswordsManagerTest, TestWrite){
    Password psw("Matsue");
    psw.generatePassword();
    LibPasswords lib;
    lib.addPassword(psw.getName(), psw);
    LibPasswordsFileManager file(&lib);
    EXPECT_NO_THROW(file.write("../resources/testlib.txt"));
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

TEST(LibPasswordsTest, TestRead_FILE){
    LibPasswords lib;
    lib.read("../resources");
    for(int i = 0; i < lib.sizeLib(); i++){
        EXPECT_NE(lib[i], "");
        EXPECT_NE(lib.findPassword(lib[i]).getPassword(), "");
    }    
}

TEST(LibPasswordsTest, TestWrite_FILE){
    Password p1("MSS1"), p2("MSS2"), p3("MSS3");
    p1.generatePassword();
    p2.generatePassword();
    p3.generatePassword();
    LibPasswords lib, lib2;
    lib.addPassword(p1.getName(), p1);
    lib.addPassword(p2.getName(), p2);
    lib.addPassword(p3.getName(), p3);
    lib.write("../resources/testlib.txt");
    lib2.read("../resources/testlib.txt");
    for(int i = 0; i < lib.sizeLib(); i++){
        EXPECT_EQ(lib[i], lib2[i]);
        EXPECT_EQ(lib.findPassword(lib[i]).getPassword(), lib2.findPassword(lib2[i]).getPassword());
    }
}