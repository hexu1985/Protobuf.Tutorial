#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"

using namespace std;

std::shared_ptr<tutorial::AddressBook> CreateAddressBook() {
    std::shared_ptr<tutorial::AddressBook> address_book(new tutorial::AddressBook);
    tutorial::Person* person = address_book->add_people();
    person->set_id(1234);
    person->set_name("John Doe");
    person->set_email("jdoe@example.com");

    tutorial::Person::PhoneNumber* phone_number = person->add_phones();
    phone_number->set_number("555-4321");
    phone_number->set_type(tutorial::Person::HOME);

    return address_book;
}

// Main function:  Reads the entire address book from a file,
//   adds one person based on user input, then writes it back out to the same
//   file.
int main(int argc, char* argv[]) {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2) {
        cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
        return -1;
    }

    auto address_book = CreateAddressBook();

    // Write the new address book back to disk.
    fstream output(argv[1], ios::out | ios::trunc | ios::binary);
    if (!address_book->SerializeToOstream(&output)) {
        cerr << "Failed to write address book." << endl;
        return -1;
    }

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}

