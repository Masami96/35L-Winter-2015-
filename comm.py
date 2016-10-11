#!/usr/bin/python

import random, sys
from optparse import OptionParser

# create a class that will convert input text into arrays
class comm:
    def __init__(self, filename):
        f = open (filename, 'r')
        self.lines = f.readlines()
        f.close ()    
    def getLines(self):
        return self.lines
    
# main function that outputs the version and usage        
def main():
    version_msg="%prog 2.0"
    usage_msg="""#prog [OPTION]...Compare FILE with FILE  and output the unique strings."""
    
# add options to the function
    parser = OptionParser(version=version_msg, usage=usage_msg)

    parser.add_option("-1", action="store_true", dest="option1", default=0, help="remove column 1 (lines unique to FILE1)")

    parser.add_option("-2", action="store_true", dest="option2", default=0, help="remove column 2 (lines unique to FILE2)")

    parser.add_option("-3", action="store_true", dest="option3", default=0, help="remove column 3 (lines that appear in both files)")

    parser.add_option("-u", action="store_true", dest="sortem", default=0, help="compare input files even when they are not sorted")

# Initialize files and check for appropriate arguments
    options, args = parser.parse_args(sys.argv[1:])

    if len(args) != 2:
        sys.stdout.write("input requires 2 files")
    inputfile1=args[0]
    inputfile2=args[1]
    file1=comm(inputfile1)
    file2=comm(inputfile2)
    list1=file1.getLines()
    list2=file2.getLines()

# remove unnecessary whitespace so output does not have multiple newlines
    for i in range(len(list1)):
        list1[i].strip()
    for j in range(len(list2)):
        list2[j].strip()

#set lengths of the lists
    l1=len(list1)
    l2=len(list2)
    oneisLonger=False
    if(l1 < l2):
        minLines=l1
        maxLines=l2
    else:
        minLines=l2
        maxLines=l1
        oneisLonger=True

#sort the files if the -u option is true
    if(options.sortem == True):
        list1.sort()
        list2.sort()
        
#loop through the files and compare each line, outputting the lines (if needed)
    i=0
    outputLine=""
    while i < minLines:
        if(list1[i] == list2[i]):
            outputLine="                "
            outputLine+=list1[i]
            if(options.option3 == False):
                sys.stdout.write(outputLine)
            outputLine=""
        else:
            if(options.option1 == False):
                sys.stdout.write(list1[i])
            outputLine="        "
            outputLine+=list2[i]
            if(options.option2 == False):
                sys.stdout.write(outputLine)
            outputLine=""
        i+=1
    if(oneisLonger == True):
        while i < maxLines:
            if(options.option1 == False):
                sys.stdout.write(list1[i])
            i+=1    
    else:
        while i < maxLines:
            if(options.option2 == False):
                outputLine="        "
                outputLine+=list2[i]
                sys.stdout.write(outputLine)
                outputLine=""
            i+=1    
        
if __name__ == "__main__":
        main()
