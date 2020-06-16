#Creates the .pot for the messages of the software.
xgettext --keyword=_ --language=C++ --add-comments --sort-output --copyright-holder="Matheus Gabriel Werny de Lima" --package-name=instagram-private-api --msgid-bugs-address=spixmaster528@gmail.com -o ../po/messages.pot ../src/constants/Messages.cpp
