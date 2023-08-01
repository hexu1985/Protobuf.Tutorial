#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"

#include "google/protobuf/util/json_util.h"

using namespace std;

void PrintAddressBook(const tutorial::AddressBook& address_book) {
    google::protobuf::util::JsonPrintOptions options;
#if 1
    options.add_whitespace = true;
    options.always_print_primitive_fields = true;
#endif

    std::string json_string;
    auto status = google::protobuf::util::MessageToJsonString(address_book, &json_string, options);
    if (!status.ok()) {
        std::cout << "Cannot convert proto to json:" << address_book.DebugString();
        return;
    }
    std::cout << "========================== address book begin ===============================\n";
    std::cout << json_string << "\n";
    std::cout << "========================== address book end ===============================\n";
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

    {
        // Read the existing address book.
        fstream input(argv[1], ios::in | ios::binary);
        if (!address_book.ParseFromIstream(&input)) {
            cerr << "Failed to parse address book." << endl;
            return -1;
        }
    }

    PrintAddressBook(address_book);

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}

