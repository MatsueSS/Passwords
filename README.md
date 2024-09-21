ManagerPasswordsEncrypted

I want to share my application, which I decided to create to improve my life and work with third-party resources, where it is important to have your own account.
My application generates a password from a set of characters (specified by the user, can be used by default) and any length (also specified by the user, but can be used by default).
This program provides for the handling of exceptions that occur when working with files.
My code is well structured in my opinion, which makes it easy to use.
I also want to add that when encrypting messages in the class Encrypt, an algorithm is written that does not go beyond the ASCII table when saving and reading. That is, all characters from 33 to 126 are read. Therefore, going beyond this is impossible.
The program is a very convenient solution for storing passwords, because I consider this method non-trivial.
