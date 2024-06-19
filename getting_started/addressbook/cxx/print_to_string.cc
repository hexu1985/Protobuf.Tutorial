#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"

#include "google/protobuf/text_format.h"

using namespace std;

void PrintAddressBook(const tutorial::AddressBook& address_book) {
    std::string debugstr;
    google::protobuf::TextFormat::PrintToString(address_book, &debugstr); //转换到字符串TextFormat::PrintToString((*msg), &debugstr); //转换到字符串
    std::cout << "========================== address book begin ===============================\n";
    std::cout << debugstr << "\n";
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

    // Read the existing address book.
    fstream input(argv[1], ios::in | ios::binary);
    if (!address_book.ParseFromIstream(&input)) {
        cerr << "Failed to parse address book." << endl;
        return -1;
    }

    PrintAddressBook(address_book);

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}

