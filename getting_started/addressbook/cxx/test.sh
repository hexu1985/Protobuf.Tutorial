#!/bin/bash

cd `dirname ${BASH_SOURCE[0]}`
./create_addressbook test.txt
./list_people test.txt
