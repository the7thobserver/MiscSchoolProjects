# Jared Leung
# UC Irvine
# 1/21/2014

# How to run
# Have python installed v3.3.3
# To check in the python shell type "import sys" and "sys.version_info"
# Output should be sys.version_info(major=3, minor=3, micro=3, releaselevel='final', serial=0)

# Running the program
# Go to where your python interrpreter is installed
# Type "python "Lab 1 Pt 2.py" [Test File Name]"
# Test File Name can be multiple test files separated by a space
# IE 
# python "Lab 1 Pt 2.py" test1.txt test2.txt
# Note python script and test files must be also in that directory

# Note
# Test files should have each date on it's own line
# IE
# 1/1/2014
# 1/2/2014

import re
import datetime
import sys
import os

# Determines if the date numbers are correct
def isValidDate(date, delimiter):
    # Split date by the delimiter
    if delimiter == 0 or delimiter == 1:
        dateList = date.split('/')
        year = int(dateList[2])
        month = int(dateList[0])
        day = int(dateList[1])
    elif delimiter == 2:
        dateList = date.split('-')
        year = int(dateList[2])
        month = int(dateList[0])
        day = int(dateList[1])        
    elif delimiter == 3 or delimiter == 4:
        dateList = date.split('.')
        year = int(dateList[2])
        month = int(dateList[1])
        day = int(dateList[0])        
    elif delimiter == 5:
        dateList = date.split('-')
        year = int(dateList[0])
        month = int(dateList[1])
        day = int(dateList[2])                
    else:
        print("No delimiter found")
        return "ERROR"
    
    try:
        date = datetime.date(year, month, day)
        print("True - is valid date")
    except ValueError:
        print("Invalid Date")
        return "False - is not valid date"
    
    return

# Determine if format is correct
def regexSearch(date):
    # Define regex list of acceptable date formats
    regexList = [re.compile('^\d{1,2}\/\d{1,2}\/\d{4}$'),                        # First case 1/10/2010
                 re.compile("^([1-9]|1[0-2])?\/([1-9]|[1-3][0-9])?\/\d{2}$"),    # 10/10/20
                 re.compile("^([0-9]|[0-1][0-2])?\-[1-3][0-9]\-\d{4}$"),         # 12/10/2000
                 re.compile("^\d{1,2}\.\d{1,2}\.\d{4}$"),                        # Dashes
                 re.compile("^\d{1,2}\.\s\d{1,2}\.\s\d{4}$"),                    # Spaces
                 re.compile("^\d{4}\-\d{2}\-\d{2}$")]                            # Dashes Rest of the World Format

    found = 0;
    
    # Search for through regex list
    for regex in regexList:
        result = re.match(regex, date)
        if result:
            found = 1
            delimiter = regexList.index(regex)

    # Regex found, onwards to date validity else it's not a valid date
    if found:
        isValidDate(date, delimiter)
    else:    
        print("False - is not valid date")
    
    return
          

# Main ====================================================================================================================
# NOTE: First arg is always the file path
print( 'Argument List:', str(sys.argv))
print( 'Args Length:', len(sys.argv))
print("testdate.py by Jared Leung\n")

if len(sys.argv) == 1:
    print('No files were inputed. Add test file name after python script name. Read source code for detailed instructions.');

# Loop over all the input files
for argIndex in range(1, len(sys.argv)):
    print("\nFile# ", argIndex)
    
    # Try to open the file
    try:
        file = open(sys.argv[argIndex], 'r')
    except FileNotFoundError:
        print(sys. argv[argIndex] + " is an invalid file")
        
    # Check if file is empty
    if (os.stat(sys.argv[argIndex]).st_size == 0):
        print('File is empty!')

    # Save the position of the file pointer in the text
    beginning = file.tell()
    # Scan all the text to see if it contains any numbers- pointer at the end of the file
    searchResults = re.findall("\d+", file.read())
    # Check if file has any numbers
    if searchResults == []:
        print(sys.argv[argIndex] + ": does not contain dates")
        continue
    # Return pointer to the beginning of the file
    file.seek(beginning)
    
    # Look at the contents of the file - parse for correct date format
    if(file):
        for line in file:
            # Remove new line character
            line = line.rstrip('\n')
            
            print("\n\"" + line + "\"")
         
            # Seach with regexes
            regexSearch(line)

        file.close();
    else:
        print(sys.argv[argIndex] + ": does not contain dates")
         
# End of Program