#name: adam celermajer
# taz: 332638592
#!/bin/bash

# File Check
#*****************************************************************************
if [ ! -f parse_moves.py ]; then
    echo "Error: parse_moves.py not found."
    exit 1
fi

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <source_pgn_file>"
  exit 1
fi

filepath=$1
flag=0
if [ ! -f "$filepath" ]; then
  echo "File '$filepath' does not exist."
  exit 1
fi
#*****************************************************************************

# Parsing File
#*****************************************************************************
echo "Metadata from PGN file:"
grep -E '^\[.*\]$' "$filepath"
echo 
moves=$(grep -v '^\[.*\]$' "$filepath" | grep -v '^$')
uci_moves=$(python parse_moves.py "$moves")
IFSa=' ' read -r -a moves_array <<< "$uci_moves"
#*****************************************************************************


# Initialize running variables
#*****************************************************************************
initial_board=(
  r n b q k b n r 
  p p p p p p p p
  . . . . . . . .
  . . . . . . . .
  . . . . . . . .
  . . . . . . . .
  P P P P P P P P
  R N B Q K B N R
)
myboard=("${initial_board[@]}")
current_move=0
moves_array_length=${#moves_array[@]}
#*****************************************************************************

# Function to display the board
display_board() {
    echo "Move $current_move/$moves_array_length"
    echo "  a b c d e f g h"
    for i in {0..7}; do
        echo -n "$((8-i)) "
        for j in {0..7}; do
            echo -n "${myboard[i*8+j]} "
        done
        echo "$((8-i))"
    done
    echo "  a b c d e f g h"
    
}

multy_apply() {
    movetogo=$1
    
    myboard=("${initial_board[@]}")
    current_move=0

    for ((i=0; i<movetogo; i++)); do
        apply_move 
        current_move=$((current_move + 1))
    done
}

# Function to apply a move
apply_move() {
from="${moves_array[$current_move]:0:2}"
to="${moves_array[$current_move]:2:2}"
prom="${moves_array[$current_move]:4:1}"   
     from_col=$(( $(echo -n "${from:0:1}" | od -An -t uC) - 97 ))
    from_row=$(( 8 - ${from:1:1} ))
    to_col=$(( $(echo -n "${to:0:1}" | od -An -t uC) - 97 ))
    to_row=$(( 8 - ${to:1:1} ))
    piece=${myboard[from_row*8+from_col]}


 # Handle en passant
#*****************************************************************************
# Handle en passant for white pawns
if [ "$piece" = "P" ] && [ "$from_col" -ne "$to_col" ]; then
    if [ "${myboard[to_row*8+to_col]}" = "." ]; then
      
        myboard[((to_row+1)*8+to_col)]="."
    fi
# Handle en passant for black pawns
elif [ "$piece" = "p" ] && [ "$from_col" -ne "$to_col" ]; then
    if [ "${myboard[to_row*8+to_col]}" = "." ]; then
        myboard[((to_row-1)*8+to_col)]="."
    fi
fi
#*****************************************************************************
    myboard[from_row*8+from_col]="."
    if [ -n "$prom" ]; then
    myboard[to_row*8+to_col]="$prom"
else
    myboard[to_row*8+to_col]="$piece"
fi

    # Handle castling
#*****************************************************************************
if [ "$piece" = "K" ] && [ "$from" = "e1" ]; then
    if [ "$to" = "g1" ]; then
        myboard[7*8+7]="."
        myboard[7*8+5]="R"
    elif [ "$to" = "c1" ]; then
        myboard[7*8+0]="."
        myboard[7*8+3]="R"
    fi
elif [ "$piece" = "k" ] && [ "$from" = "e8" ]; then
    if [ "$to" = "g8" ]; then
        myboard[0*8+7]="."
        myboard[0*8+5]="r"
    elif [ "$to" = "c8" ]; then
        myboard[0*8+0]="."
        myboard[0*8+3]="r"
    fi
fi
#*****************************************************************************
}
display_board
while true; do
        
       
        # Read the entire input string
        read key
      
        for (( i=0; i<${#key}; i++ )); do    
         echo "Press 'd' to move forward, 'a' to move back, 'w' to go to the start, 's' to go to the end, 'q' to quit:"
        case ${key:$i:1} in
            d)
                if [ $current_move -lt $moves_array_length ]; then
                    apply_move
                    current_move=$((current_move + 1))
                    display_board
                else
                    echo "No more moves available."
                fi
                ;;
            a)
                if [ $current_move -gt 0 ]; then
                    multy_apply $((current_move - 1))
                    
                fi
                    display_board
                ;;
            w)
                current_move=0
                # Reset to initial board state
                myboard=("${initial_board[@]}")
                display_board
                ;;
            s)
                # Apply all moves to the end
                multy_apply $((moves_array_length))
                display_board
                ;;
            q)
                echo "Exiting."
                echo "End of game."
                exit 0
                ;;
            *)
                echo "Invalid key pressed: ${key:$i:1}"
                ;;
        esac
        done
      
    done
done
