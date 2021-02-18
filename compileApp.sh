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
  gcc --std=gnu99 -o $executableFilename $mainFilename ${preCompilePackage}.a
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
  #  e -> run executable
  #  v -> run executable with valgrind leak analysis
  #  t -> run executable with testscript to stdout
  #  r -> run executable with testscript and send results to a report file
  #  c -> performs only cleaning of compilation files and creted test files
  while getopts "evtrc" flag; do
    case $flag in
    e) ./$executableFilename <./testfiles/input2.txt ;;
    v) valgrind ./$executableFilename ;;
    t) ./$executableFilename <./testfiles/input1.txt >testfile.txt ;;
    r) ;;
    c) ;;
    esac
    shift
  done
}

# Execute this script passing params to main
main "$@"
