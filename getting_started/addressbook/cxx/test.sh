#!/bin/bash

cd `dirname ${BASH_SOURCE[0]}`
./create_addressbook test.pb
./list_people test.pb
