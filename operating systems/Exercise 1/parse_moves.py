import sys
import chess.pgn

def parse_moves(pgn_moves):

    # Create a new game
    game = chess.pgn.Game()

    # Set up a node for adding moves
    node = game

    # Split and filter out move numbers and results
    moves = pgn_moves.split()
    filtered_moves = [
        move for move in moves if not move.endswith('.') and move not in ['1-0', '0-1', '1/2-1/2', '*']
    ]

    # Add moves to the game
    for move in filtered_moves:
        try:
            # Handle special notations like castling, checks, or promotions
            board = node.board()
            move_obj = board.parse_san(move)
            node = node.add_variation(move_obj)
        except ValueError:
            print(f"Error parsing move: {move}", file=sys.stderr)
            continue

    # Traverse the game to print moves in UCI format (from-to squares)
    node = game
    while not node.is_end():
        next_node = node.variation(0)
        move = node.board().uci(next_node.move)
        print(move, end=' ')
        node = next_node

if __name__ == "__main__":
    # Read PGN moves from command line arguments
    pgn_moves = sys.argv[1] if len(sys.argv) > 1 else ""
    if pgn_moves:
        parse_moves(pgn_moves)
    else:
        print("No moves provided", file=sys.stderr)
