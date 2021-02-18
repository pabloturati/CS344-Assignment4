#! /bin/bash

# Directory list
inputTestFilesFolder="./testFiles/testInputFiles"
outputTestFilesFolder="./testFiles/testOutputFiles"
temporaryOutputFolderName="./testFiles/temporaryGeneratedTestFiles"

# Path and name of binary file to execute
binaryExecutableFile="./line_processor"

# Test filenames
testFile1Label="testFile1"
testFile2Label="testFile2"
testFile3Label="testFile3"

# Output filenames
outputFile1Label="output1"
outputFile2Label="output2"
outputFile3Label="output3"

# Input filenames
inputFile1Label="input1"
inputFile2Label="input2"
inputFile3Label="input3"

# Input file paths
inputFile1="${inputTestFilesFolder}/${inputFile1Label}.txt"
inputFile2="${inputTestFilesFolder}/${inputFile2Label}.txt"
inputFile3="${inputTestFilesFolder}/${inputFile3Label}.txt"

# Output file paths
outputFile1="${outputTestFilesFolder}/${outputFile1Label}.txt"
outputFile2="${outputTestFilesFolder}/${outputFile2Label}.txt"
outputFile3="${outputTestFilesFolder}/${outputFile3Label}.txt"

# Test file paths
testFile1="./${temporaryOutputFolderName}/${testFile1Label}.txt"
testFile2="./${temporaryOutputFolderName}/${testFile2Label}.txt"
testFile3="./${temporaryOutputFolderName}/${testFile3Label}.txt"

# runtest(). Function to compare output file with expected output file
# Params list
# 1 - inputFileX
# 2 - testFileX
# 3 - testFileXLabel
# 4 - outputFileX
# 5 - outputFileXLabel
# 6 - inputFileXLabel
function runTest() {
  echo "Testing $6"
  # Run test 1
  rm -rf $2
  eval "${binaryExecutableFile} < $1 > $2"

  if cmp -s $4 $2; then
    printf "PASS.  $3 is identical to $5 \n"
  else
    printf "FAIL The files do not match\n"
  fi
}

function main() {
  printf "\n*****  Running Test script  *****\n\n"
  # Create test generated files folder
  mkdir -p $temporaryOutputFolderName

  # Testing
  runTest $inputFile1 $testFile1 $testFile1Label $outputFile1 $outputFile1Label $inputFile1Label
  runTest $inputFile2 $testFile2 $testFile2Label $outputFile2 $outputFile2Label $inputFile2Label
  runTest $inputFile3 $testFile3 $testFile3Label $outputFile3 $outputFile3Label $inputFile3Label

  # Cleaning up testfiles
  rm -rf $temporaryOutputFolderName

  printf "\n*****  Finished testing script  *****\n\n"
}

main "$@"
