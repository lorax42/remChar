# remChar
Removes every instance of a character or complete string in a string from a string.

## USAGE
    **remChar** _string_ [**-s** _string_] _string_ | [**-f** _file_] [**-o** _file_]\
    **-f** _file_:   file containing text to be modified\
    **-o** _file_:   output file\
    **-s** _string_: string to be completely removed

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

    $ remChar "h l" -f input.txt
      eoword
    $ cat input.txt
      hello world

**OR**

    $ remChar "h l" -f input.txt -o output.txt
    $ cat input.txt
      hello world
    $ cat output.txt
      eoword

**OR**

    $ remChar -s "hello" "hello world"
       world

## BUILD
    $ mkdir src/build/
    $ cd src/build/
    $ cmake -S ..
    $ make # to build project locally
    $ sudo make install # to build and install the project
