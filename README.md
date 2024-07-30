# remChar
Removes every instance of characters or complete string in a string from a string.

## USAGE
    remChar - remove a string or list characters from a string\n"
    **remChar _chars_to_be_removed_ | [-s string_to_be_removed] _string_ | [-f file] [-o file]\n"
    **-f file: file containing text to be modified\n"
    **-o file: output file\n"
    **-s string: string to be completely removed\n"

## EXAMPLES
    $ remChar l hello
      heo

**OR**

    $ remChar hl "hello world"
      eo word

**OR**

    $ remChar " " "hello world"
      helloworld

**OR**

    $ cat input.txt
      hello world
    $ remChar "h l" -f input.txt
      eoword

**OR**

    $ cat input.txt
      hello world
    $ remChar "h l" -f input.txt -o output.txt
    $ cat output.txt
      eoword

**OR**

    $ remChar -s "hello" "hello world"
       world

## BUILD
    $ mkdir build/
    $ cd build/
    $ cmake ..
    $ make # to build project locally
    $ sudo make install # to build and install the project
