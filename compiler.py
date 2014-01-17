###############################################################################
## @package compiler
## @details This is the compiler module
##
## @author Jordan Ross
##
###############################################################################
import sys


###############################################################################
## @function compiler
##
## @details This is the main function for the compiler
###############################################################################
class Compiler:
    def __init__(self, fn):
        self.cur_line_count = 0
        self.filename = fn

    def main(self):
        print("Starting compilation of " + self.filename + "...")
        print("Done")


if __name__ == "__main__":
    if sys.argv[1] == "":
        print("You must provide a valid file name for the compiler")

    compiler = Compiler(sys.argv[1])
    compiler.main()