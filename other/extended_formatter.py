from string import Formatter


class ExtendedFormatter(Formatter):
    """An extended format string formatter

    Formatter with extended conversion symbol to make the entire
    variable upper- or lowercase.

    Usage:
        ul_formatter.format("normal:{test}, upcase:{test!u}, lowcase:{test!l}")

        !u will make the variable `test` uppercase.
        !l will make the variable `test` lowercase. 

    (ul_formatter = ExtendedFormatter() needs to be called) 


    Code copied from Tradjincal's answer on StackOverflow:
    https://stackoverflow.com/a/46160537/3723378
    """
    def convert_field(self, value, conversion):
        """ Extend conversion symbol
        Following additional symbol has been added
        * l: convert to string and low case
        * u: convert to string and up case

        default are:
        * s: convert with str()
        * r: convert with repr()
        * a: convert with ascii()
        """

        if conversion == "u":
            return str(value).upper()
        elif conversion == "l":
            return str(value).lower()
        # Do the default conversion or raise error if no matching conversion found
        super(ExtendedFormatter, self).convert_field(value, conversion)

        # return for None case
        return value


ul_formatter = ExtendedFormatter()


if __name__ == '__main__':
    # example code on how to use
    template_str = "normal:{test}, upcase:{test!u}, lowcase:{test!l}"

    output = ul_formatter.format(template_str, test="DiDaDoDu")
    print(output)
