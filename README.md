# Data_reading

Purpose 
The purpose of this assignment is for you to:

Improve your proficiency in C programming and your dexterity with dynamic memory allocation.

Demonstrate understanding of a concrete data structure (linked list). 

Practice multi-file programming and improve your proficiency in using UNIX utilities.


Background
A dictionary is an abstract data type that stores and supports lookup of key, value pairs. For example, in a telephone directory, the (string) key is a person or company name, and the value is the phone number. In a student record lookup, the key would be a student ID number and the value would be a complex structure containing all the other information about the student. 


Your Task
In this assignment, you will create a simple dictionary based on a linked list to store information from a dataset about the City of Melbourne. A user will be able to search this dictionary to retrieve information about footpaths in Melbourne using attributes in the dataset (keys). 

Your implementation will build the dictionary by reading the data from a file and inserting each footpath record as a node in a linked list. You will also implement a method to search for a key in the list, outputting any records that match the key. Note that keys are not guaranteed to be unique!


Dataset
The dataset comes from the City of Melbourne Open Data website, which provides a variety of data about Melbourne that you can explore and visualise online:

https://data.melbourne.vic.gov.au/

The dataset used in this project is a subset of the Footpath Steepness dataset combined with data from the Small Areas for Census of Land Use and Employment (CLUE) dataset. This dataset has been processed to simplify the geometric polygon data into additional attributes clue_sa, start lon, start lat, end lon, end lat, which can be used to approximate the footpath as a line on the map. 


The processed dataset can be found in the Dataset Download slide. You aren't expected to perform this processing yourself.

The provided dataset has the following 19 fields:

footpath_id  - The row number for this footpath in the original full dataset. (integer)
address      - A name describing the location of the footpath. (string)
clue_sa      - The CLUE small area the footpath is in. (string)
asset_type   - The name of the type of footpath. (string)
deltaz       - The change in vertical distance along the footpath. (double)
distance     - The length of the footpath (full geometry) in metres. (double)
grade1in     - The percentage gradient of the footpath (full geometry). (double)
mcc_id       - The id number identifying the footpath. (integer)
mccid_int    - A second number identifying the road or intersection the footpath borders. (integer)
rlmax        - The highest elevation on the footpath. (double)
rlmin        - The lowest elevation on the footpath. (double)
segside      - The side of the road which the footpath is on. (string)
statusid     - The status of the footpath. (integer)
streetid     - The ID of the first street in the Address. (integer)
street_group - The footpath_id of one of the footpaths connected to this footpath without a gap. (integer)
start_lat    - The latitude (y) of the starting point representing the line approximation of the footpath. (double)
start_lon    - The longitude (x) of the starting point representing the line approximation of the footpath. (double)
end_lat      - The latitude (y) of the ending point representing the line approximation of the footpath. (double)
end_lon      - The longitude (x) of the starting point representing the line approximation of the footpath. (double)


The fields address, clue_sa, asset_type and segside are strings, and may be zero-length and could contain spaces. You may assume none of these fields are more than 128 characters long. The fields footpath_id , mcc_id, mccid_int, statusid, streetid and street_group are integers, you may assume they are always specified and present, even though a value of 0 signifies the information is not present or not applicable. 

This data is in CSV format, with each field separated by a comma. For the purposes of the assignment, you may assume that:

the input data are well-formatted,

input files are not empty,

input files include a header,

fields always occur in the order given above, and that

the maximum length of an input record (a single full line of the CSV) is 512 characters.

Where a string contains a comma, the usual CSV convention will be followed that such strings will be delimited with a quotation mark (always found at the beginning and end of the field) — these quotes should not be preserved once the data is read into its field. You may assume no quotes are present in the processed strings when they are stored in your dictionary.

Smaller samples of these datasets can be found in the Dataset Download slide.


Implementation Details
Stage 1 - Data Retrieval
In Stage 1, you will implement the basic functionality for a dictionary allowing the lookup of data by key (address).

Your Makefile should produce an executable program called dict1. This program should take three command line arguments: 

The first argument will be the stage, for this part, the value will always be 1.

The second argument will be the filename of the data file. 

The third argument will be the filename of the output file.

Your dict1 program should:

Read the data from the data file specified in the second command line argument. The data from the CSV should be stored in a linked list of pointers to structs for the data. Datatypes for each field should be consistent with those in the Dataset slide. Each record (row) should be stored in a separate node.

Accept addresses from stdin, search the list for all matching records and print them to the output file. You may assume that all queries will be terminated by a new line to allow for the querying of footpaths without an address. If no matches for the query are found, your program should output NOTFOUND.

In addition to outputting the record(s) to the output file, the number of records found should be output to stdout.

For testing, it may be convenient to create a file of keys to be searched, one per line, and redirect the input from this file. Use the UNIX operator < to redirect input from a file.


Stage 2 - Building an Index for Approximate Lookup
In Stage 2, you will implement a simple calculated index on the dataset (address).

An index allows for faster access to particular attributes in a database, in this stage you will construct an index on a single attribute and search on that attribute. Though you should assume a different attribute could be used to build the index, you will only need to build an index for a single attribute.

Your Makefile should now also produce an executable program called dict2. This program should take three command line arguments: 

The first argument will be the stage, for this part, the value will always be 2.

The second argument will be the filename of the data file. 

The third argument will be the filename of the output file.

Your dict2 program should:

Just as in Stage 1, read the data from the data file specified in the second command line argument. The data from the CSV should be stored in a linked list of pointers to structs for the data. Datatypes for each field should be consistent with those in the Dataset slide. Each record (row) should be stored in a separate node.

For Stage 2, you should also construct a sorted array which contains pointers to each node in the dataset. This should be sorted on the grade1in attribute, which will be the 6th index (0-based).

For Stage 2, you should accept double type values from stdin, search the index for the closest record to that value and print it to the output file. You may assume that no blank lines will be present in the queries. The closest point is defined by the absolute difference between the search value and the dataset value. In testing, you will only receive queries with a single closest record, if multiple closest matches for the query are found in the dataset, your program may select any or all matching records, you are free to attempt this as a challenge if you like.

In addition to outputting the record(s) to the output file, the grade1in value of the record found should be output to stdout.


Stage 2 Output Notes
You should use the input key given by the user in both the output file and stdout outputs exactly as entered e.g. If the input 20.4900 is given, the output should also read 20.4900.

For double type numerical outputs which come from the database, you may either round or print them with the full precision as stored in your database. If you choose to round values, this rounding should be sensible — distances and gradients may be naturally noisy values with low precision of one or two decimal places, but latitudes and longitudes should attempt to retain as much precision as possible, even if some loss of accuracy occurs during the translation to the double data type.

Your approach should be space efficient but does not need to be time efficient.


Requirements
The following implementation requirements must be adhered to:

You must write your implementation in the C programming language.

You must write your code in a modular way, so that your implementation could be used in another program without extensive rewriting or copying. This means that the dictionary operations are kept together in a separate .c file, with its own header (.h) file, separate from the main program, and other distinct modules are similarly separated into their own sections, requiring as little knowledge of the internal details of each other as possible.

Your code should be easily extensible to multiple dictionaries. This means that the functions for interacting with your dictionary should take as arguments not only the values required to perform the operation required, but also a pointer to a particular dictionary, e.g. search(dictionary, value).

Your implementation must read the input file once only.

Your program should store strings in a space-efficient manner. If you are using malloc() to create the space for a string, remember to allow space for the final end of string character, ‘\0’ (NULL).

Your program should store its data in a space-efficient manner. If you construct an index, this index should not contain information it does not need.

Your stage 2 index should allow time-efficient lookup.

For stage 2, you may assume the index only needs to be built after all records are inserted.

A full Makefile is not provided for you. The Makefile should direct the compilation of your program. To use the Makefile, make sure it is in the same directory as your code, and type make dict1 and make dict2 to make the dictionary. You must submit your Makefile with your assignment.



