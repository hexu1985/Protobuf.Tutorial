#include <iostream>
#include <fstream>
#include <string>

#include "google/protobuf/util/json_util.h"

#include "addressbook.pb.h"

using namespace std;
using google::protobuf::util::JsonStringToMessage;

bool ReadFromJsonFile(const std::string &file_name,
        google::protobuf::Message *message) {
    std::fstream input(file_name, std::ios::in | std::ios::binary);
    if (!input) {
        std::cerr << "Failed to open file " << file_name << " in binary mode.\n";
        return false;
    }

    std::string json_string{std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
    auto status = JsonStringToMessage(json_string, message);
    if (!status.ok()) {
        std::cerr << "Cannot convert json to proto:" << json_string << "\n";
        return false;
    }

    return true;
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
    if (!ReadFromJsonFile(argv[1], &address_book)) {
        cerr << "Failed to parse address book." << endl;
        return -1;
    }

    ListPeople(address_book);

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}


