#name: adam celermajer
# taz: 332638592
#!/bin/bash
if [ "$#" -ne 2 ]; then
  echo "Usage: $0 <source_pgn_file> <destination_directory>"
  exit 1
fi

filepath=$1
output_filepath=$2
filename=$(basename "$filepath" .pgn)
keyword="[Event "  # Replace with the specific word you're looking for
flag=0
new_filename="NULL"


# Check if the correct number of arguments is provided
if [ ! -f "$filepath" ]; then
  echo "Error: File '$filepath' does not exist."
  exit 1
fi
# Create the output directory if it doesn't exist
if [ ! -d "$output_filepath" ]; then
  mkdir -p "$output_filepath"
  echo "Created directory: '$output_filepath'"
fi

# Read and process the file line by line
while IFS= read -r line; do
  # Skip comments and empty lines
  if [[ "$line" =~ ^#.*$ ]] || [[ -z "$line" ]]; then
    continue
  fi
      # Check if the line starts with the specific word
  if [[ "$line" == "$keyword"* ]]; then
    # Create a new file with a unique name
    ((flag++))
    new_filename="${output_filepath}"/"${filename}"_"${flag}.pgn"
    echo "Saved game to $new_filename"
  fi
# Write the line to the new file
    echo "$line" >> "$new_filename"

done < "$filepath"
echo "All games have been split and saved to '${output_filepath}'."