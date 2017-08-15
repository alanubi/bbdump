# bbdump

*bbdump -- print human-readable colored hex dump*

### Contents of the package

`bbdump`
> The program that visualize its input in hexadecimal format.
> The visualization can look pretty nice!

`bbdump/ansicolor.h`
> The macro header for colorizing output using ANSI escape codes.
> Plain escape codes, low-level macros and high-level macros are provided.

`bbdump/switch.h` and `bbdump/label.h`
> The headers with tiny but very useful macros.
> With their help you can avoid `break` statements in `switch`,
> organize your loops in a different (and better) way
> and improve `goto`-filled error checking of initializations.

`bbdump/specifier.h`
> The header with portable function specifiers (INLINE and NORETURN).

---
### Installation

First of all, edit the file `Config` to fit your needs
(or set the variables from that file in a command line).
On a typical Linux machine you can keep it untouched.

Then build the program by running this command:

    $ make

Now you can check how the program works *(optional step)*:

    $ make show

You can adjust the defaults of your installation
by editing the file `defaults.h` and rebuilding the program.

You can also check the macro headers *(optional step)*:

    $ make demo
    $ build/syntax_a
    $ build/syntax_b
    $ build/ansicolor_a
    $ build/ansicolor_b

And finally, install the program and the macro headers
(you need superuser privileges):

    # make install

After the installation, type

    $ bbdump -h

for help, and try various options. Enjoy!

---
### Development

To remove the `build` directory, run this command:

    $ make clean

To package all the sources into a tarball, run this command:

    $ make dist
