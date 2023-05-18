# #!/bin/bash

# # Build the minishell program using the Makefile
# make

# # Specify the filename for the input tests
# test_file="tests.txt"

# # Check if the test file exists
# if [ ! -f "$test_file" ]; then
#   echo "Error: Test file '$test_file' not found."
#   exit 1
# fi

# # Read each line from the test file and execute it with the minishell program
# while IFS= read -r test_case; do
#   echo "Test Case: $test_case"
#   echo "========================"
  
#   # Run the minishell program with the test case as input
#   output=$(./minishell)

  
#   # Parse the output to obtain the number of times the string is split
#   num_splits=$(grep -o "Number of splits: [0-9]\+" <<< "$output" | awk '{print $NF}')
  
#   # Check if the number of splits is found in the output
#   if [[ -n $num_splits ]]; then
#     echo "Number of splits: $num_splits"
#   else
#     echo "Error: Number of splits not found in output."
#   fi
  
#   echo "========================"
#   echo
# done < "$test_file"

# # Clean up the compiled files using the Makefile
# make clean


#!/bin/bash


function usleep() {
  local duration_us=$1
  local start_time
  local end_time

  # Get the current timestamp in microseconds
  start_time=$(date +%s%N)

  # Calculate the end timestamp based on the duration
  end_time=$((start_time + duration_us))

  # Loop until the current timestamp exceeds the end timestamp
  while true; do
    # Get the current timestamp in microseconds
    current_time=$(date +%s%N)

    # Break the loop if the current timestamp exceeds the end timestamp
    if [ "$current_time" -ge "$end_time" ]; then
      break
    fi
  done
}
# Build the minishell program using the Makefile
make

# Specify the filename for the input tests
test_file="tests.txt"

# Read each line from the test file and execute it with the minishell program
while IFS= read -r test_case; do
  ./minishell
  echo $test_case
   while true; do
   echo "Start"
   usleep 5000000  # Sleep for 500 milliseconds (500000 microseconds)
   echo "End"
    # Code to be executed repeatedly

    # Break the infinite loop if needed

  done


done < "$test_file"

  # Run the minishell program
  
  # Simulate entering the test case and subsequent commands in the minishell
#   echo "$test_case"
#   while true; do
#     read -p "bash$ " input
#     if [[ $input == "exit" ]]; then
#       break
#     fi
#     echo "$input"
#   done
  
#   echo "========================"
#   echo
# done < "$test_file"

# Clean up the compiled files using the Makefile
#make clean


