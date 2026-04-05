#include "raylib.h"

const int screenWid = 300;
const int screenHig = 600;
const int cellSize = 30;
const int cols = 10;
const int rows = 20;

class Board {
public:
    int grid[rows][cols] = { 0 };

    void Draw() {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] != 0) {
                    DrawRectangle(c * cellSize, r * cellSize, cellSize - 2, cellSize - 2, GRAY);
                }
                DrawRectangleLines(c * cellSize, r * cellSize, cellSize, cellSize, LIGHTGRAY);
            }
        }
    }

    bool moves(int x, int y) {
        if (x < 0 || x >= cols || y >= rows) return false;
        if (y < 0) return true;
        return grid[y][x] == 0;
    }

    void LockPiece(int x, int y) {
        if (y >= 0) grid[y][x] = 1;
    }
};

class Piece {
public:
    int x = 4;
    int y = 0;
    Color color = BLUE;

    void Draw() {
        DrawRectangle(x * cellSize, y * cellSize, cellSize - 2, cellSize - 2, color);
    }

    bool Move(int dx, int dy, Board& board) {
        if (board.moves(x + dx, y + dy)) {
            x += dx;
            y += dy;
            return true;
        }
        return false;
    }

    void Reset() {
        x = 4;
        y = 0;
    }
};

int main() {
    InitWindow(screenWid, screenHig, "ANU Tetris");
    SetTargetFPS(60);

    Board board;
    Piece piece;
    float timer = 0;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_LEFT))  piece.Move(-1, 0, board);
        if (IsKeyPressed(KEY_RIGHT)) piece.Move(1, 0, board);
        if (IsKeyPressed(KEY_DOWN))  piece.Move(0, 1, board);

        timer += GetFrameTime();
        if (timer >= 0.5f) {
            if (!piece.Move(0, 1, board)) {
                board.LockPiece(piece.x, piece.y);
                piece.Reset();
            }
            timer = 0;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        board.Draw();
        piece.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}