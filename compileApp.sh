#! /bin/bash

# Build data
preCompilePackage="component_archive"
executableFilename="line_processor"
mainFilename="main.c"
testOutputFiles="
  *.o 
  *.a 
  testfile.txt
  "

# Components
declare -a componentList=(
  "constants"
  "dataProcessingMethods"
  "bufferHandlers"
  "threadHandlerMethods"
)

# Cleans previously compiled files and created folders
function preCompileClean() {
  rm -rf $executableFilename *.o *.a $testOutputFiles
}

# Cleans space of temporary compile files
function postCompileClean() {
  rm -f *.o *.a
}

function generatePrecompiledObject() {
  gcc --std=gnu99 -c ${1}/${1}.c
}

function generateModuleObjectsAndArchive() {
  # Stores object list
  precompileObjectList=""

  # Create precompiled objects and list
  for component in ${componentList[@]}; do
    precompileObjectList+=" ${component}.o"
    generatePrecompiledObject $component
  done

  # Creates archive with objects
  ar -r ${preCompilePackage}.a $precompileObjectList 2>/dev/null
}

# Compiles main
function compileMainAndArchive() {
  gcc --std=gnu99 -pthread -o $executableFilename $mainFilename ${preCompilePackage}.a
}

function main() {
  # Pre cleaning, removes leftovers from previous runs
  preCompileClean

  # Compilation step
  generateModuleObjectsAndArchive
  compileMainAndArchive

  # Post cleaning to eliminate temporary files
  postCompileClean

  # Handles parameters to execute.
  # Param triggers:
  #  e -> run executable getting standard in from input1 testfile
  #  v -> run executable with valgrind leak analysis
  #  t -> run executable and then run test script
  #  m -> run executable to take input from stdin and output from stdout
  while getopts "metv" flag; do
    case $flag in
    m) ./$executableFilename ;;
    e) ./$executableFilename <./testFiles/testInputFiles/input1.txt ;;
    t) ./testScript.sh ;;
    v) valgrind ./$executableFilename ;;
    esac
    shift
  done
}

# Execute this script passing params to main
main "$@"
