# bbdump

*bbdump -- print human-readable colored hex dump*

### Contents of the package

`bbdump`
> The program that visualizes its input in hexadecimal format.
> The visualization can look pretty nice!

---
### System requirements

Make sure you have installed `bbmacro` library of version `0.5`.
It would be good if your system supports ANSI escape codes.

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
by editing the file `src/defaults.h` and building the program again.

And finally, install the program
(you need the superuser privileges):

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
