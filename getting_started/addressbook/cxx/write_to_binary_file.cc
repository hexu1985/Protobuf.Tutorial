#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>

#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "google/protobuf/text_format.h"

#include "addressbook.pb.h"

using namespace std;

bool WriteToBinaryFile(const google::protobuf::Message &message, const std::string &file_name) {
    std::fstream output(file_name,
            std::ios::out | std::ios::trunc | std::ios::binary);
    if (!output) {
        std::cerr << "Unable to open file " << file_name << " to write.\n";
        return false;
    }
    return message.SerializeToOstream(&output);
}

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
    if (!WriteToBinaryFile(*address_book, argv[1])) {
        cerr << "Failed to write address book." << endl;
        return -1;
    }

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}



