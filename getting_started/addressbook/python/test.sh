#!/bin/bash

cd `dirname ${BASH_SOURCE[0]}`
./create_addressbook.py test.pb
./list_people.py test.pb
