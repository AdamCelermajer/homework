import chess
import chess.pgn
import sys
import io

def extract_pgn_data(file_path):
    with open(file_path, 'r') as file:
        pgn = file.read()
    
    pgn_io = io.StringIO(pgn)
    game = chess.pgn.read_game(pgn_io)
    metadata = game.headers
    moves = [move.uci() for move in game.mainline_moves()]

    return metadata, moves

def print_metadata(metadata):
    print("Metadata from PGN file:")
    for key, value in metadata.items():
        print(f"[{key} \"{value}\"]")

def print_board(board, current_move, total_moves):
    print(f"\nMove {current_move}/{total_moves}")
    print("  a b c d e f g h")
    for rank in range(8, 0, -1):
        row = f"{rank} "
        for file in range(1, 9):
            piece = board.piece_at(chess.square(file - 1, rank - 1))
            row += f"{piece.symbol() if piece else '.'} "
        row += f"{rank}"
        print(row)
    print("  a b c d e f g h")

def main():
    if len(sys.argv) != 2:
        print("Usage: python chess_game.py <PGN_FILE>")
        return

    file_path = sys.argv[1]
    metadata, moves = extract_pgn_data(file_path)
    print_metadata(metadata)

    board = chess.Board()
    move_index = 0
    total_moves = len(moves)

    print_board(board, move_index, total_moves)

    while True:
        key = input("Press 'd' to move forward, 'a' to move back, 'w' to go to the start, 's' to go to the end, 'q' to quit:").strip().lower()
        if key == 'd':
            if move_index < total_moves:
                board.push_uci(moves[move_index])
                move_index += 1
                print_board(board, move_index, total_moves)
            else:
                print()
                print("No more moves available.")
        elif key == 'a':
            if move_index > 0:
                move_index -= 1
                board.pop()
                print_board(board, move_index, total_moves)
            else:
                print_board(board, move_index, total_moves)
        elif key == 'w':
            while move_index > 0:
                board.pop()
                move_index -= 1
            print_board(board, move_index, total_moves)
        elif key == 's':
            while move_index < total_moves:
                board.push_uci(moves[move_index])
                move_index += 1
            print_board(board, move_index, total_moves)
        elif key == 'q':
            print()
            print("Exiting.")
            print("End of game.")
            break
        else:
            print()
            print(f"Invalid key pressed: {key}")

if __name__ == "__main__":
    main()
