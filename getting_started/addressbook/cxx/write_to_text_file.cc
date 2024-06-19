#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <string>

#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "google/protobuf/text_format.h"

#include "addressbook.pb.h"

using google::protobuf::TextFormat;
using google::protobuf::io::FileOutputStream;
using google::protobuf::io::ZeroCopyOutputStream;
using namespace std;

bool WriteToTextFile(const google::protobuf::Message &message, const std::string &file_name) {
    int fd = open(file_name.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    if (fd < 0) {
        std::cerr << "Unable to open file " << file_name << " to write.";
        return false;
    }
    ZeroCopyOutputStream *output = new FileOutputStream(fd);
    bool success = TextFormat::Print(message, output);
    delete output;
    close(fd);
    return success;
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
    if (!WriteToTextFile(*address_book, argv[1])) {
        cerr << "Failed to write address book." << endl;
        return -1;
    }

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}


