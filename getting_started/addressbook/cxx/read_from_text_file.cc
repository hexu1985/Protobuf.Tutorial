#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <string>

#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "google/protobuf/text_format.h"

#include "addressbook.pb.h"

using google::protobuf::TextFormat;
using google::protobuf::io::FileInputStream;
using google::protobuf::io::ZeroCopyInputStream;
using namespace std;

bool ReadFromTextFile(const std::string &file_name,
        google::protobuf::Message *message) {
    int fd = open(file_name.c_str(), O_RDONLY);
    if (fd < 0) {
        std::cerr << "Failed to open file " << file_name << " in text mode.\n";
        // Failed to open;
        return false;
    }

    ZeroCopyInputStream *input = new FileInputStream(fd);
    bool success = TextFormat::Parse(input, message);
    if (!success) {
        std::cerr << "Failed to parse file " << file_name << " as text proto.\n";
    }
    delete input;
    close(fd);
    return success;
}

void ListPeople(const tutorial::AddressBook& address_book) {
    for (int i = 0; i < address_book.people_size(); i++) {
        const tutorial::Person& person = address_book.people(i);

        cout << "Person ID: " << person.id() << endl;
        cout << "  Name: " << person.name() << endl;
        if (person.has_email()) {
            cout << "  E-mail address: " << person.email() << endl;
        }

        for (int j = 0; j < person.phones_size(); j++) {
            const tutorial::Person::PhoneNumber& phone_number = person.phones(j);

            switch (phone_number.type()) {
                case tutorial::Person::MOBILE:
                    cout << "  Mobile phone #: ";
                    break;
                case tutorial::Person::HOME:
                    cout << "  Home phone #: ";
                    break;
                case tutorial::Person::WORK:
                    cout << "  Work phone #: ";
                    break;
            }
            cout << phone_number.number() << endl;
        }
    }
}

// Main function:  Reads the entire address book from a file and prints all
//   the information inside.
int main(int argc, char* argv[]) {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2) {
        cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
        return -1;
    }

    tutorial::AddressBook address_book;
    if (!ReadFromTextFile(argv[1], &address_book)) {
        cerr << "Failed to parse address book." << endl;
        return -1;
    }

    ListPeople(address_book);

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}

