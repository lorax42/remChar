# remChar
Removes every instance of a given character from a given string.

## USAGE
    remChar <charcter to be removed> <stringToRemoveCharacterFrom|"string to remove character from">

## EXAMPLES
    $ remChar l hello
      heo

**OR**

    $ remChar l "hello world"
      heo word

**OR**

    $ remChar " " "hello world"
      helloworld

## BUILD
    $ mkdir src/build/
    $ cd src/build/
    $ cmake -S ..
    $ make # to build project locally OR
    $ sudo make install # to build and install the project
