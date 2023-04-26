#!/bin/bash

cd `dirname ${BASH_SOURCE[0]}`
./create_addressbook.py test.txt
./list_people.py test.txt
