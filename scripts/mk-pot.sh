#Creates the .pot for the messages of the software.
xgettext --keyword=_ --language=C++ --add-comments --sort-output --copyright-holder="Matheus Gabriel Werny de Lima" --package-name=tools-cpp --msgid-bugs-address=matheusgwdl@protonmail.com -o ../po/messages.pot ../src/constants/Messages.cpp
