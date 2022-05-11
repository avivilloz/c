Url Reader:

The main files in the program are part of url_reader directory.
I tried to create a generic class that will handle many types of reading from urls.
You can configure the project in the "config.txt" file.
The urls data will be loaded to the "_urls_data" directory.
The urls being used for test are in the "sample_url.txt" file.

1-In order to compile, just type "make" in the main directory ("./radview_project").
2-In order to run: 
    a-you can add the file to be read and the directory to store data
        in the makefile variable "ARGS", and just type "make run".
    b-or you can manually run it with the file, 
        ex: "_bin/test.out sample_urls.txt _urls_data/".

Modules included:

-url_reader -> Main module
-url_shortener -> To get specific names for the files created in order to store the urls' data. 
The "urls_storage.txt" file holds urls already requested.
-runtime_config -> Used to load parameters at runtime.
-singleton -> Most modules are singleton.