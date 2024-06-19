#!/usr/bin/env python3

from generated import addressbook_pb2
import sys

def CreateAddressBook():
    address_book = addressbook_pb2.AddressBook()
    person = address_book.people.add()
    person.id = 1234
    person.name = "John Doe"
    person.email = "jdoe@example.com"

    phone = person.phones.add()
    phone.number = "555-4321"
    phone.type = addressbook_pb2.Person.HOME

    return address_book

# Main procedure:  Reads the entire address book from a file,
#   adds one person based on user input, then writes it back out to the same
#   file.
if len(sys.argv) != 2:
    print("Usage:", sys.argv[0], "ADDRESS_BOOK_FILE")
    sys.exit(-1)

address_book = CreateAddressBook()

# Write the new address book back to disk.
with open(sys.argv[1], "wb") as f:
    f.write(address_book.SerializeToString())
