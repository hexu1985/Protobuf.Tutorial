#include <iostream>
#include <fstream>
#include <string>

#include "google/protobuf/util/json_util.h"

#include "addressbook.pb.h"

using namespace std;
using google::protobuf::util::MessageToJsonString;

bool WriteToJsonFile(const google::protobuf::Message &message, const std::string &file_name) {
    google::protobuf::util::JsonPrintOptions options;

    std::string json_string;
    auto status = MessageToJsonString(message, &json_string, options);
    if (!status.ok()) {
        std::cerr << "Cannot convert proto to json:" << message.DebugString() << "\n";
        return false;
    }

    std::ofstream output(file_name, std::ofstream::out | std::ofstream::trunc);
    if (!output) {
        std::cerr << "open file: " << file_name << " for write failed!\n";
        return false;
    }
    output << json_string;

    return true;
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
    if (!WriteToJsonFile(*address_book, argv[1])) {
        cerr << "Failed to write address book." << endl;
        return -1;
    }

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}




