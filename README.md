# unargs

This is a single-header library for parsing `argv`, written in C.

I mainly created it for my own needs. It does NOT attempt to follow Unix or any other convention, hence the name (<u>un</u>conventional <u>arg</u>ument<u>s</u>).

<u>**Please do not send any pull requests to this repository.**</u>

## Syntax

Options are passed as `-name value`.

Bool options are an exception - they are passed with just `-name` which will store `true` at the destination. Otherwise, the default value of `false` is stored.

Positional arguments are passed with just the value.

For example:

`main -opt1 1 -opt2 2 dir/dst.txt dir/src.txt -opt3`

Here, `opt1` is set to 1, `opt2` to 2, and `opt3` to `true`. The first positional argument was provided as the string `dir/dst.txt`, the second as `dir/src.txt`. Any other arguments will be set to their default values.

The ordering of positional arguments compared to each other DOES matter. Otherwise, arguments can be provided in any order.

## API

Parameters can be required or non-required (in which case they have a default value). Parameters can be options or positionals. The API accepts pointers to destinations where to store the parsed values.

`unargs_Param` stores information about parameters and is created by calling the functions `unargs_int` or `unargs_intReq` (or some other type).

`unargs_parse` takes in `argc`, `argv`, and an array of `unargs_Param`s. It verifies both the arguments and the parameters, parses `argv`, and stores parsed or default values into destinations. In case of errors, it returns a non-zero value.

Example usage:

```
    unargs_Param params[] = {
        // required int option '-opt1'
        unargs_intReq("opt1", "Description of opt1.", &opt1),

        // non-required option '-opt2', default value is -1
        unargs_int("opt2", "Description of opt2.", -1, &opt2),

        // required string positional
        unargs_stringReq(NULL, "Output file path.", &dst),

        // another required string positional
        unargs_stringReq(NULL, "Input file path.", &src),

        // non-required int positional, default value is 8080
        unargs_int(NULL, "Port.", 8080, &port),

        // bool option (always non-required with default of false)
        unargs_bool("opt3", "Description of opt3.", &opt3),
    };
    unargs_parse(argc, argv, sizeof(params) / sizeof(*params), params);
```

`unargs_help` prints a message on how to call the program with your specified argument interface.

## How to Use

This is a single-header library. The header file is `unargs.h`, simply copy it somewhere within your project directory and include it in ONE translation unit with:

```
    #define UNARGS_IMPLEMENTATION
    #include "unargs.h"
```

You can include it in other translation units by omitting `#define UNARGS_IMPLEMENTATION`.

The library should compile on C99, C++98, or any newer standard.

You can run `make` from this project's directory to run various tests to make sure the library works correctly.
