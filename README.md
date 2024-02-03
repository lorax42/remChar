# remChar
Removes every instance of a character in a string from a string.

## USAGE
    remChar <string> [<string>|-f <file>] (-o <file>)

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

## BUILD
    $ mkdir src/build/
    $ cd src/build/
    $ cmake -S ..
    $ make # to build project locally
    $ sudo make install # to build and install the project
