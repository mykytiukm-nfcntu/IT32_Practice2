#include <iostream>
#include <stdio.h>
#include <string.h>
//  Primitive message contrustor
//  CLI
//  1. Add message pieces
//  2. Undo
//  3. Show full message
//


// # messageasdsdasd
// undo
// show

#define wellcome_message "Wellcome! You can use this program as follow:\n" \
                "   type \"show\" to show current message\n" \
                "   type \"undo\" to undo\n" \
                "   start new message with # to add to current message (max 1024 chars)\n";

#define wrong_input_message "Wrong input!\n";

#define LINE_SIZE 1024

constexpr int grill_symbol = 35;

enum class MessageType {
    UNDO,
    SHOW,
    NEW_MESSAGE,
    INVALID
};

class InputValidator {
public:
    MessageType checkMessageType(const char *line) {
        if (strncmp(line,"undo", 4) == 0) {
            return MessageType::UNDO;
        }
        if (strncmp(line,"show", 4) == 0) {
            return MessageType::SHOW;
        }
        if (line[0] == grill_symbol) {
            return MessageType::NEW_MESSAGE;
        }
        return MessageType::INVALID;
    }
};


class Message {
public:
    int length;
    char *arr;

    Message() {
        arr = NULL;
        length = 0;
    }
    Message(const char* str) {
        int strLen = strlen(str);
        arr = new char[strLen + 1];

        strcpy(arr, str);
        length = strLen;
    }

    const char * getLine() {
        return arr;
    }

    ~Message() {
        // delete[] arr;
    }
};

// blablabla
// 66 71 65 66 71 65 66 71 65 66 71 65

// [{message, len}, {message, len},{message, len},{message, len},]
// count/line/size
class MessageArray {
private:
    void copySelf(Message *newMessages) {
        for (int i = 0; i < size; i++) {
            newMessages[i] = std::move(messages[i]);
        }
    }

public:
    Message *messages;
    int size;

    MessageArray() {
        messages = NULL;
        size = 0;
    }

    //
    // asdsad
    // asdsad asdsad
    // asdsad asdsad asdsad
    // asdsad asdsad
    void undoLastMessage() {
        if (size)
            size--;
        if (size == 0)
            delete[] messages;
    }

    void addMessage(Message message) {
        Message *newMessages = new Message[size + 1];
        copySelf(newMessages);
        delete[] messages;
        newMessages[size] = message;
        messages = newMessages;
        size++;
    }

    ~MessageArray() {
        delete[] messages;
    }
};

class MessagesPrinter {
public:
    int printMessages(MessageArray& messageArray) {
        int printedMessages = 0;
        for (int i = 0; i < messageArray.size; i++) {
            std::cout << messageArray.messages[i].arr;
            printedMessages++;
        }
        return printedMessages;
    }
};

int main() {
    std::cout << wellcome_message;
    char line[LINE_SIZE + 1];
    InputValidator validator = {};
    MessageArray messages = {};
    MessagesPrinter printer = {};

    while (true) {
        if (fgets(line, LINE_SIZE, stdin) == NULL) {
            std::cerr << "Failed to read input\n";
            return -1;
        };

        MessageType messageType = validator.checkMessageType(line);
        if (messageType == MessageType::INVALID) {
            std::cerr << wrong_input_message;
            std::cerr << std::endl;
            continue;
        }

        if (messageType == MessageType::NEW_MESSAGE) {
            Message newMessage {line + 1};
            messages.addMessage(std::move(newMessage));
        }

        if (messageType == MessageType::SHOW) {
            printer.printMessages(messages);
        }

        if (messageType == MessageType::UNDO) {
            messages.undoLastMessage();
        }

        std::cout << "Type one of the command below\n\n";
    }

    return 0;
}
